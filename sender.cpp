#include "sender.h"

Sender::Sender()
{
    socket = new QUdpSocket( this );
    QTimer *timer = new QTimer( this );
    timer->setInterval( 250 );
    timer->start();
    //connect( timer, SIGNAL(timeout()), this, SLOT(broadcastLine()) );
}

//void Sender::broadcastLine()
//{
//    QByteArray buffer( 50, 0 );
//    QDataStream stream( &buffer, QIODevice::WriteOnly );
//    stream.setVersion( QDataStream::Qt_4_0 );
//    float y = value;
//    QString z;
//    stream << z<<y;
//    socket->writeDatagram( buffer, QHostAddress::Broadcast, 9988 );
//}

void Sender::writedata()
{
    QByteArray buffer( 50, 0 );
    QDataStream stream( &buffer, QIODevice::WriteOnly );
    stream.setVersion( QDataStream::Qt_4_0 );
    float y = value;
    QString z;
    stream << z.constData() <<y;
    socket->writeDatagram( buffer, QHostAddress::Broadcast, 9988 );
}

void Sender::sendvalue(float x)
{
    value = x;
    qDebug()<< "Value sent" <<value;
}

void Sender::sendchar(QString s)
{
    character = s;
    qDebug()<< "character sent" <<character;
}
