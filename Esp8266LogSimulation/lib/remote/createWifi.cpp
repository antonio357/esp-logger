//====================================
//ESP8266 Access Point Control of LED
//====================================
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

#include "../utils/leds/builtInLed.cpp"


namespace createWifi {
  //user interface HTML code----------------
  String html = R"***(
  <!DOCTYPE html>
  <html>
    <head>    
      <title>SWITCH LED</title>
    </head>
    <body>
      <h1>SWITCH LED</h1>
      <p><a href=/ledon>LED on</a></p>
      <p><a href=/ledoff>LED off</a></p>
    </body>
  </html>
  )***";
  //--------------------------------------
  const char* ssid = "ESP8266_AP-server";
  IPAddress IPaddr (192, 168, 168, 168);
  IPAddress IPmask(255, 255, 255, 0);
  ESP8266WebServer server(80);
  //--------------------------------------
  void handleRoot() {
    server.send(200, "text/html", html);
  }
  void ledon() {
    builtInLed::turnOn();
    server.send(200, "text/html", html);
  }
  void ledoff() {
    builtInLed::turnOff();
    server.send(200, "text/html", html);
  }
  
  void setup() {
    builtInLed::setup(); 
    delay(1000);
    Serial.begin(9600);
    Serial.println();
    Serial.print("Configuring access point...");
    WiFi.softAP(ssid);
    WiFi.softAPConfig(IPaddr, IPaddr, IPmask); 
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);
    server.on("/", handleRoot);
    server.on("/ledon", ledon);
    server.on("/ledoff", ledoff);
    server.begin();
    Serial.println("HTTP server started");
  }
  
  void toLoop() {
    server.handleClient();
  }
}

// info https://www.youtube.com/watch?v=JCJ4OKv4uto&ab_channel=AnasKuzechie
