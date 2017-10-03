#include <SPI.h>
#include <Ethernet.h>
#include <SD.h>

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 40, 177);

char rootFileName[] = "index.htm";
EthernetServer server(80);

File myFile;

void setup() {
  SD.begin(4);
  Serial.begin(9600);

  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);

  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);

  Ethernet.begin(mac, ip);
  server.begin();
}

void loop()
{
  char clientline[100];
  char *filename;
  int index = 0;

  EthernetClient client = server.available();

  if (client) {
    // reset the input buffer
    index = 0;

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();

        if (c != '\n' && c != '\r') {
          clientline[index] = c;
          index++;
          continue;
        }

        clientline[index] = 0;
        filename = 0;

        Serial.println(clientline);

        // Look for substring such as a request to get the root file
        if (strstr(clientline, "GET / ") != 0) {
          filename = rootFileName;
        }

        if (strstr(clientline, "GET /") != 0) {
          // this time no space after the /, so a sub-file

          if (!filename) filename = clientline + 5; // look after the "GET /" (5 chars)

          // a little trick, look for the " HTTP/1.1" string and
          // turn the first character of the substring into a 0 to clear it out.

          (strstr(clientline, " HTTP"))[0] = 0;

          if (filename[0] == '?') {
            String queryString(filename);

            if (queryString.indexOf("state=on") > 0) {
              digitalWrite(3, HIGH);
              Serial.println("Led On");

              client.println("HTTP/1.1 200 OK");
              client.println("Content-Type: application/json");
              client.println();
              client.println("{\"state\":\"on\"}");
              break;

            } else if (queryString.indexOf("state=off") > 0) {
              digitalWrite(3, LOW);
              Serial.println("Led Off");

              client.println("HTTP/1.1 200 OK");
              client.println("Content-Type: application/json");
              client.println();
              client.println("{\"state\":\"off\"}");
              break;

            } else if (queryString.indexOf("state") > 0) {
              bool state = digitalRead(3);

              client.println("HTTP/1.1 200 OK");
              client.println("Content-Type: application/json");
              client.println();

              if (state) {
                client.println("{\"state\":\"on\"}");

              } else {
                client.println("{\"state\":\"off\"}");
              }

              break;
            }
          }

          myFile = SD.open(filename);

          if (!myFile ) {
            client.println("HTTP/1.1 404 Not Found");
            client.println("Content-Type: text/html");
            client.println();

            client.print("<h3>");
            client.print(filename);
            client.print(" not found! ");
            client.print("</h3>");
            client.println("");
            break;
          }

          client.println("HTTP/1.1 200 OK");

          if (strstr(filename, ".htm") != 0) {
            client.println("Content-Type: text/html");

          } else if (strstr(filename, ".css") != 0) {
            client.println("Content-Type: text/css");

          } else if (strstr(filename, ".js") != 0) {
            client.println("Content-Type: application/x-javascript");

          } else if (strstr(filename, ".jpg") != 0) {
            client.println("Content-Type: image/jpeg");

          } else {
            client.println("Content-Type: text");
          }

          client.println();

          byte cB[64];
          int cC = 0;

          while (myFile.available()) {
            cB[cC] = myFile.read();
            cC++;
            if (cC > 63) {
              client.write(cB, 64);
              cC = 0;
            }
          }

          if (cC > 0) {
            client.write(cB, cC);
          }

          myFile.close();

        } else {
          // everything else is a 404
          client.println("HTTP/1.1 404 Not Found");
          client.println("Content-Type: text/html");
          client.println();
          client.println("<h2>File Not Found!</h2>");

        }

        break;
      }
    }

    // give the web browser time to receive the data
    delay(1);
    client.stop();
  }
}
