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
    connect(joystick,SIGNAL(axismoved(QString,float)),this,SLOT(axismovedS(QString,float)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::axismovedS(QString s, float f)
{
    sender->sendchar(s);
    sender->sendvalue(f);
    sender->writedata();
}
