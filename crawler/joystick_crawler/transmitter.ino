
/*
   Arduino Robot Car Wireless Control using the NRF24L01 Transceiver module
             == Transmitter - Joystick ==
   by Dejan Nedelkovski, www.HowToMechatronics.com
   Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // "создать" модуль на пинах 9 и 10 Для Уно
byte address[][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"}; //возможные номера труб

char commandData[32] = "";
String xAxis, yAxis;


void setup() {
  Serial.begin(9600);

  radio.begin(); //активировать модуль
  radio.setAutoAck(1);         //режим подтверждения приёма, 1 вкл 0 выкл
  radio.setRetries(0, 15);    //(время между попыткой достучаться, число попыток)
  radio.enableAckPayload();    //разрешить отсылку данных в ответ на входящий сигнал
  radio.setPayloadSize(32);     //размер пакета, в байтах

  radio.openWritingPipe(address[0]);   //мы - труба 0, открываем канал для передачи данных
  radio.setChannel(0x60);  //выбираем канал (в котором нет шумов!)

  radio.setPALevel (RF24_PA_MAX); //уровень мощности передатчика. На выбор RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
  radio.setDataRate (RF24_250KBPS); //скорость обмена. На выбор RF24_2MBPS, RF24_1MBPS, RF24_250KBPS
  //должна быть одинакова на приёмнике и передатчике!
  //при самой низкой скорости имеем самую высокую чувствительность и дальность!!

  radio.powerUp(); //начать работу
  radio.stopListening(); //не слушаем радиоэфир, мы передатчик
}


void loop() {

  xAxis = analogRead(A1); // Read Joysticks X-axis
  yAxis = analogRead(A2); // Read Joysticks Y-axis
  
  String command = "xy:" + xAxis + "," + yAxis + ";";
 
  command.toCharArray(commandData, 14);
  radio.write(&commandData, sizeof(commandData)); // Send the array data (command) to the other NRF24L01 module

  delay(10);
}
