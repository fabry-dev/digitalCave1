#include "touchscreen.h"
#include "math.h"
#include "qdebug.h"


#define TIMEOUT_DELAY 30*1000

touchScreen::touchScreen(QLabel *parent, QString PATH) : QLabel(parent),PATH(PATH)
{
    resize(1080,1920);

    bgVp = new mpvWidget(this);
    bgVp->resize(size());
    bgVp->setProperty("keep-open","yes");
    bgVp->setLoop(false);
    bgVp->show();

    connect(this,SIGNAL(bgShouldRestart()),bgVp,SLOT(rewindAndPlay()));


    introVp = new mpvWidget(this);
    introVp->resize(size());
    introVp->setProperty("keep-open","yes");
    introVp->setLoop(false);
    introVp->lower();
    introVp->setMute(true);
    introVp->show();



    QLabel *iktvaLbl = new QLabel(this);
    QImage iktva(PATH+"iktva.png");
    iktvaLbl->resize(iktva.size());
    iktvaLbl->setPixmap(QPixmap::fromImage(iktva));
    iktvaLbl->move((width()-iktvaLbl->width())/2,1920-iktvaLbl->height()/2-100);
    iktvaLbl->show();



    QTimer::singleShot(10,this,SLOT(loadPlayer()));


    int buttonW = 359;
    int buttonH = 215;
    int buttonY = 960;
    int spacingX = (width()-2*buttonW)/3;
    int spacingY = 450;
    for(int i = 0;i<4;i++)
    {
        powerLabel *b = new powerLabel(this,i,QRect(width()/2,buttonY+buttonH+spacingY/2,0,0),QRect(spacingX*((i%2)+1)+buttonW*(i%2),buttonY+spacingY*(i/2),buttonW,buttonH),true);
        b->hide();
        QPixmap pix(PATH+"button"+QString::number(i+1)+".png");
        b->setPixmap(pix);
        b->setScaledContents(true);
        connect(b,SIGNAL(clicked()),this,SLOT(buttonClick()));

        buttons.push_back(b);
    }

    int summaryY = 0;

    QPixmap summary(PATH+"summary.png");
    summaryLbl = new powerLabel(this,0,QRect(width()/2,buttonY+buttonH+spacingY/2,0,0),QRect((width()-summary.width())/2,summaryY,summary.width(),summary.height()));
    summaryLbl->setScaledContents(true);
    summaryLbl->setPixmap(summary);
    summaryLbl->setAttribute( Qt::WA_TransparentForMouseEvents );
    connect(summaryLbl,SIGNAL(hideAnimationOver()),this,SLOT(showContent()));


    int originY = 0;
    int backY = 1500;
    for(int i = 0;i<4;i++)
    {
        QPixmap pix0(PATH+"title"+QString::number(i+1)+".png");
        QPixmap pix1(PATH+"content"+QString::number(i+1)+".png");

        int titleY = (height())/5-pix0.height()/2;
        int contentY =(height()-pix1.height())/2;
        originY = (backY + contentY +titleY)/3;

        QRect geoOrigin = QRect(width()/2,originY,0,0);
        QRect geoTitle = QRect((width()-pix0.width())/2,titleY,pix0.width(),pix0.height());
        QRect geoContent = QRect((width()-pix1.width())/2,contentY,pix1.width(),pix1.height());
        if(i==3)
        {
            geoOrigin = QRect(width()/2,originY,0,0);
            geoTitle = QRect((width()-pix0.width())/2,titleY-150,pix0.width(),pix0.height());
            geoContent = QRect((width()-pix1.width())/2,contentY-200,pix1.width(),pix1.height());
        }

        powerLabel *c0 = new powerLabel(this,i,geoOrigin,geoTitle);
        powerLabel *c1 = new powerLabel(this,i,geoOrigin,geoContent);

        c0->hide();
        c0->setPixmap(pix0);
        c0->setScaledContents(true);
        contentTitles.push_back(c0);

        c1->hide();
        c1->setPixmap(pix1);
        c1->setScaledContents(true);
        contentFrames.push_back(c1);
    }

    anim3 = new animation(this,PATH,QRect(width()/2,0,0,0),QRect(0,1000,1080,500));
    connect(contentTitles[3],SIGNAL(showAnimationOver()),anim3,SLOT(start()));

    anim3->hide();



    QPixmap pix(PATH+"back.png");
    backLbl = new powerLabel(this,0,QRect(width()/2,originY,0,0),QRect((width()-pix.width())/2,backY,pix.width(),pix.height()),true);
    backLbl->hide();
    backLbl->setPixmap(pix);
    backLbl->setScaledContents(true);
    connect(backLbl,SIGNAL(clicked()),this,SLOT(goBack()));
    connect(backLbl,SIGNAL(hideAnimationOver()),this,SLOT(showSummary()));


    timeOutTimer = new QTimer(this);
    connect(timeOutTimer,SIGNAL(timeout()),this,SLOT(hideContent()));

    //showSummary();
    selectContent(3);
}





void touchScreen::loadPlayer()
{

    bgVp->loadFilePaused(PATH+"touchBg1.mp4");
    bgVp->play();

    introVp->loadFilePaused(PATH+"touchIntro1.mp4");
}


void touchScreen::startIntroVideo()
{
    introVp->playAndRaise();
    introVp->raise();

}

void touchScreen::stopIntroVideo()
{
    introVp->lower();
    introVp->pause();
    introVp->rewind();
}





void touchScreen::showSummary()
{
    for(auto b:buttons)
        b->animateShow();
    summaryLbl->animateShow();

    timeOutTimer->stop();
}

void touchScreen::hideSummary()
{
    for(auto b:buttons)
        b->animateHide();
    summaryLbl->animateHide();
}



void touchScreen::selectContent(int contentId)
{
    nextContent = contentId;

    hideSummary();


    timeOutTimer->start(TIMEOUT_DELAY);
}


void touchScreen::showContent()
{
    if(nextContent<0)
        return;
    if(nextContent>=contentFrames.size())
        return;

    contentFrames[nextContent]->animateShow();
    contentTitles[nextContent]->animateShow();
    backLbl->animateShow();



}

void touchScreen::hideContent()
{
    for(auto c:contentFrames)
        if(c->isVisible())
            c->animateHide();

    for(auto c:contentTitles)
        if(c->isVisible())
            c->animateHide();


    if(anim3->isVisible())
        anim3->animateHide();
    backLbl->animateHide();
}



void touchScreen::buttonClick(void)
{
    powerLabel *button = (powerLabel*)QObject::sender();
    selectContent(button->getId());
}

void touchScreen::goBack()
{
    hideContent();
}

