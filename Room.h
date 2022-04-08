#ifndef ROOM_H_
#define ROOM_H_

#include <map>
#include <string>
#include <vector>
#include "enemy.h"
#include "basicenemy.h"
#include "boss.h"
#include "item.h"
using namespace std;
using std::vector;

class Room {

private:
	string description;
	map<string, Room*> exits;
	string exitString();
    vector <Item> itemsInRoom;
    Enemy enemy;
    Enemy* ptrEnemy;
    bool hasEnemy;



public:
    int numberOfItems();
    Room(string description = "no description given");
    ~Room();
	void setExits(Room *north, Room *east, Room *south, Room *west);
    void setEnemy(Enemy enemy);
    void removeEnemy();
    bool checkForEnemy();
    Enemy* getEnemy();
    string shortDescription();
    string longDescription();
	Room* nextRoom(string direction);
    void addItem(Item *inItem);
    void addItem(Item inItem);
    void removeItem(int arrNum);
    string displayItem();
    int isItemInRoom(string inString);
    vector <Item> getItems();
    //void removeItemFromRoom(int location);
    friend void output_description(Room room);

};

#endif
