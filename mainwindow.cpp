#include <iostream>
using namespace std;

#include "mainwindow.h"
#include "ui_mainwindow.h"

#define map "../ZorkProject/Images/ZorkMap.png"
#define mapCharacter "../ZorkProject/Images/MapCharacter.png"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setShortcuts();
    QPixmap zorkMap(map);
    QPixmap charIcon(mapCharacter);
    ui->zorkMap->setPixmap(zorkMap.scaled(471, 471, Qt::KeepAspectRatio));
    ui->charIcon->setPixmap(charIcon.scaled(41, 41, Qt::KeepAspectRatio));
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
    for(int i = 0; i< rooms.size(); i++)
    {
        delete rooms[i];
    }
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
    Room *a, *b, *c, *d, *e, *f, *g, *h, *i, *j, *k, *l, *f1, *g1, *h1, *i1, *j1, *k1, *l1, *m1, *g2, *h2, *i2, *j2, *k2, *m2, *i3, *j3, *k3, *j4, *k4;

    a = new Room();
    b = new Room();
    c = new Room();
    d = new Room();
    e = new Room();
        e->addItem(Item("sword", 10, 5, 0, true, false));
        e->setEnemy(BasicEnemy("bat", "the bat flies about aimlessly", 5, 2, 3));
    f = new Room();
    g = new Room();
    h = new Room();
        h->addItem(Item("rock", 3, 11, 0, false, true));
        h->addItem(Item("potion", 1, 0, 10, false, false));
    i = new Room();
    j = new Room();
    k = new Room();
    l = new Room();
        l->addItem(Item("trophie", 10, 50, 0, true, false));
        Boss *fBoss = new Boss(2, "grog", "grog is groging about menacingly", 30, 5, 20);
        floorBoss = dynamic_cast<Boss*>(fBoss);
        l->setEnemy(*floorBoss);
    f1 = new Room();
    g1 = new Room();
    h1 = new Room();
    i1 = new Room();
    j1 = new Room();
    k1 = new Room();
    l1 = new Room();
    m1 = new Room();
        m1->addItem(Item("bomb", 5, 50, 0, false, true));
    g2 = new Room();
    h2 = new Room();
    i2 = new Room();
    j2 = new Room();
    k2 = new Room();
        k2->addItem(Item("baseball bat", 5, 10, 0, true, false));
        k2->setEnemy(BasicEnemy("bat", "the bat sits on the groud stationary", 1, 0, 0));
    m2 = new Room();
        m2->addItem(Item("greater potion", 2, 0, 30, false, false));
    i3 = new Room();
    j3 = new Room();
    k3 = new Room();
        k3->addItem(Item("axe", 20, 17, 0, true, false));
    j4 = new Room();
    k4 = new Room();
        k4->addItem(Item("brick", 6, 15, 0, false, true));

                //N, E, S, W
    a->setExits(b, NULL, NULL, NULL);
    b->setExits(NULL, c, a, NULL);
    c->setExits(d, NULL, NULL, b);
    d->setExits(NULL, e, c, NULL);
    e->setExits(f, NULL, f1, d);
    f->setExits(NULL, g, e, g2);
    g->setExits(h, NULL, NULL, f);
    h->setExits(i, NULL, g, NULL);
    i->setExits(NULL, j, h, j4);
    j->setExits(NULL, k, NULL, i);
    k->setExits(l, NULL, NULL, j);
    l->setExits(NULL, NULL, k, NULL);
    f1->setExits(e, g1, NULL, NULL);
    g1->setExits(NULL, NULL, h1, f1);
    h1->setExits(g1, i1, NULL, NULL);
    i1->setExits(NULL, j1, NULL, h1);
    j1->setExits(k1, NULL, NULL, i1);
    k1->setExits(l1, NULL, j1, NULL);
    l1->setExits(m1, NULL, k1, m2);
    m1->setExits(NULL, NULL, l1, NULL);
    g2->setExits(NULL, f, NULL, h2);
    h2->setExits(i2, g2, i3, NULL);
    i2->setExits(NULL, NULL, h2, j2);
    j2->setExits(k2, i2, NULL, NULL);
    k2->setExits(NULL, NULL, j2, NULL);
    m2->setExits(NULL, l1, NULL, NULL);
    i3->setExits(h2, NULL, NULL, j3);
    j3->setExits(NULL, i3, NULL, NULL);
    k3->setExits(NULL, NULL, j4, NULL);
    j4->setExits(k3, i, NULL, k4);
    k4->setExits(NULL, j4, NULL, NULL);

    rooms = {a, b, c, d, e, f, g, h, i, j, k, l, f1, g1, h1, i1, j1, k1, l1, m1, g2, h2, i2, j2, k2, m2, i3, j3, k3, j4, k4};
    currentRoom = a;
    //example of a reference to a room
    Room &refToRoom = *currentRoom;

}


void MainWindow::setShortcuts(){
    QShortcut *shortcutW = new QShortcut(QKeySequence("W"), ui->centralwidget);
    QObject::connect(shortcutW, SIGNAL(activated()), this, SLOT(on_northButton_clicked()));

    QShortcut *shortcutS = new QShortcut(QKeySequence("S"), ui->centralwidget);
    QObject::connect(shortcutS, SIGNAL(activated()), this, SLOT(on_southButton_clicked()));

    QShortcut *shortcutD = new QShortcut(QKeySequence("D"), ui->centralwidget);
    QObject::connect(shortcutD, SIGNAL(activated()), this, SLOT(on_eastButton_clicked()));

    QShortcut *shortcutA = new QShortcut(QKeySequence("A"), ui->centralwidget);
    QObject::connect(shortcutA, SIGNAL(activated()), this, SLOT(on_westButton_clicked()));

    QShortcut *shortcutQ = new QShortcut(QKeySequence("Q"), ui->centralwidget);
    QObject::connect(shortcutQ, SIGNAL(activated()), this, SLOT(on_pickUpButton_clicked()));

    QShortcut *shortcutE = new QShortcut(QKeySequence("E"), ui->centralwidget);
    QObject::connect(shortcutE, SIGNAL(activated()), this, SLOT(on_inventoryButton_clicked()));

}


inline void MainWindow::printWelcome()
{
    showRoomDetails();
    ui->statusBar->setText("you can control the buttons with your keyboard\nDirectional buttons = WASD\nPick Up = Q\nInventory = E");
}

inline void MainWindow::showRoomDetails()
{
    ui->textEdit->setText(QConvert::convert(currentRoom->longDescription()));
}

inline QString MainWindow::getRoomDetails()
{
    return QConvert::convert(currentRoom->longDescription());
}

void MainWindow::moveCharIcon(string direction)
{
    if(direction == "north")
    {
        ui->charIcon->setGeometry(ui->charIcon->geometry().x(), ui->charIcon->geometry().y() - 64, 41, 41);
    } else if(direction == "south") {
        ui->charIcon->setGeometry(ui->charIcon->geometry().x(), ui->charIcon->geometry().y() + 64, 41, 41);
    }  else if(direction == "east") {
        ui->charIcon->setGeometry(ui->charIcon->geometry().x() + 64, ui->charIcon->geometry().y(), 41, 41);
    } else {
        ui->charIcon->setGeometry(ui->charIcon->geometry().x() - 64, ui->charIcon->geometry().y(), 41, 41);
    }
}

void MainWindow::goRoom(string direction) {

    // Try to leave current room.
    Room* nextRoom = currentRoom->nextRoom(direction);
    ui->statusBar->setText(" ");

    if (nextRoom == NULL)
    {
        showRoomDetails();
        ui->statusBar->setText("you cannot go that way");
    } else {
        previousRoom = currentRoom;
        currentRoom = nextRoom;
        if(currentRoom->checkForEnemy())
        {
            directionToMove = direction;
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
        moveCharIcon(direction);
        showRoomDetails();
    }
}


void MainWindow::showInventory()
{
    ui->statusBar->setText(" ");
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
        moveCharIcon(directionToMove);
        showRoomDetails();
        ui->statusBar->setText("Turn " + QConvert::convertToString(battleTurn) +
                              "\nyou dealt " + QConvert::convertToString(inDmg) + " damage to " + enemyName +
                              "\n" + enemyName + " died\n" +
                              "you gained " + QConvert::convertToString(currentEnemy->getExpGain()) + " experience");
        moveState();
    } else if(currentEnemy->getHealth() < 1 && currentEnemy->getType() == "boss") {
        if (floorBoss->getPhases() < 1)
        {
            currentEnemy->slain();
            currentRoom->removeEnemy();
            moveCharIcon(directionToMove);
            showRoomDetails();
            ui->statusBar->setText("Turn " + QConvert::convertToString(battleTurn) +
                                  "\nyou dealt " + QConvert::convertToString(inDmg) + " damage to " + enemyName +
                                  "\n" + enemyName + " died\n" +
                                  "you gained " + QConvert::convertToString(currentEnemy->getExpGain()) + " experience");
            moveState();
        } else {
            floorBoss->setPhases(floorBoss->getPhases() - 1);
            currentEnemy->setHealth(currentEnemy->getMaxHealth());
            ui->enemyHealthBar->setValue(currentEnemy->getHealth());
            ui->textEdit->setText(QConvert::convert(currentEnemy->getLongDescription()));
            ui->statusBar->setText("Turn " + QConvert::convertToString(battleTurn) +
                                  "\n" + enemyName + " entered next phase"
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
            ui->textEdit->setText(QConvert::convert(currentEnemy->getLongDescription()));
            ui->statusBar->setText("Turn " + QConvert::convertToString(battleTurn) +
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
            ui->textEdit->setText(QConvert::convert(currentEnemy->getLongDescription()));
            ui->statusBar->setText("Turn " + QConvert::convertToString(battleTurn) +
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
    ui->northButton->setText("North" );
    ui->southButton->setText("South");
    ui->eastButton->setText("East");
    ui->westButton->setText("West");
    ui->inventoryButton->setText("Inventory");
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
    ui->inventoryButton->setText("");
    ui->pickUpButton -> setText("");
}

void MainWindow::inventoryState()
{
    state = 2;
    ui->northButton->setText("Up");
    ui->southButton->setText("Down");
    ui->eastButton->setText("Equip/Use");
    ui->westButton->setText("Inspect");
    ui->inventoryButton->setText("Close Inventory");
    ui->pickUpButton -> setText("Drop");
}

void MainWindow::gameOverState()
{
    state = 4;
    ui->northButton->setText("");
    ui->southButton->setText("");
    ui->eastButton->setText("");
    ui->westButton->setText("");
    ui->inventoryButton->setText("Quit");
    ui->pickUpButton -> setText("");
}

void MainWindow::battleInventoryState()
{
    state = 5;
    ui->northButton->setText("Up");
    ui->southButton->setText("Down");
    ui->eastButton->setText("");
    ui->westButton->setText("");
    ui->inventoryButton->setText("Cancel");
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
            showRoomDetails();
            break;
        case 32:
            //blank
            break;
        case 33:
            mainChar.addItems((currentRoom->getItems())[0]);
            currentRoom->removeItem(0);
            moveState();
            showRoomDetails();
            break;
        case 34:
            mainChar.addItems((currentRoom->getItems())[0]);
            currentRoom->removeItem(0);
            moveState();
            showRoomDetails();
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
            showRoomDetails();
            ui->statusBar->setText("you ran away");
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
            showRoomDetails();
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
                ui->textEdit->setText(QConvert::convert(currentEnemy->getLongDescription()));
                ui->statusBar->setText("your inventory is empty");
            }

            break;
        case 2:
            //moveState();
            if(charItems[currentItem].getWeaponCheck()){
                showRoomDetails();
                ui->statusBar->setText(QConvert::convert(mainChar.equipWeapon(currentItem)));
                moveState();
            } else if (charItems[currentItem].getHealing() > 0){
                heal(charItems[currentItem]);
                int healed = charItems[currentItem].getHealing();
                mainChar.removeItem(currentItem);
                charItems = mainChar.getItems();
                currentItem = 0;
                if(charItems.size() <=1)
                {
                    moveState();
                    showRoomDetails();
                    ui->statusBar->setText("you healed for " + QConvert::convertToString(healed) + " health points");
                } else {
                    showInventory();
                    ui->statusBar->setText("you healed for " + QConvert::convertToString(healed) + " health points");
                }

            } else if (charItems[currentItem].getDmg() > 0){
                showInventory();
                ui->statusBar->setText("you can only use this during a battle");
            }

            break;
        case 31:
            //blank
            break;
        case 32:
            mainChar.addItems((currentRoom->getItems())[1]);
            currentRoom->removeItem(1);
            moveState();
            showRoomDetails();
            break;
        case 33:
            mainChar.addItems((currentRoom->getItems())[2]);
            currentRoom->removeItem(2);
            moveState();
            showRoomDetails();
            break;
        case 34:
            mainChar.addItems((currentRoom->getItems())[2]);
            currentRoom->removeItem(2);
            moveState();
            showRoomDetails();
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

//west, inspect, inspect(inventory)
void MainWindow::on_westButton_clicked()
{
    switch (state)
    {
        case 0:
            goRoom("west");
            break;
        case 1:
            ui->statusBar->setText("its a " + QConvert::convert(currentEnemy->getName()));
            break;
        case 2:
            moveState();
            showRoomDetails();
            ui->statusBar->setText(QConvert::convert(charItems[currentItem].getLongDescription()));
            break;
        case 31:
            //blank
            break;
        case 32:
            mainChar.addItems((currentRoom->getItems())[0]);
            currentRoom->removeItem(0);
            moveState();
            showRoomDetails();
            break;
        case 33:
            mainChar.addItems((currentRoom->getItems())[1]);
            currentRoom->removeItem(1);
            moveState();
            showRoomDetails();
            break;
        case 34:
            mainChar.addItems((currentRoom->getItems())[1]);
            currentRoom->removeItem(1);
            moveState();
            showRoomDetails();
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
            if ((currentRoom->getItems()).size() > 0)
            {
                ui->statusBar->setText(" ");
                selectItems((currentRoom->getItems()).size());
                   ui->inventoryButton->setText("Cancel");
            } else {
                ui->statusBar->setText("no items in room");
            }

            break;
        case 1:
            //blank
            break;
        case 2:
            currentRoom->addItem(charItems[currentItem]);
            showRoomDetails();
            ui->statusBar->setText("dropped " + QConvert::convert(charItems[currentItem].getShortDescription()));
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
                showInventory();
                ui->statusBar->setText("cannot use this item");
            }
            break;
        //default:
            //add code here
    }
}

//inventory, blank, close inventory, cancel, quit, cancel(stop item use)
void MainWindow::on_inventoryButton_clicked()
{
    switch (state)
    {
        case 0:
            if(mainChar.getItems().size() > 0)
            {
                currentItem = 0;
                charItems = mainChar.getItems();
                showInventory();
                inventoryState();
            } else {
                showRoomDetails();
                ui->statusBar->setText("your inventory is empty");
            }

            break;
        case 1:
            ///blank
            break;
        case 2:
            ui->statusBar->setText(" ");
            moveState();
            showRoomDetails();
            break;
        case 31:
            moveState();
            showRoomDetails();
            break;
        case 32:
            moveState();
            showRoomDetails();
            break;
        case 33:
            moveState();
            showRoomDetails();
            break;
        case 34:
            moveState();
            showRoomDetails();
            break;
        case 4:
            exit(0);
            break;
        case 5:
            fightState();
            ui->statusBar->setText(" ");
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






