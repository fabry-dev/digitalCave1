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

}

int powerLabel::getId() const
{
    return id;
}


void powerLabel::mousePressEvent(QMouseEvent *ev)
{
    if(zoomOnClick)
    {
        QPropertyAnimation *zoomIn = new QPropertyAnimation(this,"geometry");
        zoomIn->setDuration(100);
        zoomIn->setEasingCurve(QEasingCurve::InCurve);
        zoomIn->setStartValue(this->geometry());
        int centerX = x()+width()/2;
        int centerY = y()+height()/2;
        int nuWidth = (double)width()*1.1;
        int nuHeight = (double)height()*1.1;
        zoomIn->setEndValue(QRect(centerX-nuWidth/2,centerY-nuHeight/2,nuWidth,nuHeight));


        QPropertyAnimation *zoomOut = new QPropertyAnimation(this,"geometry");
        zoomOut->setDuration(100);
        zoomOut->setEasingCurve(QEasingCurve::InCurve);
        zoomOut->setEndValue(this->geometry());
        zoomOut->setStartValue(QRect(centerX-nuWidth/2,centerY-nuHeight/2,nuWidth,nuHeight));

        connect(zoomIn,SIGNAL(finished()),zoomOut,SLOT(start()));
        connect(zoomOut,SIGNAL(finished()),zoomOut,SLOT(deleteLater()));
        connect(zoomOut,SIGNAL(finished()),this,SIGNAL(clicked()));






       // connect(zoomIn,SIGNAL(finished()),this,SLOT(hide()));
        zoomIn->start(QAbstractAnimation::DeleteWhenStopped);

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
