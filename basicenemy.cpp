#include "basicenemy.h"

BasicEnemy::BasicEnemy()
{
    numOfBasicEnemies++;
}

void BasicEnemy::slain()
{
    numOfBasicEnemies--;
    numOfEnemies--;
}
