#ifndef LISTENER_H
#define LISTENER_H

#include <QObject>
#include <QUdpSocket>
#include <QLabel>
#include <QImage>

class Listener : public QLabel
{
Q_OBJECT
public:
Listener( QWidget *parent=0 );
private slots:
void dataPending();
private:
QUdpSocket *socket;
};

#endif // LISTENER_H
