#include "Score.h"

Score::Score() {
    score = 0;
    combo = 0;
    comboBonus = 1.0;
}
void Score::hit() {
    score += MOLE + comboBonus;
    combo++;
    updateComboBonus();
}
void Score::miss()
{
    combo -= COMBO_MISS_PENALTY;
    updateComboBonus();
}
void Score::fail() 
{
    if (combo <= 0) {
        combo -= (comboBonus <= -4)? 0 : COMBO_MISS_PENALTY;
        updateComboBonus();
        return;
    }
    combo = 0;
}
int Score::read()
{
    return score;
}
void Score::updateComboBonus()
{
    comboBonus = ( combo / MOLE_INC_EACH_HITS ) * MOLE_INC_AMOUNT;
};
