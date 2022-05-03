#include <ESP8266WiFi.h>

#include "../utils/leds/builtInLed.cpp"


const char* ssid = "wifi-name";
const char* password = "wifi-password";


namespace connectToWifiRouter {
  void setup(const char* ssid, const char* password) {
    builtInLed::setup();
    builtInLed::turnOff();

    Serial.begin(9600);
    Serial.println();
    Serial.print("Wifi connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    Serial.println();
    Serial.print("Connecting");

    while(WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");      
    }

    builtInLed::turnOn();
    Serial.println();

    Serial.println("Wifi Connected Success!");
    Serial.print("NodeMCU IP Address : ");
    Serial.println(WiFi.localIP());
  }
}

// info https://www.youtube.com/watch?v=TnWDlHpY56o&ab_channel=MakerTutor
