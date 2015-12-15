#include "sender.h"

Sender::Sender()
{
    socket = new QUdpSocket( this );
}

void Sender::writedata()
{
    QByteArray buffer;
    buffer.append(character);
    buffer.append(QByteArray::number(value));
    socket->writeDatagram( buffer, QHostAddress("169.254.0.2"), 5005 );
    qDebug()<<"Written data: "<<buffer;
}

void Sender::sendvalue(float x)
{
    value = x;
}

void Sender::sendchar(QString s)
{
    character = s;
}
