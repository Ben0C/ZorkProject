#ifndef ENEMY_H
#define ENEMY_H

#include <string>
using namespace std;
#include <vector>
using std::vector;

class Enemy
{
private:
    static int numOfEnemies;
    int health;
    int dmg;
    int expGain;

public:
    Enemy();
    void slain();
};

class Boss
{

};


#endif // ENEMY_H
