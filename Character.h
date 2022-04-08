#ifndef CHARACTER_H_
#define CHARACTER_H_
#include "item.h"

#include <string>
using namespace std;
#include <vector>
using std::vector;


class Character
{
private:
    string description;
    vector <Item> itemsInCharacter;
    int health;
    int maxHealth;
    Item weapon;
    int dmg;

public:
    Character(string inDescription = "no description given", int inHealth = 5, Item inWeapon = Item("stick", 1, 1, true));
    ~Character();
	string shortDescription();
	string longDescription();
    void addItems(Item &item);
    void addItems(Item *item);
    void removeItem(int arrNum);
    void reduceHealth(int atkDmg);
    string equipWeapon(int arrNum);
    vector<Item> getItems();
    int getHealth();
    int getMaxHealth();
    Item getWeapon();
    int getDmg();
    void setHealth(int health);
    void setWeapon(Item weapon);
};

#endif CHARACTER_H_
