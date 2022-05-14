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

// https://github.com/datasith/Ai_Demos_ESP32/tree/master/two_board_comm
int counter = 0;
void loop() {
  webSocket.loop();
  const char msg[] = "cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc";
  if (webSocket.connectedClients()) {
    webSocket.broadcastTXT(msg, strlen(msg));
    counter++;
  } else if (counter > 0) {
    Serial.print("sent msgs: ");
    Serial.print(counter);
    Serial.print(" len: ");
    Serial.println(strlen(msg));
    counter = 0;
  } 
}
