#include "musicien.h"
#include <QGraphicsItem>
#include <QBrush>
#include <QPen>
#include <QPainter>
#include "myscene.h"
#include "mycomputer.h"
#include <iostream>
using namespace std;


// CHAQUE DEFENSE DISPOSE DE :

//Constructeur qui initialise la base Defense en fonction de son mode de départ
//Etablissement de la description en fonction de ses carateristiques
//Amelioration de ses caracteristiques en fonction de son mode d'évolution


Musicien::Musicien(QSound * s, bool enable,QGraphicsItem *parent) : Defense(s,enable,1.5,0,0,0,0,15,40,80,40,3,QColor(89,208,242,0),parent)
{
    percent=20;
    this->desc=new QString("Musicien");
    if(son->isFinished())
    {
    this->son->setLoops(-1);
    this->son->play();
    }
}

void Musicien::ameliorer()
{
    {
        if((niveau==0)&&(dynamic_cast<myScene *>(this->scene())->getComputer()->getCredit()>=prixLvl1))
        {
            dynamic_cast<myScene *>(this->scene())->getComputer()->setCredit(dynamic_cast<myScene *>(this->scene())->getComputer()->getCredit()-prixLvl1);
            niveau++;
            percent=40;
            this->setScale(1.2);
            this->updateDesc();
        }
        else if((niveau==1)&&(dynamic_cast<myScene *>(this->scene())->getComputer()->getCredit()>=prixLvl2))
        {
            dynamic_cast<myScene *>(this->scene())->getComputer()->setCredit(dynamic_cast<myScene *>(this->scene())->getComputer()->getCredit()-prixLvl2);
            niveau++;
            percent=60;
            this->setScale(1.2);
            this->updateDesc();
        }
        else
        {
            //cerr<<"niveau :"<<niveau<<endl;
            //cerr<<dynamic_cast<myScene *>(this->scene())->getComputer()->getCredit()<<" et vaut :"<<prixLvl2<<endl;
           // cerr<<"pas assez d'argent dans pistolet à eau";
            wrong->setLoops(1);
            wrong->play();
        }
    }


};

void Musicien::paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    painter->setPen(QPen(Qt::NoPen));
    painter->setBrush(QPixmap(":/defenses/musicien.png"));
    painter->drawRect(0, 0, 35, 35);
    painter->setPen(QPen(Qt::NoPen));
    painter->setBrush(Qt::NoBrush);
    painter->drawEllipse(17-portee*35, 17-portee*35, portee*2*35, portee*2*35);

}

QRectF Musicien::boundingRect() const
{
    return QRectF(17-portee*35, 17-portee*35, portee*2*35, portee*2*35);
}

QPainterPath Musicien::shape() const
 {
     QPainterPath path;
     path.addEllipse(17-portee*35, 17-portee*35, portee*2*35, portee*2*35);
     return path;
 }

int Musicien::getPercent() const
{
    return this->percent;
}

Musicien::~Musicien()
{
    dynamic_cast<myScene*>(this->scene())->removeMusicien(this);
    dynamic_cast<myScene*>(this->scene())->updateMusicien();
}


void Musicien::updateDesc()
{
    QString res ("Musicien niveau ");
    QString temp(QString::number(this->niveau));
    res = res+temp;
    temp = QString(":\n\n**Bonus**\nPortee: ");
    res = res+temp;
    temp = QString(QString::number(this->portee));
    res = res+temp;
    temp = QString(":\n\nAmeliore defense de: ");
    res = res+temp;
    temp = QString(QString::number(this->percent));
    res = res+temp;
    temp = QString(" %\n");
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
