#include "GameMole.h"

GameMole::GameMole(){}

GameMole::GameMole(ButtonManager bManager, LedManager lManager, ScoreDisplay *sDisplay)
{
  buttonManager = bManager;
  ledManager = lManager;
  scoreDisplay = sDisplay;
  juicyTime = 200;
  countActiveMoles = 0;
}

void GameMole::initialize(int difficulty)
{
  juicyTime = 500 / (difficulty + 1);
  moleTime = 5000 / (difficulty + 1);
  score = Score();
  hasToUpdateNumberOfActiveMoles = true;
  numberOfMolesMustBeActive = 2;
}

bool GameMole::loop()
{
  resolveButtonsPressed();
  scoreDisplay->updateScore(score.read());
  if (hasToUpdateNumberOfActiveMoles) {
    hasToUpdateNumberOfActiveMoles = false;
    numberOfMolesMustBeActive = generateNumberOfMolesMustBeActive();
    Serial.println(numberOfMolesMustBeActive);
  }
  if (numberOfMolesMustBeActive > countActiveMoles) {
    activateRandomMole();
  }
  return true;
}

void GameMole::resolveButtonsPressed()
{
  buttonManager.readButtons();
  countActiveMoles = 0;
  for(int i= 0; i < NUMBER_OF_MOLES; i++) {
    if (activeMoles[i]) countActiveMoles++;
    if (buttonManager.hasBeenPressed(i)) {
      if (activeMoles[i]) {
        score.hit();
        deactivateMole(i);
      } else {
        score.fail();
      }
    }
  }
}

void GameMole::activateRandomMole()
{
  int mole = getRandomUnactiveMole();
  if (mole == -1) return;
  activateMole(mole);
}
void GameMole::activateMole(int mole)
{
  activeMoles[mole] = true;
  ledManager.enable(mole);
  addEvent(mole, "missMole", moleTime);
}
void GameMole::deactivateMole(int mole)
{
  activeMoles[mole] = false;
  ledManager.disable(mole); 
  cancelEvent(mole);
  hasToUpdateNumberOfActiveMoles = true;
}
void GameMole::missMole(int mole)
{
  ledManager.disable(mole);
  addEvent(mole, "finishMissMole", juicyTime);
}
void GameMole::finishMissMole(int mole)
{
  activeMoles[mole] = false;
  score.miss();
  hasToUpdateNumberOfActiveMoles = true;
}

int GameMole::generateNumberOfMolesMustBeActive()
{
  randomNumber = random(0,100);
  Serial.println(randomNumber);
  if (randomNumber < 15) {
    return 0;
  }
  if (randomNumber < 40) {
    return 1;
  }
  if (randomNumber < 85) {
    return 2;
  }
  if (randomNumber < 95) {
    return 3;
  }
  return 4;
}

int GameMole::getRandomUnactiveMole() 
{
  for (int i = 0; i < 3; i++) {
    int mole = random(0, (NUMBER_OF_MOLES - 1));
    if (activeMoles[mole] == true) {
      continue;
    }
    return mole;
  }
  return -1;
}
void GameMole::updateNumberOfActiveMoles() 
{
  hasToUpdateNumberOfActiveMoles = true;
}
void GameMole::addEvent(int mole, String functionName, int delayTime)
{
  moleEvent[mole] = functionName;
  moleEventTimer[mole] = delayTime;
}
void GameMole::cancelEvent(int mole) 
{
  moleEvent[mole] = "cancel";
}
void GameMole::finishGame() 
{
  for(int i= 0; i < NUMBER_OF_MOLES; i++) {
    deactivateMole(i);
  }
}
String GameMole::readActionEvent(int mole) 
{
  return moleEvent[mole];
}
int GameMole::readTimerEvent(int mole)
{
  return moleEventTimer[mole];
}

void GameMole::cleanActionEvent(int mole) 
{
  moleEvent[mole] = "";
  moleEventTimer[mole] = 0;
}
