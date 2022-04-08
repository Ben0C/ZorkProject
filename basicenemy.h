#ifndef BASICENEMY_H
#define BASICENEMY_H

#include "enemy.h"

class BasicEnemy : public Enemy
{
private:

public:
    inline static int numOfBasicEnemies;
    static int getNumOfBasicEnemies();
    static void setNumOfBasicEnemies(int num);

    BasicEnemy(string inName = "unknown", string inDescription = "unknown", int inHealth = 1, int inDmg = 1, int inExpGain = 0);
    void slain();
};

#endif // BASICENEMY_H
