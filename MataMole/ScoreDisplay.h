#ifndef ScoreDisplay_h
#define ScoreDisplay_h

#include "Arduino.h"

class ScoreDisplay
{
public:
  ScoreDisplay();
  ScoreDisplay(int sclk, int rclk, int dio);
  void updateScore(int score);
  void displayScore();
private:
  int _shiftClock;
  int _resetClock;
  int _displayIO;
  byte _refreshDigitIndex;
  int _score;
  void setDisplayByte(byte displayByte, int pos);
};

#endif
