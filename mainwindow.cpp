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
    ui->label->setPixmap(pix.scaled(100, 100, Qt::KeepAspectRatio));

    Enemy::setNumOfEnemies(0);
    Boss::setNumOfBosses(0);
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
        a->addItem(new Item("x", 1, 11, false));
        a->addItem(new Item("y", 2, 22, false));
    b = new Room("b");
        b->addItem(new Item("xx", 3, 33, false));
        b->addItem(new Item("yy", 4, 44, false));
    c = new Room("c");
    d = new Room("d");
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

void MainWindow::setShortcuts(){
    QShortcut w(QKeySequence('w'), ui->pushButton);
    QShortcut s(QKeySequence('s'), ui->pushButton_2);
    QShortcut d(QKeySequence('d'), ui->pushButton_3);
    QShortcut a(QKeySequence('a'), ui->pushButton_4);

     //QObject::connect(w, SIGNAL(activated()), ui->pushButton, SLOT(on_pushButton_clicked()));
}

inline void MainWindow::printWelcome() {
    ui->textEdit->setText("start \ninfo for help \n\n" +
                          QString::fromStdString(currentRoom->longDescription()) + "\n");

}

void MainWindow::goRoom(string direction) {

    // Try to leave current room.
    Room* nextRoom = currentRoom->nextRoom(direction);

    if (nextRoom == NULL)
        ui->textEdit->setText("You cannot go that way\n\n" + QString::fromStdString(currentRoom->longDescription()));
    else {
        currentRoom = nextRoom;
        ui->textEdit->setText(QString::fromStdString(currentRoom->longDescription()));
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

void MainWindow::moveState()
{
    state = 0;
    ui->pushButton->setText("north");
    ui->pushButton_2->setText("south");
    ui->pushButton_3->setText("east");
    ui->pushButton_4->setText("west");
}

void MainWindow::fightState()
{
    state = 1;
    ui->pushButton->setText("");
    ui->pushButton_2->setText("");
    ui->pushButton_3->setText("");
    ui->pushButton_4->setText("");
}



//n
void MainWindow::on_pushButton_clicked()
{
    if (state == 0) goRoom("north");
}

//s
void MainWindow::on_pushButton_2_clicked()
{
    if (state == 0) goRoom("south");
}

//e
void MainWindow::on_pushButton_3_clicked()
{
    if (state == 0) goRoom("east");

}

//w
void MainWindow::on_pushButton_4_clicked()
{
    if (state == 0) goRoom("west");

}

