#include <Arduino.h>

namespace builtInLed {
  void setup() {pinMode(LED_BUILTIN, OUTPUT);}

  void switchLed() {digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));}

  void turnOn() {digitalWrite(LED_BUILTIN, LOW);}

  void turnOff() {digitalWrite(LED_BUILTIN, HIGH);}
}
