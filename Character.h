#ifndef CHARACTER_H_
#define CHARACTER_H_
#include "mainwindow.h"

#include <string>
using namespace std;
#include <vector>
using std::vector;


class Character {
private:
	string description;
    vector <Item> itemsInCharacter;
public:
    void addItems(Item *item);




public:
    Character(string description = "no description given");
	string shortDescription();
	string longDescription();

};

#endif CHARACTER_H_
