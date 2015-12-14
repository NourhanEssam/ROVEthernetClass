#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    joystick = new joysticksdl(0);
    joystick->setKind(1,4);

    sender = new Sender();
    list = new Listener();
    x = 15.555;
    y = "empty";
    sender->sendvalue(x);
    t = new QTimer();
    t->start(30);
    //connect(t,SIGNAL(timeout()),this,SLOT(incr()));
    connect(joystick,SIGNAL(axismoved(QString,float)),this,SLOT(axismovedS(QString,float)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::incr()
{
    x++;
    sender->sendchar(y);
    sender->sendvalue(x);
}

void MainWindow::axismovedS(QString s, float f)
{
    sender->sendchar(s);
    sender->sendvalue(f);
}
