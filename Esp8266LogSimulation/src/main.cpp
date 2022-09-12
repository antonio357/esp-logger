#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>
#include <ArduinoJson.h> 

// https://www.youtube.com/watch?v=15X0WvGaVg8&ab_channel=mo_thunderz
// The JSON library uses static memory, so this will need to be allocated:
StaticJsonDocument<200> doc_tx;                       // provision memory for about 200 characters
StaticJsonDocument<200> doc_rx;

boolean send_log = false;

WebSocketsServer webSocket = WebSocketsServer(81);

void configSerialMonitor(int num=9600) {
   Serial.begin(num);
   delay(1000);
   Serial.println("Monitor working");
}

void connectToRouter(const char *ssid, const char *password) {
  Serial.print("Conecting to router");

  // https://www.youtube.com/watch?v=B9jJI7p2Gw4&ab_channel=MishMashLabs, setando ip fixo
  IPAddress local_IP(192, 168, 1, 199);
  IPAddress gateway(192, 168, 1, 1);
  IPAddress subnet(255, 255, 0, 0);
  if (!WiFi.config(local_IP, gateway, subnet)) Serial.println("STA Failed to configure");

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
  switch (type) {                                     // switch on the type of information sent
    // case WStype_ERROR:
    //   break;
    // case WStype_BIN:
    //   break;
    // case WStype_FRAGMENT_TEXT_START:
    //   break;
    // case WStype_FRAGMENT_BIN_START:
    //   break;
    // case WStype_FRAGMENT:
    //   break;
    // case WStype_FRAGMENT_FIN:
    //   break;
    case WStype_PING:
      Serial.println("Client " + String(num) + " pinged");
      break;
    case WStype_PONG:
      Serial.println("Client " + String(num) + " ponged");
      break;
    case WStype_DISCONNECTED:                         // if a client is disconnected, then type == WStype_DISCONNECTED
      Serial.println("Client " + String(num) + " disconnected");
      break;
    case WStype_CONNECTED:                            // if a client is connected, then type == WStype_CONNECTED
      Serial.println("Client " + String(num) + " connected");
      Serial.println("Server has " + String(webSocket.connectedClients()) + " clients connected");
      Serial.println("Server has " + webSocket.remoteIP(num).toString() + " clients connected");
      // webSocket.enableHeartbeat();
      // webSocket.enableHeartbeat(webSocket.connectedClients());
      break;
    case WStype_TEXT:                                 // if a client has sent data, then type == WStype_TEXT
      char payloadString[strlen((char*)(payload))];
      
      strcpy(payloadString, (char*)(payload));
      if (strcmp(payloadString, "start logs") == 0) send_log = true;
      else if (strcmp(payloadString, "stop logs") == 0) send_log = false;

      Serial.printf("received: payload [%u]: %s\n", num, payloadString);
      // try to decipher the JSON string received
      // DeserializationError error = deserializeJson(doc_rx, payload);
      // if (error) {
      //   Serial.print(F("deserializeJson() failed: "));
      //   Serial.println(error.f_str());
      //   return;
      // }
      // else {
      //   // JSON string was received correctly, so information can be retrieved:
      //   const char* g_brand = doc_rx["brand"];
      //   const char* g_type = doc_rx["type"];
      //   const int g_year = doc_rx["year"];
      //   const char* g_color = doc_rx["color"];
      //   Serial.println("Received guitar info from user: " + String(num));
      //   Serial.println("Brand: " + String(g_brand));
      //   Serial.println("Type: " + String(g_type));
      //   Serial.println("Year: " + String(g_year));
      //   Serial.println("Color: " + String(g_color));
      // }
      // Serial.println("");
      break;
  };
}

void setup() {
  configSerialMonitor();
  connectToRouter("TP-LINK_FE84", "71656137");

  webSocket.begin();
  webSocket.onEvent(receiveMsg);
  // webSocket.enableHeartbeat(5000, 3000, -1);
}

// https://github.com/datasith/Ai_Demos_ESP32/tree/master/two_board_comm
int counter = 0;
void loop() {
  webSocket.loop();
  const char msg[] = "cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc";
  if (send_log && webSocket.connectedClients()) {
    // webSocket.broadcastTXT(msg, strlen(msg));
    String jsonString = "";                           // create a JSON string for sending data to the client
    JsonObject object = doc_tx.to<JsonObject>();      // create a JSON Object
    object["rand1"] = random(100);                    // write data into the JSON object -> I used "rand1" and "rand2" here, but you can use anything else
    object["rand2"] = random(100);
    serializeJson(doc_tx, jsonString);                // convert JSON object to string
    webSocket.broadcastTXT(jsonString);               // send JSON string to clients
    counter++;
  } else if (counter > 0) {
    Serial.print("sent msgs: ");
    Serial.print(counter);
    Serial.print(" len: ");
    Serial.println(strlen(msg));
    counter = 0;
  } 
}
