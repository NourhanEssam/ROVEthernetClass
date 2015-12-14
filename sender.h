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
void sendvalue(qint16 x);
private slots:
void broadcastLine();
private:
QUdpSocket *socket;
int value;
};

#endif // SENDER_H
