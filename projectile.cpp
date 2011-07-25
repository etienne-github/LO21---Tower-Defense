#include "projectile.h"
#include <QPainter>
#include "insecte.h"
#include "defense.h"
#include <math.h>
#include <iostream>
#include <QGraphicsScene>
#include "myscene.h"
#include "petanque.h"
#include "paintball.h"

using namespace std;
Projectile::Projectile(QSound * son, float taille,int type, float degat, float Vitesse, QColor couleur, Defense* source, Insecte * cible, QGraphicsItem *parent):QGraphicsItem(parent),taille(taille),Vitesse(Vitesse),degat(degat),type(type),couleur(couleur),son(son),source(source),destination(cible)
{
    //INTEPOLATION DU PREMIER DEGRE DU DEPLACEMENT DE LA CIBLE

    qreal x =source->pos().x()+17;
    qreal y = source->pos().y()+17;
    this->setPos(0,0);
    this->setPos(x,y);
    qreal xE=cible->pos().x()+cible->boundingRect().width()/2+taille/2;
    qreal yE=cible->pos().y()+cible->boundingRect().height()/2+taille/2;
    qreal vE =cible->getVitesse();
    qreal distance = sqrt((x-xE)*(x-xE)+(y-yE)*(y-yE));
    qreal temps = distance/Vitesse;
    qreal xPrevision = xE + 1.2*cible->xVelocity()*temps;
    qreal yPrevision = yE + 1.2*cible->yVelocity()*temps;
    qreal distancePrevision = sqrt((x-xPrevision)*(x-xPrevision)+(y-yPrevision)*(y-yPrevision));
    dx = (x-xPrevision)/distancePrevision;
    dy = (y-yPrevision)/distancePrevision;
    setZValue(3000);
    degat=source->getFrappe();
    son->setLoops(1);
    son->play();
}

void Projectile::advance(int phase)
{
    if (phase==0)
    {
        qreal x = this->pos().x();
        qreal y = this->pos().y();
        if((x>=560)||(x<=0)||(y>=560)||(y<=0))
        {
            delete this;
        }
    }
    else
    {
        moveBy(-dx*Vitesse*(35.0/50),-dy*Vitesse*(35.0/50));
    }

}

Projectile::~Projectile()
{
    if(!son->isFinished())
    {
        son->stop();
    }
    dynamic_cast<myScene *>(this->scene())->removeProjectile(this);

}

void Projectile::paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    painter->setPen(QPen(Qt::NoPen));
    painter->setBrush(couleur);
    painter->drawEllipse(0, 0, taille, taille);
}

QRectF Projectile::boundingRect() const
{
    return QRectF(0,0, taille, taille);
}

QPainterPath Projectile::shape() const
 {
     QPainterPath path;
     path.addEllipse(0, 0, taille, taille);
     return path;
 }

int Projectile::getType() const
{
    return this->type;
}

float Projectile::getDegat() const
{
    return this->degat;
}

void Projectile::detruire()
{
    if(destination->getDep()==1)
    {
        Petanque* petanque = dynamic_cast<Petanque *>(source);
        if(petanque)
        {
             dynamic_cast<myScene*>(this->scene())->zoneDegat(this->pos().x(),this->pos().y(),1.0,petanque->getDegatZone());
        }

    }
    Paintball * paintball;
    if(paintball=dynamic_cast<Paintball*>(source))
    {
        destination->ralentir();
    }
    delete this;
}

Defense * Projectile::getSource() const
{
    return this->source;
}
