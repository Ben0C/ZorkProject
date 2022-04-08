#include "item.h"
Item::Item (string inDescription, int inWeightGrams, int inDmg, int inHealing, bool isWeapon, bool isThrowable)
    :description(inDescription), weightGrams(inWeightGrams), dmg(inDmg), healing(inHealing), weaponCheck(isWeapon), throwableCheck(isThrowable)
{
    if(weaponCheck)
    {
        description += " *WEAPON*";
        longDescription = ("name: " + description
                           + ".\nweight: " + std::to_string(weightGrams)
                           + ".\ndmg: " + std::to_string(dmg)
                           + ".\n------------------------------------");
    } else if(throwableCheck) {
        description += " *THROWABLE*";
        longDescription = ("name: " + description
                           + ".\nweight: " + std::to_string(weightGrams)
                           + ".\ndmg: " + std::to_string(dmg)
                           + ".\n------------------------------------");
    } else if(healing > 0 && !weaponCheck) {
        description += " *CONSUMEABLE*";
        longDescription = ("name: " + description
                           + ".\nweight: " + std::to_string(weightGrams)
                           + ".\nhealing: " + std::to_string(healing)
                           + ".\n------------------------------------");
    }
}

Item::Item(const Item& item)
    :description(item.description), weightGrams(item.weightGrams), dmg(item.dmg), healing(item.healing), weaponCheck(item.weaponCheck)
{
    if(weaponCheck)
    {
        longDescription = ("name: " + description
                           + ".\nweight: " + std::to_string(weightGrams)
                           + ".\ndmg: " + std::to_string(dmg)
                           + ".\n------------------------------------");
    } else if(dmg > 0 && !weaponCheck) {
        longDescription = ("name: " + description
                           + ".\nweight: " + std::to_string(weightGrams)
                           + ".\ndmg: " + std::to_string(dmg)
                           + ".\n------------------------------------");
    } else if(healing > 0 && !weaponCheck) {
        longDescription = ("name: " + description
                           + ".\nweight: " + std::to_string(weightGrams)
                           + ".\nhealing: " + std::to_string(healing)
                           + ".\n------------------------------------");
    }
}


void Item::setWeight(int inWeightGrams)
{
    if (inWeightGrams > 9999 || inWeightGrams < 0)
       cout << "weight invalid, must be 0<weight<9999" ;
    else
	   weightGrams = inWeightGrams;
}

string Item::getShortDescription()
{
	return description;
}

string Item::getLongDescription()
{
    return longDescription;
}

int Item::getWeight()
{
    return weightGrams;
}

int Item::getDmg()
{
    return dmg;
}

int Item::getHealing()
{
    return healing;
}

int Item::getWeaponCheck()
{
    return weaponCheck;
}


