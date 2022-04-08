#ifndef BOSS_H
#define BOSS_H

#include <string>
using namespace std;
#include "enemy.h"
#include "alive.h"

class Boss : public Enemy, public Alive
{
private:
    int phases;
    bool alive;

public:
    inline static int numOfBosses;
    static int getNumOfBosses();
    static void setNumOfBosses(int num);

    Boss(int phases, string inName = "unknown", string inDescription = "unknown", int inHealth = 1, int inDmg = 1, int inExpGain = 0);
    void slain();
    void isAlive();
    int getPhases();
    void setPhases(int num);
};

#endif // BOSS_H
