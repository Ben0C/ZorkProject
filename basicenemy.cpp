#include "basicenemy.h"

BasicEnemy::BasicEnemy(string inName, string inDescription, int inHealth, int inDmg, int inExpGain)
    :Enemy(inName, inDescription, inHealth, inDmg, inExpGain)
{
    numOfBasicEnemies++;
    this->type = "basic enemy";
}

void BasicEnemy::slain()
{
    numOfBasicEnemies--;
    numOfEnemies--;
}


