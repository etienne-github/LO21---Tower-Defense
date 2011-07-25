#include "pistolet_eau.h"
#include <QGraphicsItem>
#include <QBrush>
#include <QPen>
#include <QPainter>
#include "mainwindow.h"
#include "math.h"
#include<QString>
#include<QObject>
#include<iostream>
#include "myscene.h"
#include "mycomputer.h"

using namespace std;

// CHAQUE DEFENSE DISPOSE DE :

//Constructeur qui initialise la base Defense en fonction de son mode de départ
//Etablissement de la description en fonction de ses carateristiques
//Amelioration de ses caracteristiques en fonction de son mode d'évolution

Pistolet_eau::Pistolet_eau(QSound* s,bool enable,QGraphicsItem *parent) : Defense(s,enable,2,4,5,0,3,8,20,45,40,3,QColor(89,208,242),parent)
{
    //connect(dynamic_cast<myView*>(this),SIGNAL(mouseClick(float,float)),this,SLOT(isClicked()));
    this->desc = new QString;
//this->setZValue(2000);
//this->setAcceptedMouseButtons(Qt::LeftButton);
    this->updateDesc();
}


void Pistolet_eau::paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    painter->setPen(QPen(Qt::NoPen));
    painter->setBrush(QPixmap(":/defenses/pistolet-eau.png"));
    painter->drawRect(0, 0, 35, 35);
    painter->setPen(QPen(Qt::NoPen));
    painter->setBrush(Qt::NoBrush);
    painter->drawEllipse(17-portee*35, 17-portee*35, portee*2*35, portee*2*35);

}

QRectF Pistolet_eau::boundingRect() const
{
    return QRectF(17-portee*35, 17-portee*35, portee*2*35, portee*2*35);
}

QPainterPath Pistolet_eau::shape() const
 {
    QPainterPath path;
    path.addEllipse(17-portee*35, 17-portee*35, portee*2*35, portee*2*35);
    return path;
 }


void Pistolet_eau::ameliorer()
{
    if((niveau==0)&&(dynamic_cast<myScene *>(this->scene())->getComputer()->getCredit()>=prixLvl1))
    {
        dynamic_cast<myScene *>(this->scene())->getComputer()->setCredit(dynamic_cast<myScene *>(this->scene())->getComputer()->getCredit()-prixLvl1);
        niveau++;
        portee=2+niveau/2;
        cadence=4-niveau/2;
        frappe=5*pow(niveau,1.5);
        this->setScale(1.2);
        this->updateDesc();
    }
    else if((niveau==1)&&(dynamic_cast<myScene *>(this->scene())->getComputer()->getCredit()>=prixLvl2))
    {
        dynamic_cast<myScene *>(this->scene())->getComputer()->setCredit(dynamic_cast<myScene *>(this->scene())->getComputer()->getCredit()-prixLvl2);
        niveau++;
        portee=2+niveau/2;
        cadence=4-niveau/2;
        frappe=5*pow(niveau,1.5);
        this->setScale(1.2);
        this->updateDesc();
    }
    else
    {
        cerr<<"niveau :"<<niveau<<endl;
        cerr<<dynamic_cast<myScene *>(this->scene())->getComputer()->getCredit()<<" et vaut :"<<prixLvl2<<endl;
        //cerr<<"pas assez d'argent dans pistolet à eau";
        wrong->setLoops(1);
        wrong->play();
    }

};


void Pistolet_eau::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    cerr<<"T'as cliqué sur un pistolet a eau";
}

/*void Pistolet_eau::isClicked()
{
    if(this->isSelected())
    {
        cerr<<"Je suis cliqué";
    }
}*/

void Pistolet_eau::updateDesc()
{
    QString res ("Tireur au pistolet a eau niveau ");
    QString temp(QString::number(this->niveau));
    res = res+temp;
    temp = QString(":\n\nCible: Volants et Rampants\nPortee: ");
    res = res+temp;
    temp = QString(QString::number(this->portee));
    res = res+temp;
    temp = QString("\nCadence: ");
    res = res+temp;
    temp = QString(QString::number(this->cadence));
    res = res+temp;
    temp = QString("\nFrappe: ");
    res = res+temp;
    temp = QString(QString::number(this->frappe));
    res = res+temp;
    if (this->niveau==0)
    {
    temp = QString("\nAmeliorer: ");
    res = res+temp;
    temp = QString(QString::number(this->prixLvl1));
    res = res+temp;
    temp = QString(" credits | ");
    res = res+temp;
    temp = QString("Revente: ");
    res = res+temp;
    temp = QString(QString::number(this->prixBase/2));
    res = res+temp;
    temp = QString(" credits");
    res = res+temp;
    }
    else if (this->niveau==1)
    {
    temp = QString("\nAmeliorer: ");
    res = res+temp;
    temp = QString(QString::number(this->prixLvl2));
    res = res+temp;
    temp = QString(" credits | ");
    res = res+temp;
    temp = QString("Revente: ");
    res = res+temp;
    temp = QString(QString::number((prixBase+prixLvl1)/2));
    res = res+temp;
    temp = QString(" credits");
    res = res+temp;
    }
    else
    {
        temp = QString("Revente: ");
        res = res+temp;
        temp = QString(QString::number((prixBase+prixLvl1+prixLvl2)/2));
        res = res+temp;
        temp = QString(" credits");
        res = res+temp;
    }
    *(this->desc)=res;

}
