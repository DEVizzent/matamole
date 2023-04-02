#ifndef GameMole_h
#define GameMole_h
#define NUMBER_OF_MOLES 5
#include "Arduino.h"
#include "arduino-timer.h"
#include "ScoreDisplay.h"
#include "LedManager.h"
#include "ButtonManager.h"
#include "Score.h"

class GameMole
{
public:
  GameMole();
  GameMole(ButtonManager bManager, LedManager lManager, ScoreDisplay sDisplay);
  void initialize(int dificulty);
  bool loop();
private:
  ButtonManager buttonManager;
  LedManager ledManager;
  ScoreDisplay scoreDisplay;
  Score score;
  int juicyTime;
  bool molesActive[NUMBER_OF_MOLES] = {false, false, false, false, false};;
};

#endif
