#ifndef LedManager_h
#define LedManager_h
#define NUMBER_OF_LEDS 5

#include "Arduino.h"

class LedManager
{
public:
  LedManager();
  LedManager(int first, int second, int third, int fourth, int fifth);
  void enable(int ledNumber);
  void disable(int ledNumber);
  void enableAll();
  void disableAll();
  void toggle(int ledNumber);
private:
  int _pins[NUMBER_OF_LEDS];
};

#endif
