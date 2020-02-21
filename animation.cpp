#include "animation.h"


int xs[10] = {205,380,540,700,860,920,900,720,540,360};

int ys[10] = {200,200,200,200,200,320,440,440,440,440};

animation::animation(QWidget *parent, QString PATH, QRect hidePoint, QRect showPoint) : QWidget(parent),PATH(PATH),hidePoint(hidePoint),showPoint(showPoint)
{
    setGeometry(showPoint);


    for(int i = 0;i<=10;i++)
    {
        QPixmap pix(PATH+"animation/"+QString::number(i));
        QRect showGeo = QRect(xs[i]-pix.width()/2,ys[i]-pix.height()/2,pix.width(),pix.height());
        QRect hideGeo = QRect(showGeo.x()+pix.width()/2,showGeo.y()+pix.height()/2,0,0);
         powerLabel *lbl = new powerLabel((QLabel*)this,i,hideGeo,showGeo);
        lbl->setPixmap(pix);
        lbl->setScaledContents(true);
        lbl->hide();
        tiles.push_back(lbl);
        if(i>0)
        connect(tiles[i-1],SIGNAL(showAnimationOver()),lbl,SLOT(animateShow()));
    }


    hideAnim = new QPropertyAnimation(this,"geometry");
    hideAnim->setDuration(400);
    hideAnim->setEasingCurve(QEasingCurve::InCurve);
    hideAnim->setStartValue(geometry());
    hideAnim->setEndValue(hidePoint);
    connect(hideAnim,SIGNAL(finished()),this,SLOT(hide()));

}



void animation::start(void)
{
        show();
        setGeometry(showPoint);


        tiles[0]->animateShow();

}

void animation::animateHide()
{

    for(auto t:tiles)
        t->animateHide();
    hideAnim->start();

}
