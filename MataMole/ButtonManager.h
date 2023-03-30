#ifndef ButtonManager_h
#define ButtonManager_h
#define NUMBER_OF_BUTTONS 5
#include "Arduino.h"

class ButtonManager
{
public:
  ButtonManager();
  ButtonManager(int first, int second, int third, int fourth, int fifth);
  void readButtons();
  bool hasBeenPressed(int buttonNumber);
private:
  int _pins[NUMBER_OF_BUTTONS];
  bool _lastStatus[NUMBER_OF_BUTTONS];
  bool _currentStatus[NUMBER_OF_BUTTONS];
  bool _haveBeenPressed[NUMBER_OF_BUTTONS];
};

#endif
