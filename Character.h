#ifndef CHARACTER_H_
#define CHARACTER_H_
#include "item.h"

#include <string>
using namespace std;
#include <vector>
using std::vector;


class Character {
private:
    string description;
    vector <Item> itemsInCharacter;
    int health;
    Item weapon;

public:
    Character(string description = "no description given", int health = 5, Item weapon = Item("stick", 1, 1, true));
    ~Character();
	string shortDescription();
	string longDescription();
    void addItems(Item &item);
    void addItems(Item *item);
    void removeItem(int arrNum);
    string equipWeapon(int arrNum);
    vector<Item> getItems();
    int getHealth();
    Item getWeapon();
    void setHealth(int health);
    void setWeapon(Item weapon);
};

#endif CHARACTER_H_
