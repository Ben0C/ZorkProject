#include "Character.h"

Character::Character(string inDescription, int inHealth, Item inWeapon)
    : description(inDescription), health(inHealth), weapon(inWeapon)
{
    dmg = weapon.getDmg();
    maxHealth = inHealth;
}

Character::~Character()
{

}

void Character::addItems(Item &item) {
    itemsInCharacter.push_back(item);
}

void Character::addItems(Item *item)
{
    itemsInCharacter.push_back(*item);
    delete item;
}

void Character::removeItem(int arrNum)
{
    itemsInCharacter.erase(itemsInCharacter.begin() + arrNum);
}

void Character::reduceHealth(int atkDmg){
    health -= atkDmg;
}

string Character::equipWeapon(int arrNum)
{
    if(arrNum >= 0 && arrNum < itemsInCharacter.size())
    {
        if(itemsInCharacter[arrNum].getWeaponCheck())
        {
            itemsInCharacter.push_back(getWeapon());
            setWeapon(itemsInCharacter[arrNum]);
            dmg = itemsInCharacter[arrNum].getDmg();
            itemsInCharacter.erase(itemsInCharacter.begin() + arrNum);
            return getWeapon().getShortDescription() + " equipped";
        }else{
            return "This item is not a weapon";
        }
    }
}

string Character::shortDescription()
{
    return this->description;
}

string Character::longDescription()
{
  string ret = this->description;
  ret += "\nItem list:\n";
  for (vector<Item>::iterator i = itemsInCharacter.begin(); i != itemsInCharacter.end(); i++)
    ret += "\t"+ (*i).getLongDescription() + "\n";
  return ret;
}

//mutator methods----------------------------------------------

int Character::getHealth()
{
    return health;
}

int Character::getMaxHealth()
{
    return maxHealth;
}

Item Character::getWeapon()
{
    return weapon;
}

int Character::getDmg()
{
    return dmg;
}

vector<Item> Character::getItems()
{
    return itemsInCharacter;
}

void Character::setHealth(int health)
{
    this->health = health;
}

void Character::setWeapon(Item weapon)
{
    this->weapon = weapon;
}






