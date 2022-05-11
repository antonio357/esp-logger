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

void loop() {
  WiFiClient client = server.available();
  if (client) {     
    //Se o cliente tem dados que deseja nos enviar
    while (client.connected()) {//Criamos um buffer para colocar os dados
      while (client.available() > 0)
      {
        uint8_t value = client.read();
        Serial.write(value);
      }
      delay(10);
    }
    //Fecha a conexão com o cliente
    client.stop();
  }
}
