#include "item.h"
Item::Item (string inDescription, int inWeightGrams, float inValue, bool isWeapon)
    :description(inDescription), weightGrams(inWeightGrams), value(inValue), weaponCheck(isWeapon)
{
    if(isWeapon)
    {
        description += "\n*WEAPON*";
    }
    else
    {
        description += "\n*ITEM*";
    }
}

Item::Item(const Item& item)
    :description(item.description), weightGrams(item.weightGrams), value(item.value), weaponCheck(item.weaponCheck)
{
}


void Item::setWeight(int inWeightGrams)
{
    if (inWeightGrams > 9999 || inWeightGrams < 0)
       cout << "weight invalid, must be 0<weight<9999" ;
    else
	   weightGrams = inWeightGrams;
}

void Item::setValue(float inValue)
{
    if (inValue > 9999 || inValue < 0)
       cout << "value invalid, must be 0<value<9999" ;
    else
	   value = inValue;
}

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
	return " item(s), " + description + ".\n";
}

int Item::getWeight()
{
    return weightGrams;
}

float Item::getValue()
{
    return value;
}

int Item::getWeaponCheck()
{
    return weaponCheck;
}


