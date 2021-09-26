
/**
 * 
 *  To make the radio work in config file RF24_config.h do the following:
 *  1)  uncomment line
 *        //#define SOFTSPI  =>  #define SOFTSPI 
 *      
 *  2) сhange pins:
 *      #define SOFT_SPI_MISO_PIN 7
 *      #define SOFT_SPI_MOSI_PIN 6
 *      #define SOFT_SPI_SCK_PIN 5
 *   
**/
      
#define E1_PIN 10
#define M1_PIN 12
#define E2_PIN 11
#define M2_PIN 13
#define BUZZER_PIN 4

#include "DigitalIO.h"
#include "nRF24L01.h"
#include "RF24.h"

#include "crawler.h"
#include "controller.h"

SoftSPI<SOFT_SPI_MISO_PIN, SOFT_SPI_MOSI_PIN, SOFT_SPI_SCK_PIN, SPI_MODE> spi;

RF24 radio(8, 9); // "создать" модуль на пинах 8 (CE) и 9 (CS(N)) 

byte address[][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"}; // возможные номера пайпов
char receivedData[32] = "";

Crawler crawler(E1_PIN, M1_PIN, E2_PIN, M2_PIN, BUZZER_PIN);
Controller controller;

String command;

unsigned int xAxis = 512;
unsigned int yAxis = 512;

void setup()
{
  //crawler.enableDebugMode();
  Serial.begin(9600);
 
  
  crawler.begin();  
  command.reserve(32);

  radio.begin();                        // активировать модуль
  radio.setAutoAck(1);                  // режим подтверждения приёма, 1 вкл 0 выкл
  radio.setRetries(0, 15);              // (время между попыткой достучаться, число попыток)
  radio.enableAckPayload();             // разрешить отсылку данных в ответ на входящий сигнал
  radio.setPayloadSize(32);             // размер пакета, в байтах

  radio.openReadingPipe(1, address[0]); // хотим слушать пайп 0
  radio.setChannel(0x60);               // выбираем канал (в котором нет шумов!)

  radio.setPALevel (RF24_PA_MAX);       // уровень мощности передатчика. На выбор RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
  radio.setDataRate (RF24_250KBPS);     // скорость обмена. На выбор RF24_2MBPS, RF24_1MBPS, RF24_250KBPS
                                        // должна быть одинакова на приёмнике и передатчике!
                                        // при самой низкой скорости имеем самую высокую чувствительность и дальность!!

  radio.powerUp(); // начать работу
  radio.startListening(); //  начинаем слушать эфир, мы приёмный модуль
}

void loop()
{
  byte pipeNo;
  if (radio.available(&pipeNo)) {   
    radio.read(&receivedData, sizeof(receivedData)); 

    command = String(receivedData);

    if (command.startsWith("xy:")) {
      char commandChars[14];
      memset(commandChars, 0, sizeof(commandChars));
      command.toCharArray(commandChars, sizeof(commandChars));
      strtok(commandChars, ":,;");

      xAxis = atoi(strtok (NULL, ":,;"));
      yAxis = 1023 - atoi(strtok (NULL, ":,;"));

      delay(5);
    }
  }

  controller.setAxes(xAxis, yAxis);

  Crawler::Direction direction = controller.getDirection();
  int leftSpeed = controller.getLeftSpeed();
  int rightSpeed = controller.getRightSpeed();


  crawler.speed(leftSpeed, rightSpeed);
  crawler.run(direction);       
}
