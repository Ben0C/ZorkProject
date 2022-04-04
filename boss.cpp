#include "boss.h"

Boss::Boss(int phases)
    :phases(phases)
{
    numOfBosses++;
}

void Boss::slain()
{
    numOfEnemies--;
    numOfBosses--;
}

int Boss::getNumOfBosses()
{
    return numOfBosses;
}

void Boss::setNumOfBosses(int num)
{
    numOfBosses = num;
}
