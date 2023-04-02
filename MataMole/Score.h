#ifndef Score_h
#define Score_h
#define HIT 5

#include "Arduino.h"

class Score
{
public:
  Score();
  void hit();
  void miss();
  void fail();
  int read();
private:
    static const unsigned int MOLE = 5;
    static const unsigned int MOLE_INC_AMOUNT = 1;
    static const unsigned int MOLE_INC_EACH_HITS = 5;
    static const unsigned int MOLE_MINIUM_VALUE = 1;
    static const int COMBO_MISS_PENALTY = 2;
    unsigned short int score;
    short int combo;
    short int comboBonus;
    void updateComboBonus();
};

#endif
