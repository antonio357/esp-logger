#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>


WebSocketsServer webSocket = WebSocketsServer(81);

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

void receiveMsg(uint8_t num, WStype_t type, uint8_t *payload, size_t length) {
  if(type == WStype_TEXT) {
    Serial.printf("received: payload [%u]: %s\n", num, payload);
  }
}

void setup() {
  configSerialMonitor();
  connectToRouter("TP-LINK_FE84", "71656137");

  webSocket.begin();
  webSocket.onEvent(receiveMsg);
}

int counter = 0;
void loop() {
  webSocket.loop();
  const char msg[] = "0123456776543210";
  if (webSocket.connectedClients()) {
    webSocket.broadcastTXT(msg, strlen(msg));
    Serial.print("sent msg num ");
    Serial.println(counter++);
  } else counter = 0;
  // delay(1000);
}
