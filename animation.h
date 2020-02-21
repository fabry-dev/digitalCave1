#ifndef ANIMATION_H
#define ANIMATION_H

#include <QWidget>
#include <QWidget>
#include <QLabel>
#include "qdebug.h"
#include "QMouseEvent"
#include "QPropertyAnimation"
#include "powerLabel.h"

class animation : public QWidget
{
    Q_OBJECT
public:
    explicit animation(QWidget *parent = nullptr, QString PATH="", QRect hidePoint=QRect(0,0,0,0),QRect showPoint=QRect(0,0,0,0));
    std::vector<powerLabel*>tiles;

private:
    QString PATH;
    QRect hidePoint,showPoint;
    QPropertyAnimation *hideAnim;

signals:

public slots:
    void start(void);
    void animateHide(void);
};

#endif // ANIMATION_H
