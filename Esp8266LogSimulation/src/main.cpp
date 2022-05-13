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
// https://www.youtube.com/watch?v=H6qpSjj3HgE&ab_channel=ElectricalMagic
void loop() {
  WiFiClient client = server.available();

  while (client && client.connected()) {
    Serial.println("client connected");
    client.write("this is a log");
    Serial.println("sent data");
  }
}
