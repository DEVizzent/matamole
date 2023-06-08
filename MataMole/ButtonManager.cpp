#include "ButtonManager.h"

ButtonManager::ButtonManager()
{}
ButtonManager::ButtonManager(int first, int second, int third, int fourth, int fifth)
{
  _pins[0] = first;
  _pins[1] = second;
  _pins[2] = third;
  _pins[3] = fourth;
  _pins[4] = fifth;
  for(int i = 0; i < NUMBER_OF_MOLES; i++) {
    pinMode(_pins[i], INPUT);
    _lastStatus[i] = false;
    _currentStatus[i] = false;
  }
}
ButtonManager::ButtonManager(int first, int second, int third, int fourth, int fifth, int sixth, int seventh, int eighth, int nineth, int tenth)
{
  _pins[0] = first;
  _pins[1] = second;
  _pins[2] = third;
  _pins[3] = fourth;
  _pins[4] = fifth;
  _pins[5] = sixth;
  _pins[6] = seventh;
  _pins[7] = eighth;
  _pins[8] = nineth;
  _pins[9] = tenth;
  
  for(int i = 0; i < NUMBER_OF_MOLES; i++) {
    pinMode(_pins[i], INPUT);
    _lastStatus[i] = false;
    _currentStatus[i] = false;
  }
}
void ButtonManager::readButtons()
{
  for (int i = 0; i < NUMBER_OF_MOLES; i++) {
     _currentStatus[i] = (digitalRead(_pins[i]) == HIGH);
     _haveBeenPressed[i] = _currentStatus[i] && !_lastStatus[i];
     _lastStatus[i] = _currentStatus[i];
  }
}

bool ButtonManager::hasBeenPressed(int buttonNumber)
{
  return _haveBeenPressed[buttonNumber];
}

int ButtonManager::getButtonPressed() {
  readButtons();
  for (int i = 0; i < NUMBER_OF_MOLES; i++) {
    if (_haveBeenPressed[i]) {
      return i;
    }
  }
  return 1000;
}
