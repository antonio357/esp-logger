
// create acess point
// https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/soft-access-point-examples.html
#include <ESP8266WiFi.h>

void setup() {
  Serial.begin(9600);
  Serial.println();

  Serial.print("Setting soft-AP ... ");
  boolean result = WiFi.softAP("my-esp", "password");
  if(result == true) Serial.println("Ready");
  else Serial.println("Failed!");
}

void loop() {
  Serial.printf("Stations connected = %d\n", WiFi.softAPgetStationNum());
  delay(3000);
}