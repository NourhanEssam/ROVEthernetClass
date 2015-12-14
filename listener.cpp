#include "listener.h"
Listener::Listener( QWidget *parent ) : QLabel( parent )
{
qDebug()<<"inside constructor";
setText( "Waiting for data." );
socket = new QUdpSocket( this );
socket->bind( 9988 );
connect( socket, SIGNAL(readyRead()), this, SLOT(dataPending()) );
}
void Listener::dataPending()
{
while( socket->hasPendingDatagrams() )
{
QByteArray buffer( socket->pendingDatagramSize(), 0 );
socket->readDatagram( buffer.data(), buffer.size() );
QDataStream stream( buffer );
stream.setVersion( QDataStream::Qt_4_0 );
float y;
QString str;
stream>> str >>y;
qDebug()<<"Sent data"<< str <<y;
}
}
