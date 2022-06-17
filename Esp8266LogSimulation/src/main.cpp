#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>

boolean send_log = false;

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

void receiveMsg(uint8_t num, WStype_t type, uint8_t* payload, size_t length) {  
  // make soure any operation is made if (type == WStype_TEXT) the type is correct
  if(type == WStype_TEXT) {
    char payloadString[strlen((char*)(payload))];
    strcpy(payloadString, (char*)(payload));
    const char* start = "start logs";
    const char* stop = "stop logs";
    Serial.print("payloadString = ");
    Serial.println(payloadString);
    Serial.println(strcmp(payloadString, start) == 0);
    boolean startB = strcmp(payloadString, start) == 0;
    boolean stopB = strcmp(payloadString, stop) == 0;
    Serial.println("startB = " + startB);
    Serial.println("stopB = " + stopB);
    if (startB) { // o bug ta na camparacao dentro do if (strcmp(payloadString, start) == 0)
      send_log = true;
      Serial.println(start);
    }
    else if (stopB) {
      send_log = false;
      Serial.println(stop);
    }
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
  if (send_log && webSocket.connectedClients()) {
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
