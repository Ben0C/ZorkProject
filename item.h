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
	float value;
	bool weaponCheck;

public:
    Item (string description, int inWeight = 5, float inValue = 5, bool isWeapon = false);
    Item (const Item& item);
	string getShortDescription();
    string getLongDescription();
	int getWeight();
	void setWeight(int weightGrams);
	float getValue();
	void setValue(float value);
	int getWeaponCheck();
    //void setWeaponCheck(bool weaponCheck);
    bool operator == (Item item)
    {
        if(weightGrams == item.getWeight() && value == item.getValue() && weaponCheck == item.getWeaponCheck() && description == item.getShortDescription())
            return true;
        else
            return false;
    }
};

#endif /*ITEM_H_*/
