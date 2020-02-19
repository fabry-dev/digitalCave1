#include "powerLabel.h"

powerLabel::powerLabel(QLabel *parent, int id, QRect hideGeo, QRect showGeo,bool zoomOnClick) : QLabel(parent),id(id),hideGeo(hideGeo),showGeo(showGeo),zoomOnClick(zoomOnClick)
{
    hide();
    setGeometry(hideGeo);
    showAnim = new QPropertyAnimation(this,"geometry");
    showAnim->setDuration(400);
    showAnim->setEasingCurve(QEasingCurve::InCurve);
    showAnim->setStartValue(hideGeo);
    showAnim->setEndValue(showGeo);

    hideAnim = new QPropertyAnimation(this,"geometry");
    hideAnim->setDuration(400);
    hideAnim->setEasingCurve(QEasingCurve::InCurve);
    hideAnim->setStartValue(showGeo);
    hideAnim->setEndValue(hideGeo);
    connect(hideAnim,SIGNAL(finished()),this,SLOT(hide()));
    connect(hideAnim,SIGNAL(finished()),this,SIGNAL(hideAnimationOver()));


    zoomIn = new QPropertyAnimation(this,"geometry");
    zoomIn->setDuration(100);
    zoomIn->setEasingCurve(QEasingCurve::InCurve);

    zoomOut = new QPropertyAnimation(this,"geometry");
    zoomOut->setDuration(100);
    zoomOut->setEasingCurve(QEasingCurve::InCurve);
}

int powerLabel::getId() const
{
    return id;
}


void powerLabel::mousePressEvent(QMouseEvent *ev)
{
    if(hideAnim->state() == QAbstractAnimation::Running)
        return;
    if(showAnim->state() == QAbstractAnimation::Running)
        return;
    if(zoomIn->state() == QAbstractAnimation::Running)
        return;
    if(zoomOut->state() == QAbstractAnimation::Running)
        return;


    if(zoomOnClick)
    {


        zoomIn->setStartValue(this->geometry());
        int centerX = x()+width()/2;
        int centerY = y()+height()/2;
        int nuWidth = (double)width()*1.1;
        int nuHeight = (double)height()*1.1;
        zoomIn->setEndValue(QRect(centerX-nuWidth/2,centerY-nuHeight/2,nuWidth,nuHeight));



        zoomOut->setEndValue(this->geometry());
        zoomOut->setStartValue(QRect(centerX-nuWidth/2,centerY-nuHeight/2,nuWidth,nuHeight));

        connect(zoomIn,SIGNAL(finished()),zoomOut,SLOT(start()));
        connect(zoomOut,SIGNAL(finished()),this,SIGNAL(clicked()));






        // connect(zoomIn,SIGNAL(finished()),this,SLOT(hide()));
        zoomIn->start(QAbstractAnimation::KeepWhenStopped);

    }
    else
        emit clicked();
}


void powerLabel::animateHide(void)
{
    hideAnim->start();
}

void powerLabel::animateShow(void)
{
    show();
    showAnim->start();
}
