#include <ESP8266WiFi.h>

const char *ssid = "test";
const char *password = "password";

boolean sendLog = false;

WiFiServer server(5000);

// definindo sequencia de protocolo
enum Protocol {
  SEND_LOG,
  BUFFER_SIZE // tem que ser o ultimo
};

void setup() {
  // serial monitor
  Serial.begin(9600);

  // access point
  Serial.println("Configuring access point…");
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  server.begin();
  Serial.println(WiFi.softAPIP());

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
