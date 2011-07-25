#ifndef MYVIEW_H
#define MYVIEW_H

#include <QGraphicsView>
#include <QBrush>
#include <QGraphicsRectItem>
#include <QtGui/QtGui>
#include <iostream>
#include <QSound>
class myComputer;

class myView : public QGraphicsView
{
    Q_OBJECT
public:
    //CONSTRUCTOR
    explicit myView(myComputer *comp,QGraphicsScene *parent = 0);

    //EVENTS
    void mouseMoveEvent ( QMouseEvent * event );
    void leaveEvent(QEvent * event);
    void enterEvent(QEvent * event);
    void mousePressEvent(QMouseEvent * event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    //GETTERS
    myComputer * getComputer() const;
    //SETTERS
    void setComputer(myComputer * comp);
private:
    bool tracking; //=true si curseur au dessus de la scene, false sinon
    myComputer* comp;//=reference vers le gestionnaire principal
    QGraphicsItem *item;
    QGraphicsEllipseItem * portee;
    int stateMouseMoving;
    QSound *money;

signals:
    void mouseOnScene(); //signal envoyé lorsque le curseur entre sur la scene
    void mouseOutScene(); //signal envoyé lorsque le curseur sort de la scene
    void mouseMoving(float x, float y); //signal envoyé lorsque le curseur se deplace sur la scene
    void mouseClick(float x, float y);
    void mouseDoubleClick();
public slots:
    void ameliorerItem();
    void vendreItem();
    void switchMouseMoving();
};

#endif // MYVIEW_H
