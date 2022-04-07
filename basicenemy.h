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
    BasicEnemy();
    void slain();
};

#endif // BASICENEMY_H
