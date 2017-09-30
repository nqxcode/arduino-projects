
/**
   Led switch via web interface

  A simple web server that shows the button for switching of LED
  using an Arduino Wiznet Ethernet shield.

  Address will look like http://192.168.40.177/.

*/

#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //ethernet shield mac address
byte ip[] = { 192, 168, 40, 177 }; // arduino IP in lan
byte gateway[] = { 192, 168, 40, 177 }; // internet access via router
byte subnet[] = { 255, 255, 255, 0 }; //subnet mask

EthernetServer server(80); // server port
String readString;

void setup() {
  pinMode(4, OUTPUT); // pin selected to control

  Ethernet.begin(mac, ip, gateway, gateway, subnet);
  server.begin();

  //enable serial data print
  Serial.begin(9600);
}

void loop() {
  // Create a client connection
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read(); // read char by char HTTP request
        
        if (readString.length() < 100) {
          readString += c;
        }
        
        if (c == '\n') { // if HTTP request has ended
          Serial.println(readString); // print to serial monitor for debuging

          // now output HTML data header
          if (readString.indexOf('?') >= 0) { // don't send new page
            client.println("HTTP/1.1 204 Arduino");
            client.println();
            client.println();
          }
          else {
            client.println("HTTP/1.1 200 OK"); // send new page
            client.println("Content-Type: text/html");
            client.println();

            client.println("<html>");
            client.println("<head>");
            client.println("<meta charset='utf8'>");
            client.println("<title>LED wed switcher</title>");
            client.println("</head>");
            client.println("<body>");

            client.println("<h1>LED web switcher</h1>");

            client.println("<a href='/?on'>Включить</a>");
            client.println("<a href='/?off'>Выключить</a>");

            client.println("</body>");
            client.println("</html>");
          }

          delay(1);
          
          // stopping client
          client.stop();
          
          if (readString.indexOf("on") > 0) { //checks for on
            digitalWrite(4, HIGH);    // set pin 4 high
            Serial.println("Led On");
          }
          
          if (readString.indexOf("off") > 0) { //checks for off
            digitalWrite(4, LOW);    // set pin 4 low
            Serial.println("Led Off");
          }

          // clearing string for next read
          readString = "";
        }
      }
    }
  }
}


