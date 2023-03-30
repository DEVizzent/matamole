
#include "ScoreDisplay.h"
#include "LedManager.h"
#include "ButtonManager.h"
#include "arduino-timer.h"
enum LoopAction {initGame, startGame, game, endGame};
LoopAction loopAction;
ScoreDisplay scoreDisplay;
LedManager ledManager;
ButtonManager buttonManager;
int score = 0;
Timer<> timer;

void setup ()
{
  Serial.begin(9600);
  loopAction = initGame;
  scoreDisplay = ScoreDisplay(13, 12, 11);
  int analogicPin5 = A5;
  ledManager = LedManager(analogicPin5, 2, 3, 4, 5);
  buttonManager = ButtonManager(6, 7, 8, 9, 10);
  timer.every(5, displayScore);
}
bool displayScore(){
  scoreDisplay.displayScore();
}
void gameLoop() {
  buttonManager.readButtons();
  for(int i; i < NUMBER_OF_BUTTONS; i++) {
    if (buttonManager.hasBeenPressed(i)) {
      Serial.println(i);
      score++;
      ledManager.disable(i);
    }
  }
  scoreDisplay.updateScore(score);
}

void initLoop() {
  scoreDisplay.updateScore(22);
  ledManager.enable(0);
  ledManager.enable(1);
  ledManager.enable(2);
  ledManager.enable(3);
  ledManager.enable(4);
}


void loop() {
  timer.tick();
    switch (loopAction) {
        case initGame:
            Serial.println("Init");
            initLoop();
            loopAction = startGame;
            break;
        case startGame:
            Serial.println("Start Game");
            loopAction = game;
            break;
        case game:
            gameLoop();
            break;
        case endGame:
            Serial.println("EndGame");
            break;
    }
}
