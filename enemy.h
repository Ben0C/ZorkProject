#ifndef ENEMY_H
#define ENEMY_H

#include <string>
using namespace std;
#include <vector>
using std::vector;

class Enemy
{
protected:
    string name;
    string description;
    string longDescription;
    int health;
    int maxHealth;
    int dmg;
    int expGain;
    string type;

public:
    Enemy(string inName = "unknown", string inDescription = "unknown", int inHealth = 1, int inDmg = 1, int inExpGain = 0);
    inline static int numOfEnemies;
    static int getNumOfEnemies();
    static void setNumOfEnemies(int num);

    void reduceHealth(int atkDmg);
    string getName();
    string getDescription();
    string getLongDescription();
    int getHealth();
    int getMaxHealth();
    int getDmg();
    int getExpGain();
    string getType();
    void setName(string name);
    void setDescription(string description);
    void setHealth(int health);
    void setDmg(int dmg);
    void setExpGain(int expGain);
    virtual void slain();
};

#endif // ENEMY_H
