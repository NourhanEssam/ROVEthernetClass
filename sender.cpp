#include "sender.h"

Sender::Sender()
{
    socket = new QUdpSocket( this );
//    QTimer *timer = new QTimer( this );
//    timer->setInterval( 250 );
//    timer->start();
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
    QByteArray buffer;/*
    QDataStream stream( &buffer, QIODevice::WriteOnly );
    stream.setVersion( QDataStream::Qt_4_0 );
    float y = value;
    QString z;
    //stream << z.constData() <<y;
    //buffer.append("test");
//    buffer += QByteArray:: number(100);
    stream << z <<y;
    qDebug()<<"size1"<<(quint32)buffer.data()<<buffer.size();*/
    //qDebug()<<"buffer"<<buffer;
    //float x = 102.123;
    buffer.append(character);
    buffer.append(QByteArray::number(value));
    socket->writeDatagram( buffer, QHostAddress("169.254.0.2"), 5005 );
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
