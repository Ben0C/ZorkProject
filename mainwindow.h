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
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

using std::ifstream;

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

    void on_inventoryButton_clicked();

private:
    Ui::MainWindow *ui;

    //Zork parts

    vector<Room*> rooms;
    vector<Item> charItems;
    Room *currentRoom;
    Room *previousRoom;
    Boss *floorBoss;
    int currentItem;
    int currentLetter;
    Enemy *currentEnemy;
    string directionToMove;
    QString enemyName;
    QString charDmg;
    int battleTurn;

    //wordle parts
    Character mainChar;
    char letters[26];
    string wordleWords[6];
    vector<string> previousGuesses;
    string currentGuess;
    int currentWord;
    string displayPreviousGuesses();
    void compareWords();

    void createRooms();
    void setShortcuts();
    void printWelcome();
    void showRoomDetails();
    void moveCharIcon(string direction);
    void goRoom(string direction);
    void selectItems(int numOfItems);
    void showInventory();
    void atkEnemy(int dmg = 0);
    void useItem(Item item);
    void heal(Item item);
    void displayItems();
    void displayLetters();
    friend Room output(MainWindow mainwindow);

    //states
    int state; //0 move, 1 fight, 2 inventory, 3 selecting items
    void moveState();
    void fightState();
    void inventoryState();
    void gameOverState();
    void battleInventoryState();
    void wordleState();
};




#endif // MAINWINDOW_H
