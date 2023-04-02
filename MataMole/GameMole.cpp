#include "GameMole.h"

GameMole::GameMole(){}

GameMole::GameMole(ButtonManager bManager, LedManager lManager, ScoreDisplay sDisplay)
{
  buttonManager = bManager;
  ledManager = lManager;
  scoreDisplay = sDisplay;
  juicyTime = 200;
}

void GameMole::initialize(int dificulty)
{
  juicyTime = 500 / abs(dificulty - 5);
  score = Score();
}

bool GameMole::loop()
{
  buttonManager.readButtons();
  for(int i; i < NUMBER_OF_BUTTONS; i++) {
    if (buttonManager.hasBeenPressed(i)) {
      score.hit();
      ledManager.disable(i);
    }
  }
  scoreDisplay.updateScore(score.read());
  return true;
}
