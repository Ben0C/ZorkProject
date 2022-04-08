#include "boss.h"

Boss::Boss(int phases, string inName, string inDescription, int inHealth, int inDmg, int inExpGain)
    :Enemy(inName, inDescription, inHealth, inDmg, inExpGain), phases(phases)
{
    numOfBosses++;
    this->type = "boss";
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

int Boss::getPhases()
{
    return phases;
}

void Boss::setPhases(int num)
{
    phases = num;
}

void Boss::isAlive()
{
    alive = true;
}
