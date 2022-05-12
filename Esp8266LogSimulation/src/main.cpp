#include <ESP8266WiFi.h>

WiFiServer server(5000);

void configSerialMonitor(int num=9600) {
   Serial.begin(num);
   delay(1000);
   Serial.println("Monitor working");
}

void connectToRouter(const char *ssid, const char *password) {
  Serial.print("Conecting to router");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print(" .");
  }
  Serial.println("\nConected");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  configSerialMonitor();
  connectToRouter("TP-LINK_FE84", "71656137");
  server.begin();
}

int counter = 0;

void loop() {
  WiFiClient client = server.available();
  // while (client && client.connected() && client.available() > 0) {     
  //   client.println("counter " + counter++);
  //   client.stop();
  //   delay(500);
  //   Serial.println("sent data");
  // }
  if (client) {
    Serial.println("has client");
    while (client.connected()) {
      Serial.println("client connected");
      // client.println("counter " + counter++);
      client.write("this is a log");
      // delay(500);
      Serial.println("sent data");
      // while (client.available() > 0) {
      //   Serial.println("client avaliable");
      //   client.println("counter " + counter++);
      //   client.stop();
      //   delay(500);
      //   Serial.println("sent data");
      // }
    }
  }
}
