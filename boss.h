#ifndef BOSS_H
#define BOSS_H

#include <string>
using namespace std;
#include "enemy.h"

class Boss : public Enemy
{
private:
    int phases;

public:
    inline static int numOfBosses;
    static int getNumOfBosses();
    static void setNumOfBosses(int num);

    Boss(int phases, string inName = "unknown", string inDescription = "unknown", int inHealth = 1, int inDmg = 1, int inExpGain = 0);
    void slain();
    int getPhases();
    void setPhases(int num);
};

#endif // BOSS_H
