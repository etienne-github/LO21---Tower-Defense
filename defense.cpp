#include "defense.h"
#include <QGraphicsItem>
#include <iostream>
#include <QPainter>
#include <QObject>
#include "insecte.h"
#include "fourmi.h"
#include <math.h>
#include "myscene.h"
using namespace std;

extern QString * sourcePath;

Defense::Defense(QGraphicsItem *parent) :QObject(0),
    QGraphicsItem(parent)
{
}

Defense::Defense(QSound * son, bool enable,float portee,float cadence,float frappe,int niveau, int type,int prixBase,int prixLvl1,int prixLvl2,float vitProj,float tailleProj,QColor couleurProj,QGraphicsItem *parent) :
    QGraphicsItem(parent),portee(portee),cadence(cadence),frappe(frappe),niveau(niveau),type(type),enable(enable),prixBase(prixBase),prixLvl1(prixLvl1),prixLvl2(prixLvl2),shoot(true),vitProj(vitProj),tailleProj(tailleProj),couleurProj(couleurProj),son(son),upgrade(0)
{
    QString * path = new QString(*sourcePath);
    wrong = new QSound(*path+"wrong.mp3");
    setTransformOriginPoint(17,17);
    connect(&(this->tCadence),SIGNAL(timeout()),this,SLOT(enableShoot()));
}



void Defense::paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    painter->setPen(QPen(Qt::NoPen));
    painter->setBrush(Qt::blue);
    painter->drawEllipse(0, 0, 35, 35);
    painter->setPen(QPen(Qt::yellow));
    painter->setBrush(Qt::NoBrush);
    painter->drawEllipse(17-portee*35, 17-portee*35, portee*2*35, portee*2*35);
}

QRectF Defense::boundingRect() const
{
    return QRectF(17-portee*35, 17-portee*35, portee*2*35, portee*2*35);
}

QPainterPath Defense::shape() const
 {
    QPainterPath path;
    path.addEllipse(17-portee*35, 17-portee*35, portee*2*35, portee*2*35);
    return path;
 }

//GETTERS

float Defense::getPortee() const
{
    return this->portee;
}
float Defense::getCadence() const
{
    return this-> cadence;
}
float Defense::getFrappe() const
{
    return this->frappe;
}
int Defense::getNiveau() const
{
    return this->niveau;
}
int Defense::getType() const
{
    return this->type;
}
int Defense::getPrixBase() const
{
    return this->prixBase;
}
int Defense::getPrixLvl1() const
{
    return this->prixLvl1;
}
int Defense::getPrixLvl2() const
{
    return this->prixLvl2;
}

QString* Defense::getDesc() const
{
    return this->desc;
}

//SETTERS
void Defense::setPortee(float portee)
{
    this->portee=portee;
}
void Defense::setCadence(float cadence)
{
    this->cadence=cadence;
}
void Defense::setFrappe(float frappe)
{
    this->frappe=frappe;
}
void Defense::setNiveau(int niveau)
{
    this->niveau=niveau;
}
void Defense::setType(int type)
{
    this->type=type;
}
void Defense::setDesc(QString * desc)
{
    this->desc = desc;
}

Defense::~Defense()
{
    dynamic_cast<myScene*>(this->scene())->removeDefense(this);
};

int Defense::revendre() //detruit la tour et retourne la moitié de la valeur cumulée de la defense
{
    int ret;
    switch(niveau)
    {
    case 0:
        ret = prixBase/2;
        break;
    case 1:
        ret = (prixBase+prixLvl1)/2;
        break;
    case 2:
        ret = (prixBase+prixLvl1+prixLvl2)/2;
        break;
    default : break;

    }
    delete this;
    return ret;
}

void Defense::disableShoot() //empêche la tour de tirer pdt un temps de 1/cadence
{
    shoot = false;
    tCadence.setSingleShot(true);
    tCadence.setInterval(20*50*(1/cadence));
    tCadence.start();
}



bool Defense::canShoot() const //retourne false si la tour est d'un une phase bloquée et true sinon
{
    return shoot;
}

void Defense::enableShoot()
{
    shoot = true;
}

float Defense::getTailProj()
{
    return this->tailleProj;
}

float Defense::getVitProj()
{
    return this->vitProj;
}

QColor Defense::getColProj()
{
   return this->couleurProj;
}

QSound * Defense::getSound() const
{
    return this->son;
}

void Defense::suivre(Insecte * insecte) //rotatione la tour pour qu'elle suive l'insecte visé.
{
    qreal xI=insecte->pos().x()/*+insecte->boundingRect().width()/2*/;
    qreal yI=insecte->pos().y()/*+insecte->boundingRect().height()/2*/;
    qreal xD= this->pos().x()/*+this->boundingRect().width()/2*/;
    qreal yD= this->pos().y()/*+this->boundingRect().height()/2*/;
    cerr<<"xI: "<<xI<<" | yI: "<<yI<<endl;
    cerr<<"xD: "<<xD<<" | yI: "<<yD<<endl;
    qreal DeltaX = xI-xD;
    qreal DeltaY = yI-yD;
    qreal Angle;

        //effectue artcan(coté opposé sur adjacent) (+ pi si cadrant sensible)

            if (DeltaX == 0)
            {
                    if (DeltaY < 0)
                            Angle = -M_PI/2;
                    else
                            Angle = M_PI/2;
            }

            //Cas "Normaux"
            else
                    {
                    Angle = atan(DeltaY / DeltaX);
                    if (DeltaX < 0)
                            Angle = Angle + M_PI;
            }

            //Angle Positif
            if (Angle < 0)
                    Angle = Angle + 2 * M_PI;
            Angle=Angle*(360.0/M_PI);
            this->setRotation(Angle+80);
}

void Defense::checkUpgrade(int percent) //affecte la tour avec un pourcentage d'amelioration
{
    if(percent!=upgrade)
    {
        cerr<<"On ameliore de "<<percent<<" %"<<endl;
        frappe-=frappe*(upgrade/100.0);
        upgrade=percent;
        frappe+=frappe*(upgrade/100.0);
        this->updateDesc();
    }
}
