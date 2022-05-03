/*------------------------------------------------------------------------------
  11/30/2016
  Author: Makerbro
  Platforms: ESP8266
  Language: C++/Arduino
  File: server.ino
  ------------------------------------------------------------------------------
  Description: 
  Code for YouTube video demonstrating how to use Python to send data to a
  webserver running on an ESP8266.
  https://youtu.be/CpWhlJXKuDg 

  Do you like my videos? You can support the channel:
  https://patreon.com/acrobotic
  https://paypal.me/acrobotic
  ------------------------------------------------------------------------------
  Please consider buying products from ACROBOTIC to help fund future
  Open-Source projects like this! We'll always put our best effort in every
  project, and release all our design files and code for you to use. 

  https://acrobotic.com/
  https://amazon.com/acrobotic
  ------------------------------------------------------------------------------
  License:
  Please see attached LICENSE.txt file for details.
------------------------------------------------------------------------------*/
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
// #include <ArduinoJson.h>

ESP8266WebServer server;
uint8_t pin_led = LED_BUILTIN;
char* ssid = "wifi-name";
char* password = "wifi-password";

void toggleLED()
{
  digitalWrite(pin_led,!digitalRead(pin_led));
  server.send(204,"");
}

void qBlinkLED()
{
  String del = server.arg("pause");
  String n = server.arg("times");
  Serial.println(del + ", " + n);
  for (int i=0; i<n.toInt();i++)
  {
   digitalWrite(pin_led,!digitalRead(pin_led));
   delay(del.toInt()); 
  }
  server.send(200, "led piscou");
}

void setup()
{
  pinMode(pin_led, OUTPUT);
  WiFi.begin(ssid,password);
  Serial.begin(9600);
  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/",[](){server.send(200,"text/plain","Hello World!");});
  server.on("/toggle",toggleLED);
  // server.on("/jblink",jBlinkLED);
  server.on("/qblink",qBlinkLED);
  server.begin();
}

void loop()
{
  server.handleClient();
}

// void jBlinkLED()
// {
//   String data = server.arg("plain");
//   StaticJsonBuffer<200> jBuffer;
//   JsonObject& jObject = jBuffer.parseObject(data);
//   String del = jObject["pause"];
//   String n = jObject["times"];
//   for (int i=0; i<n.toInt();i++)
//   {
//    digitalWrite(pin_led,!digitalRead(pin_led));
//    delay(del.toInt()); 
//   }
//   server.send(200,"text/plain","GOT THE DATA!"); 
// }


// to test https://lastminuteengineers.com/creating-esp32-web-server-arduino-ide/
// to test https://stackoverflow.com/questions/59118310/how-to-send-string-to-esp32-using-http  
// loking for how to create a esp8266 server that will be sendding info and can revive info
// idea esp creates server -> client connects to esp server -> leaves open connection so esp server can send logs

// https://www.youtube.com/watch?v=CpWhlJXKuDg&ab_channel=datasith