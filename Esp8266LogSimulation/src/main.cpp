#include <ESP8266WiFi.h>
// #include<cstring>

#define LOG_HEADER_LEN 16

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

void logHeader(char* log_header, const uint16* log_len, const char* pad=".") {
  sprintf(log_header, "log-header:%d", *log_len);
  for (uint8 i = strlen(log_header); i < LOG_HEADER_LEN; i++) strcat(log_header, pad);
}


int counter = 0;
// https://www.youtube.com/watch?v=H6qpSjj3HgE&ab_channel=ElectricalMagic
void loop() {
  WiFiClient client = server.available();

  while (client && client.connected()) {
    const char *msg = "0123456776543210";
    const uint16 msglen = strlen(msg);
    // send header of fix lenght to inform the size of the msg
    // send msg 
    char log_header[LOG_HEADER_LEN];
    logHeader(log_header, &msglen);
    client.write(log_header);
    delay(5);
    client.write(msg);
    delay(5);
    counter++;
  }
  delay(1000);
  Serial.print("logs sent = ");
  Serial.println(counter);
  counter = 0;
}
