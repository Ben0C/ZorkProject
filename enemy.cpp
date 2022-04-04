#include "enemy.h"

Enemy::Enemy(string name, string description, int health, int dmg, int expGain)
    :name(name), description(description), health(health), dmg(dmg), expGain(expGain)
{  
}

void Enemy::slain()
{
    numOfEnemies--;
}

int Enemy::getNumOfEnemies()
{
    return numOfEnemies;
}

void Enemy::setNumOfEnemies(int num)
{
    numOfEnemies = num;
}
