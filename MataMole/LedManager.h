#ifndef LedManager_h
#define LedManager_h
#define NUMBER_OF_MOLES 10

#include "Arduino.h"

class LedManager
{
public:
  LedManager();
  LedManager(int first, int second, int third, int fourth, int fifth);
  LedManager(int first, int second, int third, int fourth, int fifth, int sixth, int seventh, int eighth, int nineth, int tenth);
  void enable(int ledNumber);
  void disable(int ledNumber);
  void enableAll();
  void disableAll();
  void toggle(int ledNumber);
private:
  int _pins[NUMBER_OF_MOLES];
};

#endif
