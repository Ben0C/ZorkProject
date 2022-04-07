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

public:
    Item (string description = "unknown", int inWeight = 5, int dmg = 1, bool isWeapon = false);
    Item (const Item& item);
	string getShortDescription();
    string getLongDescription();
	int getWeight();
	void setWeight(int weightGrams);
    //float getValue();
    //void setValue(float value);
	int getWeaponCheck();
    //void setWeaponCheck(bool weaponCheck);
    bool operator == (Item item)
    {
        if(weightGrams == item.getWeight() && weaponCheck == item.getWeaponCheck() && description == item.getShortDescription())
            return true;
        else
            return false;
    }
};

#endif /*ITEM_H_*/
