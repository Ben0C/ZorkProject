#ifndef ROOM_H_
#define ROOM_H_

#include <map>
#include <string>
#include <vector>
#include "item.h"
using namespace std;
using std::vector;

class Room {

private:
	string description;
	map<string, Room*> exits;
	string exitString();
    vector <Item> itemsInRoom;


public:
    int numberOfItems();
    Room(string description = "no description given");
	void setExits(Room *north, Room *east, Room *south, Room *west);
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
