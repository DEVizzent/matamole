
#include "GameMole.h"
#include "ScoreDisplay.h"
#include "LedManager.h"
#include "ButtonManager.h"
#include "arduino-timer.h"
enum LoopAction {initGame, startGame, game, endGame, waiting};
LoopAction loopAction;
ScoreDisplay scoreDisplay;
LedManager ledManager;
ButtonManager buttonManager;
GameMole gameMole;
int score = 0;
int difficulty = 0;
Timer<> timer;
Timer<>::Task events[NUMBER_OF_MOLES];

void setup ()
{
  Serial.begin(9600);
  loopAction = waiting;
  activateWaiting();
  scoreDisplay = ScoreDisplay(13, 12, 11);
  int analogicPin5 = A5;
  ledManager = LedManager(23, 25, 27, 29, 31, 33, 35, 37, 39, 41);
  buttonManager = ButtonManager(22, 24, 26, 28, 30, 32, 34, 36, 38, 40);
  gameMole = GameMole(buttonManager, ledManager, &scoreDisplay);
  timer.every(5, displayScore);
}
bool displayScore(){
  scoreDisplay.displayScore();
}
void gameLoop() {
  gameMole.loop();
  manageGameMoleEvents();
}

void initLoop() {
  cleanGameMoleEvents();
  ledManager.disableAll();
  gameMole.initialize(difficulty);
  timer.every(3000, updateNumberOfActiveMoles);
  timer.in(30000, finishGame);
}

void endLoop() {
  cleanGameMoleEvents();
  gameMole.finishGame();
}

void waitingLoop() {
  difficulty = buttonManager.getButtonPressed();
  if (difficulty < 5) {
    loopAction = initGame;
  }
}


void loop() {
  timer.tick();
    switch (loopAction) {
        case initGame:
            initLoop();
            loopAction = startGame;
            break;
        case startGame:
            loopAction = game;
            break;
        case game:
            gameLoop();
            break;
        case endGame:
            endLoop();
            delay(1000);
            loopAction = waiting;
            activateWaiting();
            break;
        case waiting:
            waitingLoop();
            break;
    }
}
//Game functions

void manageGameMoleEvents() {
  for(int i = 0; i < NUMBER_OF_MOLES; i++) {
    if (gameMole.readActionEvent(i).equals("")) {
      continue;
    }
    if (gameMole.readActionEvent(i).equals("cancel")) {
      timer.cancel(events[i]);
      gameMole.cleanActionEvent(i);
      continue;
    }
    if (gameMole.readActionEvent(i).equals("missMole")) {
      events[i] = timer.in(gameMole.readTimerEvent(i), missMole, i);
      gameMole.cleanActionEvent(i);
      continue;
    }
    if (gameMole.readActionEvent(i).equals("finishMissMole")) {
      events[i] = timer.in(gameMole.readTimerEvent(i), finishMissMole, i);
      gameMole.cleanActionEvent(i);
      continue;
    }
  }
}


void cleanGameMoleEvents() {
  for(int i = 0; i < NUMBER_OF_MOLES; i++) {
    timer.cancel(events[i]);
    gameMole.cleanActionEvent(i);
  }
}

bool missMole(int mole) {
  gameMole.missMole(mole); 
  return false;
}

bool updateNumberOfActiveMoles() {
  gameMole.updateNumberOfActiveMoles();
  return true;
}

bool finishMissMole(int mole) {
  gameMole.finishMissMole(mole);
  return false;
}

bool finishGame() {
  loopAction = endGame;
  timer.cancel();
  timer.every(5, displayScore);
  return false;
}

// WaitingFunctions
void activateWaiting() {
  for(int i = 0; i < NUMBER_OF_MOLES; i++) {
    events[i] = timer.in(200*i, activateToggle, i);
  }
}

bool activateToggle(int led) {
  events[led] = timer.every(200*NUMBER_OF_MOLES, toggleLed, led);
  return false;
}

bool toggleLed(int led) {
  ledManager.toggle(led);
  return true;
}
