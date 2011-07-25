#include "myview.h"
#include "mycomputer.h"
#include <iostream>
#include <fstream>
#include <QPixmap>
#include"Defense.h"
#include "mainwindow.h"
#include "mydockwidget.h"
#include "mybuilder.h"
#include "myscene.h"
#include "mypushbutton.h"
#include <QPushButton>
#include <QWidget>
#include<QTimer>
#include<QTimerEvent>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QPoint>

using namespace std;
extern QString * sourcePath;


myView::myView(myComputer *comp,QGraphicsScene *parent)
    :QGraphicsView(parent),tracking(true),comp(comp),item(NULL),stateMouseMoving(-1)
{
    QString * path = new QString(*sourcePath);
    money = new QSound(*path+"money.mp3");
    this->setRenderHint(QPainter::Antialiasing);
    this->setCacheMode(QGraphicsView::CacheBackground);
    this->setMouseTracking(false);
    portee = new QGraphicsEllipseItem(0,0,0,0);
    portee->setPen(QPen(Qt::white));
    dynamic_cast<myScene *>(parent)->addItem(portee);
    //connect(dynamic_cast<MainWindow *>(this->getComputer()->parent())->getDock()->getUpdateDefense(),SIGNAL(clicked()),this,SLOT(ameliorerItem()));

}




void myView::enterEvent(QEvent * event)
{
    this->setMouseTracking(true);
    tracking=true;
    emit mouseOnScene();


}
void myView::leaveEvent(QEvent * event)
{
    this->setMouseTracking(true);
    tracking=false;
    emit mouseOutScene();


}

void myView::mouseMoveEvent ( QMouseEvent * event)
{
    if (stateMouseMoving==1)
    {
        emit mouseMoving(event->x(),event->y());
    }
}

void myView::mouseDoubleClickEvent(QMouseEvent *event)
{

}


//QUAND ON CLIQUE SUR UNE TOUR, MONTER OU CACHE SES BOUTON AMELIORER/VENDRE
void myView::mousePressEvent(QMouseEvent * event)
{
    emit mouseClick(event->x(),event->y());
    if (item = itemAt(event->pos()))
    {
            Defense * defenseItem = dynamic_cast<Defense *>(item);
            if ((defenseItem)&&(dynamic_cast<MainWindow *>(this->getComputer()->parent())->getBuilder()->getActivated()==-1))
            {
                defenseItem->setZValue(1500);
                dynamic_cast<MainWindow *>(this->getComputer()->parent())->getScene()->setFront(defenseItem);
                dynamic_cast<MainWindow *>(this->getComputer()->parent())->getDock()->setInfoDefense(defenseItem->getDesc());
                dynamic_cast<MainWindow *>(this->getComputer()->parent())->getDock()->getSellDefense()->show();
                dynamic_cast<MainWindow *>(this->getComputer()->parent())->getDock()->getSellDefense()->setEnabled(true);

                portee->setRect(17+defenseItem->pos().x()-(defenseItem->getPortee()*35),17+defenseItem->pos().y()-(defenseItem->getPortee()*35),defenseItem->getPortee()*2*35,defenseItem->getPortee()*2*35);


                if(defenseItem->getNiveau()<2)
                {
                    dynamic_cast<MainWindow *>(this->getComputer()->parent())->getDock()->getUpdateDefense()->show();

                }
                if((defenseItem->getNiveau()==0)&&(dynamic_cast<myComputer *>(this->getComputer())->getCredit()>=defenseItem->getPrixLvl1()))
                {
                   dynamic_cast<MainWindow *>(this->getComputer()->parent())->getDock()->getUpdateDefense()->setEnabled(true);
                }
                 else if((defenseItem->getNiveau()==1)&&(dynamic_cast<myComputer *>(this->getComputer())->getCredit()>=defenseItem->getPrixLvl2()))
                {
                  dynamic_cast<MainWindow *>(this->getComputer()->parent())->getDock()->getUpdateDefense()->setEnabled(true);
                }
                else
                {
                    dynamic_cast<MainWindow *>(this->getComputer()->parent())->getDock()->getUpdateDefense()->setEnabled(false);

                }
            }
            else
            {
                if(dynamic_cast<MainWindow *>(this->getComputer()->parent())->getBuilder()->getActivated()==-1)
                {
                dynamic_cast<MainWindow *>(this->getComputer()->parent())->getDock()->getUpdateDefense()->hide();
                dynamic_cast<MainWindow *>(this->getComputer()->parent())->getDock()->getSellDefense()->hide();
                dynamic_cast<MainWindow *>(this->getComputer()->parent())->getDock()->setInfoDefense(&QString("Cliquez sur un objet pour en obtenir \nles informations"));
                }


            }
    }
    else
    {
             qDebug() << "Pas d'objet clique";
    }
}


myComputer * myView::getComputer() const
{
    return this->comp;
}
//SETTERS
void myView::setComputer(myComputer * comp)
{
    this->comp=comp;
}


void myView::vendreItem() //REVEND UN OBJET, JOUE UN SON
{
    if(item){
        if(dynamic_cast<Defense*>(item))
        {
            this->getComputer()->setCredit(this->getComputer()->getCredit()+dynamic_cast<Defense*>(item)->revendre());
            dynamic_cast<MainWindow *>(this->getComputer()->parent())->getDock()->getUpdateDefense()->hide();
            dynamic_cast<MainWindow *>(this->getComputer()->parent())->getDock()->getSellDefense()->hide();
            dynamic_cast<MainWindow *>(this->getComputer()->parent())->getDock()->setInfoDefense(&QString("Cliquez sur un objet pour en obtenir \nles informations"));
            portee->setRect(0,0,0,0);
            money->setLoops(1);
            money->play();
            }
        }
}

void myView::ameliorerItem() // SI ON VEUT AMELIORER, VERIFIER QU'ON A LE CREDIT NECESSAIRE ET METTRE A JOUR
{
    if(item){
        if(dynamic_cast<Defense*>(item))
        {
            Defense * defenseItem;
            defenseItem = dynamic_cast<Defense*>(item);
            dynamic_cast<Defense *>(defenseItem)->ameliorer();
            dynamic_cast<MainWindow *>(this->getComputer()->parent())->getDock()->setInfoDefense(defenseItem->getDesc());
            dynamic_cast<MainWindow *>(this->getComputer()->parent())->getDock()->getSellDefense()->show();
            dynamic_cast<MainWindow *>(this->getComputer()->parent())->getDock()->getSellDefense()->setEnabled(true);

            portee->setRect(17+defenseItem->pos().x()-(defenseItem->getPortee()*35),17+defenseItem->pos().y()-(defenseItem->getPortee()*35),defenseItem->getPortee()*2*35,defenseItem->getPortee()*2*35);
            //connect(dynamic_cast<MainWindow *>(this->getComputer()->parent())->getDock()->getUpdateDefense(),SIGNAL(clicked()),this,SLOT(ameliorerItem()));

            if(defenseItem->getNiveau()<2)
            {
                dynamic_cast<MainWindow *>(this->getComputer()->parent())->getDock()->getUpdateDefense()->show();

            }
            if((defenseItem->getNiveau()==0)&&(dynamic_cast<myComputer *>(this->getComputer())->getCredit()>=defenseItem->getPrixLvl1()))
            {
               dynamic_cast<MainWindow *>(this->getComputer()->parent())->getDock()->getUpdateDefense()->setEnabled(true);
            }
             else if((defenseItem->getNiveau()==1)&&(dynamic_cast<myComputer *>(this->getComputer())->getCredit()>=defenseItem->getPrixLvl2()))
            {
              dynamic_cast<MainWindow *>(this->getComputer()->parent())->getDock()->getUpdateDefense()->setEnabled(true);
            }
            else
            {
                dynamic_cast<MainWindow *>(this->getComputer()->parent())->getDock()->getUpdateDefense()->setEnabled(false);

            }

        }
    }

}

void myView::switchMouseMoving()
{
    stateMouseMoving=stateMouseMoving*-1;
}
