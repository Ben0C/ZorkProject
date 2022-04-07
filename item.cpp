#include "item.h"
Item::Item (string inDescription, int inWeightGrams, int inDmg, bool isWeapon)
    :description(inDescription), weightGrams(inWeightGrams), dmg(inDmg), weaponCheck(isWeapon)
{
    if(weaponCheck)
    {
        description += " *WEAPON*";
        longDescription = ("name: " + description
                           + ".\nweight: " + std::to_string(weightGrams)
                           + ".\ndmg: " + std::to_string(dmg)
                           + "------------------------------------");
    }
    else
    {
        description += " *ITEM*";
        longDescription = ("name: " + description
                           + ".\nweight: " + std::to_string(weightGrams)
                           + "------------------------------------");
    }
}

Item::Item(const Item& item)
    :description(item.description), weightGrams(item.weightGrams), weaponCheck(item.weaponCheck), dmg(item.dmg)
{
    if(weaponCheck)
    {
        longDescription = ("name: " + description
                           + ".\nweight: " + std::to_string(weightGrams)
                           + ".\ndmg: " + std::to_string(dmg));
    }
    else
    {
        longDescription = ("name: " + description
                           + ".\nweight: " + std::to_string(weightGrams));
    }
}


void Item::setWeight(int inWeightGrams)
{
    if (inWeightGrams > 9999 || inWeightGrams < 0)
       cout << "weight invalid, must be 0<weight<9999" ;
    else
	   weightGrams = inWeightGrams;
}

/*
void Item::setValue(float inValue)
{
    if (inValue > 9999 || inValue < 0)
       cout << "value invalid, must be 0<value<9999" ;
    else
	   value = inValue;
}
*/

/*
void Item::setWeaponCheck(bool isWeapon)
{
    if(isWeapon)
    {
        weaponCheck = true;
        description += "\n*WEAPON*";
    }
    else
    {
        description += "\n*ITEM*";
    }

}
*/

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

/*
float Item::getValue()
{
    return value;
}
*/

int Item::getWeaponCheck()
{
    return weaponCheck;
}


