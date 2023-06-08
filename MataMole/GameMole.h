#ifndef GameMole_h
#define GameMole_h
#define NUMBER_OF_MOLES 10
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
  GameMole(ButtonManager bManager, LedManager lManager, ScoreDisplay *sDisplay);
  void initialize(int dificulty);
  bool loop();
  String readActionEvent(int mole);
  int readTimerEvent(int mole);
  void cleanActionEvent(int mole);
  void missMole(int);
  void finishMissMole(int);
  void finishGame();
  void updateNumberOfActiveMoles();
private:
  ButtonManager buttonManager;
  LedManager ledManager;
  ScoreDisplay *scoreDisplay;
  Score score;
  int juicyTime;
  int moleTime;
  int countActiveMoles;
  bool hasToUpdateNumberOfActiveMoles;
  int numberOfMolesMustBeActive;
  int randomNumber;
  bool activeMoles[NUMBER_OF_MOLES] = {false, false, false, false, false, false, false, false, false, false};
  String moleEvent[NUMBER_OF_MOLES] = {"","","","","","","","","",""};
  int moleEventTimer[NUMBER_OF_MOLES] = {0,0,0,0,0,0,0,0,0,0};
  int generateNumberOfMolesMustBeActive();
  void resolveButtonsPressed();
  void activateRandomMole();
  void activateMole(int mole);
  void deactivateMole(int mole);
  int getRandomUnactiveMole();
  void addEvent(int mole, String functionName, int delayTime);
  void cancelEvent(int mole);
};

#endif
