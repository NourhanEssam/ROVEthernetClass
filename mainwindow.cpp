#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    Sender sender;
//    Listener list;
    sender = new Sender();
    list = new Listener();
    //qint16 x;
    x = 15;
    sender->sendvalue(x);
    t = new QTimer();
    t->start(30);
    connect(t,SIGNAL(timeout()),this,SLOT(incr()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::incr()
{
    x++;
    sender->sendvalue(x);
}
