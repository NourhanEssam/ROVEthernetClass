#include "listener.h"
Listener::Listener( QWidget *parent ) : QLabel( parent )
{    setText( "Waiting for data." );
     socket = new QUdpSocket( this );
      socket->bind( QHostAddress("169.254.242.202"), 5005 );
       connect( socket, SIGNAL(readyRead()), this, SLOT(dataPending()) );
}
void Listener::dataPending()
{
    while( socket->hasPendingDatagrams() )
    {
        QByteArray buffer( socket->pendingDatagramSize(), 0 );
        buffer.resize(socket->pendingDatagramSize());
        socket->readDatagram( buffer.data(), buffer.size() );
        qDebug()<<"Received data: "<<buffer;
    }
}
