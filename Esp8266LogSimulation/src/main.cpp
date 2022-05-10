// #include <ESP8266WiFi.h>
// #include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

const char *ssid = "test";
const char *password = "password";

ESP8266WebServer server(80);

void home() {
  server.send(200, "text/plain", "you are connect to esp8266");
}

String getBody() { 
  return server.arg("plain");
}

void start() {
  const String body = getBody();
  Serial.println(body);
  server.send(200, "application/json", body);
}

void sendPost() {
  delay(4000);
  HTTPClient http;    //Declare object of class HTTPClient
  WiFiClient wifiClient;
 
  http.begin(wifiClient, "192.168.4.2", 8080, "/log");      //Specify request destination
  http.addHeader("Content-Type", "text/plain");  //Specify content-type header
 
  int httpCode = http.POST("Message from ESP8266");   //Send the request
  String payload = http.getString();                  //Get the response payload
 
  Serial.println(httpCode);   //Print HTTP return code
  Serial.println(payload);    //Print request response payload
 
  http.end();  //Close connection
}


void setup() {
  Serial.begin(9600);
  Serial.println("Configuring access point…");
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.printf("AP IP address: "); Serial.println(myIP);

  server.on("/", HTTP_GET, home);
  server.on("/start", HTTP_PATCH, start);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  sendPost();
}