#include "guepe.h"
#include "myScene.h"
#include <QList>
#include <QGraphicsItem>
#include <QObject>
#include <math.h>

Guepe::Guepe(int x, int y,float taille,QGraphicsScene *scene): Insecte(dynamic_cast<myScene*>(scene)->animationGuepe,dynamic_cast<myScene*>(scene)->sonGuepe,taille,2,3,4,7,scene)
{
    hp=7*pow(taille,2);
    resistance=4*pow(taille,2);
    vitesse=3;
    this->setPos(x*35,y*35);
    degatZone=5*pow(taille,2);
}

float Guepe::getDegatZone() const //retourne la valeur des dégats de zone infligés par la guepe quand elle meurt
{
    return this->degatZone;
}
