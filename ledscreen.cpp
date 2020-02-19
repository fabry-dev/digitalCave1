#include "ledscreen.h"
#include "math.h"
#include "qdebug.h"
#include "qthread.h"
#include "qlayout.h"

#include "qmediaplayer.h"

double Touch2Led = (double)53.1/250; //size led = size touch * Touch2Led
ledScreen::ledScreen(QLabel *parent, QString PATH) : QLabel(parent),PATH(PATH)
{

    resize(960,1152);

    bgVp = new mpvWidget(this);
    bgVp->resize(size());
    bgVp->setProperty("keep-open","yes");
    bgVp->setLoop(true);
    bgVp->show();

    connect(bgVp,SIGNAL(videoRestart()),this,SIGNAL(bgRestart()));


    introVp = new mpvWidget(this);
    introVp->resize(size());
    introVp->setMute(true);
    introVp->setProperty("keep-open","yes");
    introVp->setLoop(false);
    introVp->lower();
    introVp->show();





    QTimer::singleShot(10,this,SLOT(loadPlayer()));



    QLabel *touchLbl = new QLabel(this);
    touchLbl->resize(1080*Touch2Led,1920*Touch2Led);
    touchLbl->move((width()-touchLbl->width())/2,(height()-touchLbl->height())/2);
    touchLbl->setStyleSheet("border: 1px solid red");
    touchLbl->show();


}

void ledScreen::loadPlayer()
{
    bgVp->lower();
    bgVp->loadFilePaused(PATH+"ledBg1.mp4");
    bgVp->play();

    introVp->lower();
   introVp->loadFilePaused(PATH+"ledIntro1.mp4");
}




void ledScreen::startIntroVideo()
{
    introVp->playAndRaise();
    introVp->raise();

}

void ledScreen::stopIntroVideo()
{
    introVp->lower();
    introVp->pause();
    introVp->rewind();
}














void ledScreen::keyPressEvent(QKeyEvent *ev)
{
  if(ev->key() == 16777216)
        exit(0);



  //qDebug()<<ev->key();
}



