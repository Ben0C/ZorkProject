#include <iostream>
using namespace std;

#include "mainwindow.h"
#include "ui_mainwindow.h"

#define map "../ZorkProject/Images/glep.png"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap pix(map);
    ui->label->setPixmap(pix.scaled(371, 471, Qt::KeepAspectRatio));
    ui->enemyHealthBar->setStyleSheet("QProgressBar::chunk {background: red}");
    ui->playerHealthBar->setStyleSheet("QProgressBar::chunk {background: green}");

    Enemy::setNumOfEnemies(0);
    Boss::setNumOfBosses(0);
    mainChar = Character("You", 50);
    ui->playerHealthBar->setMaximum(mainChar.getHealth());
    ui->playerHealthBar->setValue(mainChar.getHealth());
    createRooms();
    moveState();
    printWelcome();
}

MainWindow::~MainWindow()
{
    delete ui;
}

namespace QConvert
{
    QString convert(string stdString)
    {
        return QString::fromStdString(stdString);
    }

    template<typename T>
    QString convertToString(T value)
    {
        return QString::fromStdString(to_string(value));
    }
}

void MainWindow::createRooms()  {
    Room *a, *b, *c, *d, *e, *f, *g, *h, *i, *j;


    a = new Room();
        a->addItem(new Item("weapon", 1, 10, 0, true));
        //a->addItem(new Item("y", 2, 22, false));
    b = new Room("b");
        b->addItem(new Item("x1", 3, 1, 0,  false));
        b->addItem(new Item("y1", 4, 0, 1, false));
        b->setEnemy(BasicEnemy("bat", "flies about aimlessly", 5, 2, 3));
    c = new Room("c");
        c->addItem(new Item("x2", 3, 0, 1, false));
        c->addItem(new Item("y2", 4, 1, 0, false));
        c->addItem(new Item("z2", 4, 0, 1, false));
        c->setEnemy(BasicEnemy("bat", "flies about aimlessly", 5, 20, 3));
    d = new Room("d");
        d->addItem(new Item("x3", 3, 0, 1, false));
        d->addItem(new Item("y3", 4, 0, 1, false));
        d->addItem(new Item("z3", 4, 0, 1, false));
        d->addItem(new Item("q3", 4, 0, 1, false));
    e = new Room("e");
    f = new Room("f");
        f->addItem(new Item("x4", 3, 0, 1, false));
        f->addItem(new Item("y4", 4, 1, 0, false));
        f->addItem(new Item("z4", 4, 1, 0, false));
        f->addItem(new Item("q4", 4, 0, 1, false));
    g = new Room("g");
        Boss *fBoss = new Boss(2, "grog", "grogs around", 30, 5, 20);
        floorBoss = dynamic_cast<Boss*>(fBoss);
        g->setEnemy(*floorBoss);
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

inline void MainWindow::printWelcome()
{
    ui->textEdit->setText("start \ninfo for help \n\n" +
                          getRoomDetails() + "\n");
}

inline void MainWindow::printRoomDetails()
{
    ui->textEdit->setText(QConvert::convert(currentRoom->longDescription()));
}

inline QString MainWindow::getRoomDetails()
{
    return QConvert::convert(currentRoom->longDescription());
}

void MainWindow::goRoom(string direction) {

    // Try to leave current room.
    Room* nextRoom = currentRoom->nextRoom(direction);

    if (nextRoom == NULL)
        ui->textEdit->setText("You cannot go that way\n\n" + QConvert::convert(currentRoom->longDescription()));
    else {
        previousRoom = currentRoom;
        currentRoom = nextRoom;
        if(currentRoom->checkForEnemy())
        {
            fightState();
            battleTurn = 0;
            currentEnemy = currentRoom->getEnemy();
            ui->enemyHealthBar->setMaximum(currentEnemy->getMaxHealth());
            ui->enemyHealthBar->setValue(currentEnemy->getHealth());
            enemyName = QConvert::convert(currentEnemy->getName());
            charDmg = QConvert::convertToString(mainChar.getDmg());
            ui->textEdit->setText(QConvert::convert(currentEnemy->getLongDescription()));
            return;
        }
        printRoomDetails();
    }
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
    ui->textEdit->setText(QConvert::convert(itemList));
}

QString MainWindow::getInventory()
{
    string itemList = "";
    for(int i = 0; i < charItems.size(); i++)
    {
        if(i == currentItem){
            itemList += "->";
        }
        itemList += ("  " + (charItems[i]).getShortDescription() + "\n");
    }
    return QConvert::convert(itemList);
}

void MainWindow::selectItems(int numOfItems)
{
    switch (numOfItems){
        case 0:
            break;
        case 1:
            state = 31;
            ui->northButton->setText(QConvert::convert((currentRoom->getItems())[0].getShortDescription()));
            ui->southButton->setText("");
            ui->eastButton->setText("");
            ui->westButton->setText("");
            break;
        case 2:
            state = 32;
            ui->northButton->setText("");
            ui->southButton->setText("");
            ui->eastButton->setText(QConvert::convert((currentRoom->getItems())[1].getShortDescription()));
            ui->westButton->setText(QConvert::convert((currentRoom->getItems())[0].getShortDescription()));
            break;
        case 3:
            state = 33;
            ui->northButton->setText(QConvert::convert((currentRoom->getItems())[0].getShortDescription()));
            ui->southButton->setText("");
            ui->eastButton->setText(QConvert::convert((currentRoom->getItems())[2].getShortDescription()));
            ui->westButton->setText(QConvert::convert((currentRoom->getItems())[1].getShortDescription()));
            break;
        default:
            state = 34;
            ui->northButton->setText(QConvert::convert((currentRoom->getItems())[0].getShortDescription()));
            ui->southButton->setText(QConvert::convert((currentRoom->getItems())[3].getShortDescription()));
            ui->eastButton->setText(QConvert::convert((currentRoom->getItems())[2].getShortDescription()));
            ui->westButton->setText(QConvert::convert((currentRoom->getItems())[1].getShortDescription()));
    }
}

void MainWindow::atkEnemy(int inDmg)
{
    if(inDmg == 0){
        currentEnemy->reduceHealth(mainChar.getDmg());
        inDmg = mainChar.getDmg();
    } else {
        currentEnemy->reduceHealth(inDmg);
    }
    ui->enemyHealthBar->setValue(currentEnemy->getHealth());
    if(currentEnemy->getHealth() < 1 && currentEnemy->getType() == "basic enemy")
    {
        currentEnemy->slain();
        currentRoom->removeEnemy();
        ui->textEdit->setText("Turn " + QConvert::convertToString(battleTurn) +
                              "\nyou dealt " + QConvert::convertToString(inDmg) + " damage to " + enemyName +
                              "\n" + enemyName + " died\n" +
                              "you gained " + QConvert::convertToString(currentEnemy->getExpGain()) + " experience\n\n\n" +
                              getRoomDetails());
        moveState();
    } else if(currentEnemy->getHealth() < 1 && currentEnemy->getType() == "boss") {
        if (floorBoss->getPhases() < 1)
        {
            currentEnemy->slain();
            currentRoom->removeEnemy();
            ui->textEdit->setText("Turn " + QConvert::convertToString(battleTurn) +
                                  "\nyou dealt " + QConvert::convertToString(inDmg) + " damage to " + enemyName +
                                  "\n" + enemyName + " died\n" +
                                  "you gained " + QConvert::convertToString(currentEnemy->getExpGain()) + " experience\n\n\n" +
                                  getRoomDetails());
            moveState();
        } else {
            floorBoss->setPhases(floorBoss->getPhases() - 1);
            currentEnemy->setHealth(currentEnemy->getMaxHealth());
            ui->enemyHealthBar->setValue(currentEnemy->getHealth());
            ui->textEdit->setText("Turn " + QConvert::convertToString(battleTurn) +
                                  "\nyou dealt " + QConvert::convertToString(inDmg) + " damage to " + enemyName +
                                  "\n" + enemyName + " dealt " + QConvert::convertToString(currentEnemy->getDmg()) + " damage to you\n");
            battleTurn++;
            fightState();
        }



    } else {
        mainChar.reduceHealth(currentEnemy->getDmg());
        ui->playerHealthBar->setValue(mainChar.getHealth());
        if(mainChar.getHealth() < 1)
        {
            ui->textEdit->setText("Game Over");
            ui->playerHealthBar->setValue(0);
            gameOverState();
        } else {
            ui->textEdit->setText("Turn " + QConvert::convertToString(battleTurn) +
                                  "\nyou dealt " + QConvert::convertToString(inDmg) + " damage to " + enemyName +
                                  "\n" + enemyName + " dealt " + QConvert::convertToString(currentEnemy->getDmg()) + " damage to you\n");
            battleTurn++;
            fightState();
        }


    }

}

void MainWindow::heal(Item item)
{
    mainChar.setHealth(mainChar.getHealth() + item.getHealing());
    if(mainChar.getHealth() > mainChar.getMaxHealth()) mainChar.setHealth(mainChar.getMaxHealth());
    ui->playerHealthBar->setValue(mainChar.getHealth());
}

void MainWindow::useItem(Item item)
{
    if (item.getDmg() > 0)
    {
        atkEnemy(item.getDmg());
    } else if (item.getHealing() > 0){
        heal(item);
        mainChar.reduceHealth(currentEnemy->getDmg());
        ui->playerHealthBar->setValue(mainChar.getHealth());
        if(mainChar.getHealth() < 1)
        {
            ui->textEdit->setText("Game Over");
            ui->playerHealthBar->setValue(0);
            gameOverState();
        } else {
            ui->textEdit->setText("Turn " + QConvert::convertToString(battleTurn) +
                                  "\nyou healed for " + QConvert::convertToString(item.getHealing()) + " health points\n" +
                                  "\n" + enemyName + " dealt " + QConvert::convertToString(currentEnemy->getDmg()) + " damage to you\n");
            battleTurn++;
            fightState();
        }
    }

}



//States ---------------------------

void MainWindow::moveState()
{
    state = 0;
    ui->enemyHealthBar->setTextVisible(false);
    ui->enemyHealthBar->setValue(0);
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
    ui->enemyHealthBar->setTextVisible(true);
    ui->northButton->setText("Attack");
    ui->southButton->setText("Run");
    ui->eastButton->setText("Item");
    ui->westButton->setText("Inspect");
    ui->InventoryButton->setText("");
    ui->pickUpButton -> setText("");
}

void MainWindow::inventoryState()
{
    state = 2;
    ui->northButton->setText("Up");
    ui->southButton->setText("Down");
    ui->eastButton->setText("Equip/Use");
    ui->westButton->setText("Inspect");
    ui->InventoryButton->setText("Close Inventory");
    ui->pickUpButton -> setText("Drop");
}

void MainWindow::gameOverState()
{
    state = 4;
    ui->northButton->setText("");
    ui->southButton->setText("");
    ui->eastButton->setText("");
    ui->westButton->setText("");
    ui->InventoryButton->setText("Quit");
    ui->pickUpButton -> setText("");
}

void MainWindow::battleInventoryState()
{
    state = 5;
    ui->northButton->setText("Up");
    ui->southButton->setText("Down");
    ui->eastButton->setText("");
    ui->westButton->setText("");
    ui->InventoryButton->setText("Cancel");
    ui->pickUpButton -> setText("Use");
}

//Buttons -------------------------

//north, attack, up(inventory), itemselect, blank, up(battleinventory)
void MainWindow::on_northButton_clicked()
{
    switch (state)
    {
        case 0:
            goRoom("north");
            break;
        case 1:
            atkEnemy();
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
        case 4:
            //blank
            break;
        case 5:
            if(currentItem > 0) currentItem--;
            showInventory();
            break;
        default:
            goRoom("north");
    }
}

//south, run, down(inventory), itemselect, blank, down(battleinventory)
void MainWindow::on_southButton_clicked()
{
    switch (state)
    {
        case 0:
            goRoom("south");
            break;
        case 1:
            currentRoom = previousRoom;
            moveState();
            ui->textEdit->setText("you ran away\n\n" + getRoomDetails());
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
        case 4:
            //blank
            break;
        case 5:
            if(currentItem < charItems.size() - 1) currentItem++;
            showInventory();
            break;
        default:
            goRoom("south");
    }
}

//east, item, equip/use
void MainWindow::on_eastButton_clicked()
{
    switch (state)
    {
        case 0:
            goRoom("east");
            break;
        case 1:
            if(mainChar.getItems().size() > 0)
            {
                currentItem = 0;
                charItems = mainChar.getItems();
                showInventory();
                battleInventoryState();
            } else {
                ui->textEdit->setText("your inventory is empty\n\n" + QConvert::convert(currentEnemy->getLongDescription()));
            }

            break;
        case 2:
            //moveState();
            if(charItems[currentItem].getWeaponCheck()){
                ui->textEdit->setText(QConvert::convert(mainChar.equipWeapon(currentItem)) + "\n\n"
                                      + getInventory());
            } else if (charItems[currentItem].getHealing() > 0){
                heal(charItems[currentItem]);
                int healed = charItems[currentItem].getHealing();
                mainChar.removeItem(currentItem);
                charItems = mainChar.getItems();
                currentItem = 0;
                if(charItems.size() <=1)
                {
                    moveState();
                    ui->textEdit->setText("you healed for " + QConvert::convertToString(healed) + " health points \n\n"
                                           + getRoomDetails());
                } else {
                    ui->textEdit->setText("you healed for " + QConvert::convertToString(healed) + " health points \n\n"
                                           + getInventory());
                }

            } else if (charItems[currentItem].getDmg() > 0){
                ui->textEdit->setText("you can only use this during a battle\n\n"
                                      + getInventory());
            }

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
        case 4:
            //blank
            break;
        case 5:
            //blank
            break;
        default:
            goRoom("east");
    }
}

//west, inspect(fight), inspect(inventory)
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
            ui->textEdit->setText(QConvert::convert(charItems[currentItem].getLongDescription()) + "\n\n"
                                  + getRoomDetails());
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
        case 4:
            //blank
            break;
        case 5:
            //blank
            break;
        default:
            goRoom("west");
    }
}

//pickup, blank, drop, blank, blank, use
void MainWindow::on_pickUpButton_clicked()
{
    switch (state)
    {
        case 0:
            selectItems((currentRoom->getItems()).size());
            if ((currentRoom->getItems()).size() > 0) ui->InventoryButton->setText("Cancel");
            break;
        case 1:
            //blank
            break;
        case 2:
            currentRoom->addItem(charItems[currentItem]);
            ui->textEdit->setText("dropped " + QConvert::convert(charItems[currentItem].getShortDescription()) + "\n\n"
                                  + getRoomDetails());
            mainChar.removeItem(currentItem);
            moveState();

            break;
        case 4:
            //blank
            break;
        case 5:
            if (!charItems[currentItem].getWeaponCheck())
            {
                useItem(charItems[currentItem]);
                mainChar.removeItem(currentItem);
            } else {
                ui->textEdit->setText("cannot use this item\n" + getInventory());
            }
            break;
        //default:
            //add code here
    }
}

//inventory, blank, close inventory, cancel, quit, cancel(stop item use)
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
            ///blank
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
        case 4:
            exit(0);
            break;
        case 5:
            fightState();
            ui->textEdit->setText(QConvert::convert(currentEnemy->getLongDescription()));
            break;
        //default:
            //add code here
    }


}

//other implementations --------------------------------------------------

template<typename T>
T templateTest(T x, T y)
{
    T temp;
    temp = x;
    x = y;
    y = temp;
    T & reference = temp;
}



