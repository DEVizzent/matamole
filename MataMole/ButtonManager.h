#ifndef ButtonManager_h
#define ButtonManager_h
#include "Arduino.h"
#define NUMBER_OF_MOLES 10

class ButtonManager
{
public:
  ButtonManager();
  ButtonManager(int first, int second, int third, int fourth, int fifth);
  ButtonManager(int first, int second, int third, int fourth, int fifth, int sixth, int seventh, int eighth, int nineth, int tenth);
  void readButtons();
  bool hasBeenPressed(int buttonNumber);
  int getButtonPressed();
private:
  int _pins[NUMBER_OF_MOLES];
  bool _lastStatus[NUMBER_OF_MOLES];
  bool _currentStatus[NUMBER_OF_MOLES];
  bool _haveBeenPressed[NUMBER_OF_MOLES];
};

#endif
