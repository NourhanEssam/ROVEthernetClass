#ifndef SENDER_H
#define SENDER_H

#include <QObject>
#include <QUdpSocket>
#include <QTimer>
#include <QLabel>
#include <QImage>

class Sender : public QObject
{
    Q_OBJECT
public:
    Sender();
    void sendvalue(float x);
    void sendchar(QString s);
    void writedata();
private:
    QUdpSocket *socket;
    float value;
    QString character;
};

#endif // SENDER_H
