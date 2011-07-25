#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QObject>
#include <QPushButton>
#include <QString>

#include<QPalette>
class myDockWidget;

class myPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit myPushButton(int i, QColor c, QString s,myDockWidget *parent = 0);
    void mousePressEvent(QMouseEvent * e);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    QPalette * basicPalette;
    QPalette * pressedPalette;
    int getI() const;
private:
    myDockWidget * dock;
    QString sauvegarde;
    bool sauvegarde_sell;
    bool sauvegarde_update;
    int i;
    bool enable;
signals:
    void myClicked(int i);

public slots:
    void myUnable();
    void myLink();
};

#endif // MYPUSHBUTTON_H
