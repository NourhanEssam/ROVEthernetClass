#include "joystick.h"

joysticksdl::joysticksdl(unsigned int joystickNumber, QObject *parent) : QObject(parent),
    t(new QTimer(this)),
    joystickNumber(joystickNumber),
    isConnected(false),
    checkAutoRepeat(new QTimer(this)),
    autoRepeat(new QTimer(this)),
    currentButton(0)
{
    SDL_Init( SDL_INIT_VIDEO | SDL_INIT_JOYSTICK );
    SDL_JoystickEventState(SDL_ENABLE);

    qDebug()<<  "joysticks found " << SDL_NumJoysticks();
    //ShowAvailableJoysticks();

    if(SDL_NumJoysticks()>0) {
        joy = SDL_JoystickOpen(joystickNumber);
        qDebug()<<"Connecting ... ";
    }else {  qDebug()<<"Couldn't open Joystick";}


    t->start(30);

    connect(t,SIGNAL(timeout()),this,SLOT(checkConnectivity()));
    connect(t, SIGNAL(timeout()), this, SLOT(readJoystickState()));
    connect(checkAutoRepeat, SIGNAL(timeout()), this, SLOT(sCheckAutoRepeat()));
    connect(autoRepeat, SIGNAL(timeout()), this, SLOT(sAutoRepeat()));


    for (int i = 0; i < SDL_JoystickNumButtons(joy); i++)
        buttonStates[i] = false;

    for (int i = 0; i < SDL_JoystickNumButtons(joy); i++)
        buttonKinds[i] = 0;

    emit axismoved("0",10.1);


}


joysticksdl::~joysticksdl()
{}

void joysticksdl::readJoystickState()
{
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch(event.type)
        {
        case SDL_JOYBUTTONDOWN:
            ButtonDown(event);
            break;

        case SDL_JOYBUTTONUP:
            ButtonUp(event);
            break;

        case SDL_JOYAXISMOTION:
            AxisMotion(event);
            break;

        case SDL_JOYBALLMOTION:
            BallMotion(event);
            break;

        case SDL_JOYHATMOTION:
            HatMotion(event);
            break;
        }
    }
}


void joysticksdl::ButtonDown(SDL_Event event)
{
    for(int i=0;i<SDL_JoystickNumButtons(joy);i++)
    {
        if ( event.jbutton.button == i )
        {
            if (checkAutoRepeat->isActive())
                checkAutoRepeat->stop();

            if (autoRepeat->isActive())
                autoRepeat->stop();

            if (getKind(i) == AUTO_REPEAT) {
                checkAutoRepeat->start(100);

                currentButton = i;
            }
            emit buttonPressed(i);
            //qDebug()<<"Button pressed" <<i;
        }
    }
}


void joysticksdl::ButtonUp(SDL_Event event)
{
    for(int i=0;i<SDL_JoystickNumButtons(joy);i++)
    {
        if ( event.jbutton.button == i )
        {
            if (checkAutoRepeat->isActive())
                checkAutoRepeat->stop();

            if (autoRepeat->isActive())
                autoRepeat->stop();

            emit buttonReleased(i);
            //qDebug()<<"released" <<i;
        }
    }
}

void joysticksdl::AxisMotion(SDL_Event event)
{
    if ( ( event.jaxis.value < -3200 ) || (event.jaxis.value > 3200 ) )
    {
        if( event.jaxis.axis == 0) /*0 for Left or Right*/
        {
            emit axismoved(QString("x"),event.jaxis.value);
        }

        if( event.jaxis.axis == 1) /*1 for Up and Down*/
        {
            emit axismoved("y",event.jaxis.value);
        }
        if( event.jaxis.axis == 2)
        {
            emit axismoved("u",event.jaxis.value);
        }
        if( event.jaxis.axis == 3)
        {
            emit axismoved("p",event.jaxis.value);
        }
        if( event.jaxis.axis == 4)
        {
            emit axismoved("p",event.jaxis.value);
        }
        if( event.jaxis.axis == 5)
        {
            emit axismoved("p",event.jaxis.value);
        }
    }
}

void joysticksdl::BallMotion(SDL_Event event)
{
    if( event.jball.ball == 0 )
    {
        qDebug()<<"Ball x"<<event.jball.xrel <<"Ball y"<<event.jball.yrel;
    }
}

void joysticksdl::HatMotion(SDL_Event event)
{
    if ( event.jhat.value & SDL_HAT_UP )
    {
        emit axismoved("z",event.jhat.value);
    }

    if ( event.jhat.value & SDL_HAT_DOWN )
    {
        emit axismoved("z",event.jhat.value);
    }
    if ( event.jhat.value & SDL_HAT_LEFT )
    {
        emit axismoved("z",event.jhat.value);
    }
    if ( event.jhat.value & SDL_HAT_RIGHT )
    {
        emit axismoved("z",event.jhat.value);
    }
    if ( event.jhat.value & SDL_HAT_CENTERED )
    {
        emit axismoved("z",event.jhat.value);
    }
    if ( event.jhat.value & SDL_HAT_LEFTDOWN )
    {
        emit axismoved("z",event.jhat.value);
    }
    if ( event.jhat.value & SDL_HAT_LEFTUP )
    {
        emit axismoved("z",event.jhat.value);
    }
    if ( event.jhat.value & SDL_HAT_RIGHTDOWN )
    {
        emit axismoved("z",event.jhat.value);
    }
    if ( event.jhat.value & SDL_HAT_RIGHTUP )
    {
        emit axismoved("z",event.jhat.value);
    }
}

void joysticksdl::checkConnectivity()
{
    SDL_JoystickUpdate();

    if(SDL_JoystickOpened(joystickNumber) && !isConnected){
        isConnected = true;
        //emit connected();
        qDebug()<<"Joystick of index "<<joystickNumber<< "is connected";
    }
    if(!SDL_JoystickOpened(joystickNumber) && isConnected){
        isConnected = false;
        //emit disconnected();
        qDebug()<<"disconnect";
    }
}


void joysticksdl::sCheckAutoRepeat() {
    checkAutoRepeat->stop();
    autoRepeat->start(50);
}

void joysticksdl::sAutoRepeat() {
    emit buttonPressed(currentButton);
    //qDebug()<<currentButton;
}


void joysticksdl::GetNumberOFButtons()
{    qDebug()<< "Number of buttons is " << SDL_JoystickNumButtons(joy);}

void joysticksdl::GetNumberOFAxes()
{    qDebug()<< "Number of Axes is " << SDL_JoystickNumAxes(joy);}

void joysticksdl::GetNumberOFHats()
{    qDebug()<< "Number of Hats is " << SDL_JoystickNumHats(joy);}

void joysticksdl::GetNumberOFBalls()
{    qDebug()<< "Number of Balls is " << SDL_JoystickNumBalls(joy);}

void joysticksdl::GetIndex()
{    qDebug()<< "Index is " << SDL_JoystickIndex(joy);}

void joysticksdl::NumberOfAvailableJS()
{    qDebug()<<"Number of available joysticks"<<SDL_NumJoysticks();}

void joysticksdl::setKind(int id, int kind)
{buttonKinds[id]=kind;}

int joysticksdl::getKind(int id)
{return buttonKinds[id];}

void joysticksdl::ShowJoystickData()
{
    qDebug()<< "Index is " << SDL_JoystickIndex(joy);
    qDebug()<<"Name is" <<SDL_JoystickName(joystickNumber);
    qDebug()<< "Number of buttons is " << SDL_JoystickNumButtons(joy);
    qDebug()<< "Number of Axes is " << SDL_JoystickNumAxes(joy);
    qDebug()<< "Number of Hats is " << SDL_JoystickNumHats(joy);
    qDebug()<< "Number of Balls is " << SDL_JoystickNumBalls(joy);
}

void joysticksdl::ShowAvailableJoysticks()
{
    for(int i=0; i < SDL_NumJoysticks(); i++ )
    { qDebug()<< "Joystick of Index "<<i<<"Has name: " << SDL_JoystickName(i); }
}

