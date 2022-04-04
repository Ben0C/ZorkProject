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
    Character(string description = "no description given");
	string shortDescription();
	string longDescription();
    void addItems(Item &item);
    void addItems(Item *item);
};

#endif CHARACTER_H_
