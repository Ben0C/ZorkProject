#ifndef BASICENEMY_H
#define BASICENEMY_H

#include "enemy.h"
#include "alive.h"

class BasicEnemy : public Enemy, public Alive
{
private:
        bool Alive;


public:
    inline static int numOfBasicEnemies;
    static int getNumOfBasicEnemies();
    static void setNumOfBasicEnemies(int num);

    BasicEnemy(string inName = "unknown", string inDescription = "unknown", int inHealth = 1, int inDmg = 1, int inExpGain = 0);
    void slain();
    void isAlive();
};

#endif // BASICENEMY_H
