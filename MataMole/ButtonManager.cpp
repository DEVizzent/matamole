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
  for(int i = 0; i < NUMBER_OF_BUTTONS; i++) {
    pinMode(_pins[i], INPUT);
    _lastStatus[i] = false;
    _currentStatus[i] = false;
  }
}
void ButtonManager::readButtons()
{
  for (int i = 0; i < NUMBER_OF_BUTTONS; i++) {
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
  for (int i = 0; i < NUMBER_OF_BUTTONS; i++) {
    if (_haveBeenPressed[i]) {
      return i;
    }
  }
  return 1000;
}
