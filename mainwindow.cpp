#include <iostream>
using namespace std;

#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap pix("C:/Users/benoc/Documents/ZorkProject/Images/glep.png");
    ui->label->setPixmap(pix.scaled(371, 521, Qt::KeepAspectRatio));

    Enemy::setNumOfEnemies(0);
    Boss::setNumOfBosses(0);
    mainChar = Character("You", 50);
    createRooms();
    moveState();
    printWelcome();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createRooms()  {
    Room *a, *b, *c, *d, *e, *f, *g, *h, *i, *j;


    a = new Room();
        a->addItem(new Item("weapon", 1, 10, true));
        //a->addItem(new Item("y", 2, 22, false));
    b = new Room("b");
        b->addItem(new Item("x1", 3, 0, false));
        b->addItem(new Item("y1", 4, 0, false));
    c = new Room("c");
        c->addItem(new Item("x2", 3, 0, false));
        c->addItem(new Item("y2", 4, 0, false));
        c->addItem(new Item("z2", 4, 0, false));
    d = new Room("d");
        d->addItem(new Item("x3", 3, 0, false));
        d->addItem(new Item("y3", 4, 0, false));
        d->addItem(new Item("z3", 4, 0, false));
        d->addItem(new Item("q3", 4, 0, false));
    e = new Room("e");
    f = new Room("f");
    g = new Room("g");
    h = new Room("h");
    i = new Room("i");
    j = new Room("j");


//             (N, E, S, W)
    a->setExits(f, b, d, c);
    b->setExits(NULL, NULL, NULL, a);
    c->setExits(NULL, a, NULL, NULL);
    d->setExits(a, e, NULL, i);
    e->setExits(NULL, NULL, NULL, d);
    f->setExits(NULL, g, a, h);
    g->setExits(NULL, NULL, NULL, f);
    h->setExits(NULL, f, NULL, NULL);
    i->setExits(NULL, d, NULL, j);
    j->setExits(NULL, i, NULL, NULL);

    rooms = {a, b, c, d, e, f, g, h, i, j};
    currentRoom = a;

    //example of a reference to a room
    Room & refToRoom = *currentRoom;
}

/*
void MainWindow::setShortcuts(){
    QShortcut w(QKeySequence('w'), ui->pushButton);
    QShortcut s(QKeySequence('s'), ui->pushButton_2);
    QShortcut d(QKeySequence('d'), ui->pushButton_3);
    QShortcut a(QKeySequence('a'), ui->pushButton_4);

     //QObject::connect(w, SIGNAL(activated()), ui->pushButton, SLOT(on_pushButton_clicked()));
}
*/

inline void MainWindow::printWelcome() {
    ui->textEdit->setText("start \ninfo for help \n\n" +
                          QString::fromStdString(currentRoom->longDescription()) + "\n");
}

inline void MainWindow::printRoomDetails()
{
    ui->textEdit->setText(QString::fromStdString(currentRoom->longDescription()));
}

void MainWindow::goRoom(string direction) {

    // Try to leave current room.
    Room* nextRoom = currentRoom->nextRoom(direction);

    if (nextRoom == NULL)
        ui->textEdit->setText("You cannot go that way\n\n" + QString::fromStdString(currentRoom->longDescription()));
    else {
        currentRoom = nextRoom;
        printRoomDetails();
    }
}


template<typename T>
T templateTest(T x, T y){
    T temp;
    temp = x;
    x = y;
    y = temp;
    T & reference = temp;
}

void MainWindow::showInventory()
{
    string itemList = "";
    for(int i = 0; i < charItems.size(); i++)
    {
        if(i == currentItem){
            itemList += "->";
        }
        itemList += ("  " + (charItems[i]).getShortDescription() + "\n");
    }
    ui->textEdit->setText(QString::fromStdString(itemList));
}

void MainWindow::selectItems(int numOfItems)
{
    switch (numOfItems){
        case 0:
            break;
        case 1:
            state = 31;
            ui->northButton->setText(QString::fromStdString((currentRoom->getItems())[0].getShortDescription()));
            ui->southButton->setText("");
            ui->eastButton->setText("");
            ui->westButton->setText("");
            break;
        case 2:
            state = 32;
            ui->northButton->setText("");
            ui->southButton->setText("");
            ui->eastButton->setText(QString::fromStdString((currentRoom->getItems())[1].getShortDescription()));
            ui->westButton->setText(QString::fromStdString((currentRoom->getItems())[0].getShortDescription()));
            break;
        case 3:
            state = 33;
            ui->northButton->setText(QString::fromStdString((currentRoom->getItems())[0].getShortDescription()));
            ui->southButton->setText("");
            ui->eastButton->setText(QString::fromStdString((currentRoom->getItems())[2].getShortDescription()));
            ui->westButton->setText(QString::fromStdString((currentRoom->getItems())[1].getShortDescription()));
            break;
        default:
            state = 34;
            ui->northButton->setText(QString::fromStdString((currentRoom->getItems())[0].getShortDescription()));
            ui->southButton->setText(QString::fromStdString((currentRoom->getItems())[3].getShortDescription()));
            ui->eastButton->setText(QString::fromStdString((currentRoom->getItems())[2].getShortDescription()));
            ui->westButton->setText(QString::fromStdString((currentRoom->getItems())[1].getShortDescription()));
    }
}

void MainWindow::hideInventory()
{

}



//Button States ---------------------------

void MainWindow::moveState()
{
    state = 0;
    ui->northButton->setText("North");
    ui->southButton->setText("South");
    ui->eastButton->setText("East");
    ui->westButton->setText("West");
    ui->InventoryButton->setText("Inventory");
    ui->pickUpButton -> setText("Pick Up");
}

void MainWindow::fightState()
{
    state = 1;
    ui->northButton->setText("Attack");
    ui->southButton->setText("Run");
    ui->eastButton->setText("Inspect");
    ui->westButton->setText("Item");
}

void MainWindow::inventoryState()
{
    state = 2;
    ui->northButton->setText("Up");
    ui->southButton->setText("Down");
    ui->eastButton->setText("Equip");
    ui->westButton->setText("Inspect");
    ui->InventoryButton->setText("Close Inventory");
    ui->pickUpButton -> setText("Drop");
}

//Buttons -------------------------

//north, attack, up
void MainWindow::on_northButton_clicked()
{
    switch (state)
    {
        case 0:
            goRoom("north");
            break;
        case 1:
            //add code here
            break;
        case 2:
            if(currentItem > 0) currentItem--;
            showInventory();
            break;
        case 31:
            mainChar.addItems((currentRoom->getItems())[0]);
            currentRoom->removeItem(0);
            moveState();
            printRoomDetails();
            break;
        case 32:
            //blank
            break;
        case 33:
            mainChar.addItems((currentRoom->getItems())[0]);
            currentRoom->removeItem(0);
            moveState();
            printRoomDetails();
            break;
        case 34:
            mainChar.addItems((currentRoom->getItems())[0]);
            currentRoom->removeItem(0);
            moveState();
            printRoomDetails();
            break;
        default:
            goRoom("north");
    }
}

//south, run, down
void MainWindow::on_southButton_clicked()
{
    switch (state)
    {
        case 0:
            goRoom("south");
            break;
        case 1:
            //add code here
            break;
        case 2:
            if(currentItem < charItems.size() - 1) currentItem++;
            showInventory();
            break;
        case 31:
            //blank
            break;
        case 32:
            //blank
            break;
        case 33:
            //blank
            break;
        case 34:
            mainChar.addItems((currentRoom->getItems())[3]);
            currentRoom->removeItem(3);
            moveState();
            printRoomDetails();
            break;
        default:
            goRoom("south");
    }
}

//east, inspect(fight), equip
void MainWindow::on_eastButton_clicked()
{
    switch (state)
    {
        case 0:
            goRoom("east");
            break;
        case 1:
            //add code here
            break;
        case 2:
            moveState();
            ui->textEdit->setText(QString::fromStdString(mainChar.equipWeapon(currentItem)) + "\n"
                                  + QString::fromStdString(currentRoom->longDescription()));
            break;
        case 31:
            //blank
            break;
        case 32:
            mainChar.addItems((currentRoom->getItems())[1]);
            currentRoom->removeItem(1);
            moveState();
            printRoomDetails();
            break;
        case 33:
            mainChar.addItems((currentRoom->getItems())[2]);
            currentRoom->removeItem(2);
            moveState();
            printRoomDetails();
            break;
        case 34:
            mainChar.addItems((currentRoom->getItems())[2]);
            currentRoom->removeItem(2);
            moveState();
            printRoomDetails();
            break;
        default:
            goRoom("east");
    }
}

//west, item, inspect(inventory)
void MainWindow::on_westButton_clicked()
{
    switch (state)
    {
        case 0:
            goRoom("west");
            break;
        case 1:
            //add code here
            break;
        case 2:
            moveState();
            ui->textEdit->setText(QString::fromStdString(charItems[currentItem].getLongDescription()) + "\n\n"
                                  + QString::fromStdString(currentRoom->longDescription()));
            break;
        case 31:
            //blank
            break;
        case 32:
            mainChar.addItems((currentRoom->getItems())[0]);
            currentRoom->removeItem(0);
            moveState();
            printRoomDetails();
            break;
        case 33:
            mainChar.addItems((currentRoom->getItems())[1]);
            currentRoom->removeItem(1);
            moveState();
            printRoomDetails();
            break;
        case 34:
            mainChar.addItems((currentRoom->getItems())[1]);
            currentRoom->removeItem(1);
            moveState();
            printRoomDetails();
            break;
        default:
            goRoom("west");
    }
}

//pickup, blank, drop
void MainWindow::on_pickUpButton_clicked()
{
    switch (state)
    {
        case 0:
            selectItems((currentRoom->getItems()).size());
            if ((currentRoom->getItems()).size() > 0) ui->InventoryButton->setText("Cancel");
            break;
        case 1:
            //add code here
            break;
        case 2:
            currentRoom->addItem(charItems[currentItem]);
            ui->textEdit->setText("dropped " + QString::fromStdString(charItems[currentItem].getShortDescription()) + "\n\n"
                                  + QString::fromStdString(currentRoom->longDescription()));
            mainChar.removeItem(currentItem);
            moveState();

            break;
        //default:
            //add code here
    }
}

//inventory, blank, close inventory, cancel
void MainWindow::on_InventoryButton_clicked()
{
    switch (state)
    {
        case 0:
            currentItem = 0;
            charItems = mainChar.getItems();
            showInventory();
            inventoryState();
            break;
        case 1:
            //add code here
            break;
        case 2:
            moveState();
            printRoomDetails();
            break;
        case 31:
            moveState();
            printRoomDetails();
            break;
        case 32:
            moveState();
            printRoomDetails();
            break;
        case 33:
            moveState();
            printRoomDetails();
            break;
        case 34:
            moveState();
            printRoomDetails();
            break;
        //default:
            //add code here
    }
}

