#include "Character.h"

Character::Character(string description)
    : description(description)
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



