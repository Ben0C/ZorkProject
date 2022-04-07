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

    string getName();
    string getDescription();
    int getHealth();
    int getDmg();
    int getExpGain();
    void setName(string name);
    void setDescription(string description);
    void setHealth(int health);
    void setDmg(int dmg);
    void setExpGain(int expGain);

    Enemy(string name = "unknown", string description = "unknown", int health = 1, int dmg = 1, int expGain = 0);
    virtual void slain();
};

#endif // ENEMY_H
