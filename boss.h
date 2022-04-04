#ifndef BOSS_H
#define BOSS_H

#include "enemy.h"

class Boss : public Enemy
{
private:
    int phases;

public:
    inline static int numOfBosses;
    static int getNumOfBosses();
    static void setNumOfBosses(int num);

    Boss(int phases);
    void slain();
};

#endif // BOSS_H
