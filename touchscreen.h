#ifndef MAINSCREEN_H
#define MAINSCREEN_H


#include <QWidget>
#include <qobject.h>
#include "qlabel.h"
#include "mpvwidget.h"
#include "qtimer.h"
#include "alphaVideoPlayer.h"
#include "QPropertyAnimation"
#include "powerLabel.h"
class touchScreen : public QLabel
{
    Q_OBJECT
public:
    explicit touchScreen(QLabel *parent = nullptr, QString PATH="");

private:
    QString PATH;
    mpvWidget *bgVp,*introVp;
    alphaVideo *alphaVp;


    std::vector<powerLabel*> buttons;
    powerLabel *summaryLbl;

    std::vector<powerLabel *> contentTitles,contentFrames;
    powerLabel *backLbl;
    int nextContent;

private slots:
    void loadPlayer(void);
    void showSummary(void);
    void buttonClick(void);
    void hideSummary(void);
    void selectContent(int contentId);
    void showContent(void);
    void hideContent(void);
    void goBack(void);
    void startIntroVideo(void);
    void stopIntroVideo(void);
signals:
    void bgShouldRestart(void);

};

#endif // MAINSCREEN_H
