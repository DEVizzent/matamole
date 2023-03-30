/*
  LEDDisplay74HC595.cpp

  Library for presenting number values using a
  4-Bit LED Digital Tube Module with two 74HC595.

  Created by Chrizzzzz January 2016.

  Released into the public domain.
*/
#include "Arduino.h"
#include "ScoreDisplay.h"
#include "arduino-timer.h"

#define EMPTY 11

#define MAX_DECIMAL_PLACES 3

const byte CHARS[] = {
  0b00111111, // 0
  0b00000110, // 1
  0b01011011, // 2
  0b01001111, // 3
  0b01100110, // 4
  0b01101101, // 5
  0b01111101, // 6
  0b00000111, // 7
  0b01111111, // 8
  0b01101111, // 9
  0b00000000, // <empty>
};

const byte POS[] = {
  0b00001000, // first digit in diplay
  0b00000100, // second digit
  0b00000010, // third digit
  0b00000001, // forth digit
};

ScoreDisplay::ScoreDisplay()
{}

ScoreDisplay::ScoreDisplay(int sclk, int rclk, int dio)
{
  pinMode(sclk, OUTPUT);
  pinMode(rclk, OUTPUT);
  pinMode(dio, OUTPUT);
  _shiftClock = sclk;
  _resetClock = rclk;
  _displayIO = dio;
  _refreshDigitIndex = 0;
  _score = 0;
}

void ScoreDisplay::updateScore(int score)
{
  _score = score;
}

void ScoreDisplay::displayScore()
{
  // build the display values
  byte displayBytes[] {
    CHARS[_score / 1000 % 10],
    CHARS[_score / 100 % 10],
    CHARS[_score / 10 % 10],
    CHARS[_score % 10],
  };

  // remove leading zeroes
  int i = 0;
  while(displayBytes[i] == CHARS[0]) {
    displayBytes[i] = CHARS[EMPTY];
    i++;
  }

  // set the current digit character to the LED display
  const byte digitIndex = _refreshDigitIndex++ % 4;
  setDisplayByte(displayBytes[digitIndex], digitIndex);

}

void ScoreDisplay::setDisplayByte(byte displayByte, int pos)
{
  shiftOut(_displayIO, _shiftClock, MSBFIRST, ~displayByte);
  shiftOut(_displayIO, _shiftClock, MSBFIRST, POS[pos]);
  digitalWrite(_resetClock, LOW);
  digitalWrite(_resetClock, HIGH);
}
