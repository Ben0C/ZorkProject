#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Room.h"
#include "boss.h"
#include "basicenemy.h"
#include "Character.h"

#include <QProgressBar>
#include <QPixmap>
#include <QShortcut>
#include <QPixmap>
#include <QShortcut>
#include <QObject>
#include <iostream>
#include <string>
using namespace std;

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_northButton_clicked();

    void on_southButton_clicked();

    void on_eastButton_clicked();

    void on_westButton_clicked();

    void on_pickUpButton_clicked();

    void on_InventoryButton_clicked();

private:
    Ui::MainWindow *ui;

    //Zork parts
    Character mainChar;
    vector<Room*> rooms;
    vector<Item> charItems;
    Room *currentRoom;
    Room *previousRoom;
    Boss *floorBoss;
    int currentItem;
    Enemy *currentEnemy;
    QString enemyName;
    QString charDmg;
    int battleTurn;
    int state; //0 move, 1 fight, 2 inventory, 3 selecting items
    Room* randomRoom();
    void createRooms();
    //void setShortcuts();
    void printWelcome();
    void showRoomDetails();
    QString getRoomDetails();
    void printHelp();
    void goRoom(string direction);
    //void createItems();
    void selectItems(int numOfItems);
    void showInventory();
    QString getInventory();
    void atkEnemy(int dmg = 0);
    void useItem(Item item);
    void heal(Item item);
    void displayItems();
    friend Room output(MainWindow mainwindow);

    //states
    void moveState();
    void fightState();
    void inventoryState();
    void gameOverState();
    void battleInventoryState();
};



#endif // MAINWINDOW_H
