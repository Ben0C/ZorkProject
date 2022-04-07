#include "enemy.h"

Enemy::Enemy(string name, string description, int health, int dmg, int expGain)
    :name(name), description(description), health(health), dmg(dmg), expGain(expGain)
{  
    numOfEnemies++;
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

string Enemy::getName()
{
    return name;
}

string Enemy::getDescription()
{
    return description;
}

int Enemy::getHealth()
{
    return health;
}

int Enemy::getDmg()
{
    return dmg;
}
int Enemy::getExpGain()
{
    return expGain;
}

void Enemy::setName(string name)
{
    this->name = name;
}

void Enemy::setDescription(string description)
{
    this->description = description;
}

void Enemy::setHealth(int health)
{
    this->health = health;
}

void Enemy::setDmg(int dmg)
{
    this->dmg = dmg;
}

void Enemy::setExpGain(int expGain)
{
    this->expGain = expGain;
}
