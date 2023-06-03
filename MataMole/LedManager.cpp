
#include "LedManager.h"
LedManager::LedManager()
{}

LedManager::LedManager(int first, int second, int third, int fourth, int fifth) 
{
  _pins[0] = first;
  _pins[1] = second;
  _pins[2] = third;
  _pins[3] = fourth;
  _pins[4] = fifth;
  for(int i; i < NUMBER_OF_LEDS; i++) {
    pinMode(_pins[i], OUTPUT);
  }
}

void LedManager::toggle(int ledNumber) {
  digitalWrite(_pins[ledNumber], !digitalRead(_pins[ledNumber]));
}

void LedManager::enable(int ledNumber) {
  digitalWrite(_pins[ledNumber], HIGH);
}

void LedManager::disable(int ledNumber) {
  digitalWrite(_pins[ledNumber], LOW);
}

void LedManager::enableAll() {
  for(int i = 0; i < NUMBER_OF_LEDS; i++) {
    digitalWrite(_pins[i], HIGH);
  }
}

void LedManager::disableAll() {
  for(int i = 0; i < NUMBER_OF_LEDS; i++) {
    digitalWrite(_pins[i], LOW);
  }
}
