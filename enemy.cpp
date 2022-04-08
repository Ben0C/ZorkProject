#include "enemy.h"

Enemy::Enemy(string inName, string inDescription, int inHealth, int inDmg, int inExpGain)
    :name(inName), description(inDescription), health(inHealth), dmg(inDmg), expGain(inExpGain)
{  
    numOfEnemies++;
    longDescription = (this->name + "\natk: " + to_string(this->dmg) + "\n\n" + description);
    maxHealth = inHealth;
}

void Enemy::slain()
{
    numOfEnemies--;
}

void Enemy::reduceHealth(int atkDmg){
    health -= atkDmg;
}

//mutator methods -------------------------

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

string Enemy::getLongDescription()
{
    return longDescription;
}

int Enemy::getHealth()
{
    return health;
}

int Enemy::getMaxHealth()
{
    return maxHealth;
}

int Enemy::getDmg()
{
    return dmg;
}
int Enemy::getExpGain()
{
    return expGain;
}

string Enemy::getType()
{
    return type;
}

void Enemy::setName(string name)
{
    this->name = name;
}

void Enemy::setDescription(string description)
{
    this->description = description;
}

void Enemy::setLongDescription(string inName, int inDmg, string inDescription)
{
        longDescription = (inName + "\natk: " + to_string(inDmg) + "\n\n" + inDescription);
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
