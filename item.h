#ifndef ITEM_H_
#define ITEM_H_

#include <map>
#include <string>
#include <iostream>
using namespace std;

class Item {
private:
	string description;
	string longDescription;
	int weightGrams;
    // value;
	bool weaponCheck;
    int dmg;
    int healing;

public:
    Item (string inDescription = "unknown", int inWeight = 5, int inDmg = 0, int inHealing = 0, bool isWeapon = false);
    Item (const Item& item);
	string getShortDescription();
    string getLongDescription();
	int getWeight();
	void setWeight(int weightGrams);
    int getDmg();
    int getHealing();
	int getWeaponCheck();
    bool operator == (Item item)
    {
        if(weightGrams == item.getWeight() && weaponCheck == item.getWeaponCheck() && description == item.getShortDescription())
            return true;
        else
            return false;
    }
};

#endif /*ITEM_H_*/
