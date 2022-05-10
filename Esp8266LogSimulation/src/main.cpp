#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>

const char *ssid = "test";
const char *password = "password";

WebSocketsServer webSocket = WebSocketsServer(81);

// Tratamento de eventos dos dados que vêm do cliente 
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t lenght) {

  switch (type) {
    case WStype_DISCONNECTED:
      break;

    case WStype_CONNECTED:
      { IPAddress ip = webSocket.remoteIP(num);
        Serial.println(ip);
      }
      break;

    case WStype_TEXT:
      { String text = String((char *) &payload[0]);
        Serial.println(text);
        Serial.println(num);
        Serial.println(type);

        if (text == "ON") {
          digitalWrite(BUILTIN_LED, LOW);
        } else {
          digitalWrite(BUILTIN_LED, HIGH);
        }
      }
      break;

  }

}

void socketReciveCommands() {

}

void socketsendLogs() {
  
}

void setup() {
  Serial.begin(9600);
  Serial.println("Configuring access point…");
  WiFi.softAP(ssid, password);

  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, HIGH);

  Serial.println(WiFi.softAPIP());
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  // sending data
  delay(3000);
  webSocket.sendTXT(0, "digitalRead(BUILTIN_LED)");
}

// node code remove this later
// Coloque aqui o IP obtino no ESP8266
// let con = WebSocket.server('ws://192.168.4.1:81/', ['arduino']);
let ws = new WebSocket("ws://192.168.4.1:81/");

ws.onopen = function (event) {
  ws.send("node client found");
};

ws.onmessage = function (evt) { 
  console.log("esp send ", evt.data);
};