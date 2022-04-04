#ifndef ENEMY_H
#define ENEMY_H

#include <string>
using namespace std;
#include <vector>
using std::vector;

class Enemy
{
private:
    string name;
    string description;
    int health;
    int dmg;
    int expGain;

public:
    inline static int numOfEnemies;
    static int getNumOfEnemies();
    static void setNumOfEnemies(int num);

    Enemy(string name = "unknown", string description = "unknown", int health = 1, int dmg = 1, int expGain = 0);
    virtual void slain();
};

#endif // ENEMY_H
