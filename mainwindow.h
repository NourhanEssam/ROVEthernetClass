#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sender.h"
#include "listener.h"
#include <QTimer>
#include "joystick.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    Sender *sender;
    Listener *list;
    float x;
    QString y;
    joysticksdl *joystick;

private slots:
    void axismovedS(QString s, float f);
};

#endif // MAINWINDOW_H
