#include "fourmi.h"
#include "myScene.h"
#include <QList>
#include <QGraphicsItem>
#include <QObject>
#include <math.h>
                                                                                                                                //2
Fourmi::Fourmi(int x, int y,float taille,QGraphicsScene *scene): Insecte(dynamic_cast<myScene*>(scene)->animationFourmi,dynamic_cast<myScene*>(scene)->sonFourmi,taille,1,2,1,5,scene)
{

 hp=5*pow(taille,2);
 resistance=1*pow(taille,2);
 vitesse=2+taille/2;
 this->setPos(x*35,y*35);
 connect(&(this->tAccelerer),SIGNAL(timeout()),this,SLOT(slotVitesseBackNormal()));
}

//rampant hp 5,resist1,vitesse2

void Fourmi::recevoirDegat(float degat)
{
    float deg = (degat-resistance);
    if (deg<0)
    {
        deg=1;
    }
    hp-=deg;
    if(!tAccelerer.isActive()) //si la fourmi n'est pas déjà entrain d'accelerer, accelerer
    {
        tAccelerer.setSingleShot(true);
        tAccelerer.setInterval(20*50*5);
        tAccelerer.start();
        this->accelerer();
    }

}

void Fourmi::accelerer()
{

    this->vitesse=vitesse*1,5;
}

void Fourmi::vitesseBackNormal()
{

    this->vitesse=vitesse/1,5;
}
