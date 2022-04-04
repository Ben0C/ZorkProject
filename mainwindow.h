#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Room.h"
#include "enemy.h"
#include "boss.h"
#include "item.h"


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
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;

    //Zork parts
    vector<Room*> rooms;
    Room *currentRoom;
    int state; //0 move, 1 fight,
    Room* randomRoom();
    void moveState();
    void fightState();
    void createRooms();
    void setShortcuts();
    void printWelcome();
    void printHelp();
    void goRoom(string direction);
    void createItems();
    void displayItems();
    friend Room output(MainWindow mainwindow);
};
#endif // MAINWINDOW_H
