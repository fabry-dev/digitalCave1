#ifndef SIMPLEBUTTON_H
#define SIMPLEBUTTON_H

#include <QWidget>
#include <QLabel>
#include "qdebug.h"
#include "QMouseEvent"
#include "QPropertyAnimation"
class powerLabel : public QLabel
{
    Q_OBJECT
public:
    explicit powerLabel(QLabel *parent = nullptr, int id=0, QRect hideGeo=QRect(0,0,0,0), QRect showGeo=QRect(0,0,0,0), bool zoomOnClick=false);

    int getId() const;

signals:
    void clicked();
    void hideAnimationOver(void);

private:
    int id;
    QRect hideGeo,showGeo;
    QPropertyAnimation *showAnim,*hideAnim;
    bool zoomOnClick;

public slots:
    void animateShow(void);
    void animateHide(void);

protected:
    void mousePressEvent(QMouseEvent *ev);
};

#endif // SIMPLEBUTTON_H
