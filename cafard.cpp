#include "cafard.h"
#include "myScene.h"
#include <QList>
#include <QGraphicsItem>
#include <QObject>
#include "mycomputer.h"
#include <iostream>

using namespace std;

Cafard::Cafard(int x, int y,float taille,QGraphicsScene *scene): Insecte(dynamic_cast<myScene*>(scene)->animationCafard,dynamic_cast<myScene*>(scene)->sonCafard,taille,1,2,5,10,scene)
{
    hp=10*pow(taille,2);
    resistance=5*pow(taille,2);
    vitesse=2;
    this->setPos(x*35,y*35);
    connect(&(this->tFils2),SIGNAL(timeout()),this,SLOT(slotFils2()));
}


void Cafard::dupliquer()
{
        //Méthode créant de cafard d'une taille de la moitié du cafard père si celui-ci ça une taille supérieur à deux
        Cafard* fils1;
        fils1=new Cafard(round(this->pos().x()/35),round(this->pos().y()/35),taille/2,this->scene()); //on creer le fils 1
        dynamic_cast<myScene*>(scene())->addItem(fils1);
        if(!tFils2.isActive()) //on lance la tempo avant la création du fils 2
        {
        tFils2.setSingleShot(true);
        tFils2.setInterval(20*15);
        tFils2.start();
        }
}

void Cafard::fils2() //appelé après la tempo
{
    Cafard * fils2 = new Cafard(round(this->pos().x()/35),round(this->pos().y()/35),taille/2,this->scene());
    dynamic_cast<myScene*>(scene())->addItem(fils2); //on cree le fils deux
    dynamic_cast<myScene*>(this->scene())->removeInsect(this);
    delete this; //et on supprime le cafard

}


void Cafard::mourir()
{
    dynamic_cast<myScene*>(this->scene())->getComputer()->setCredit((dynamic_cast<myScene*>(this->scene())->getComputer()->getCredit())+1); //on récompense le joueur
    if (!son->isFinished())
    {
       son->stop();
    }
    if(taille>=2) //si la taille superieur à deux on retire de la referentiation et on dupplique
    {
        dynamic_cast<myScene*>(this->scene())->removeInsect(this);
        this->dupliquer();
    }
    else
    {
        dynamic_cast<myScene*>(this->scene())->removeInsect(this); //sinon on retire de la referentiation et on supprime directement
        delete this;
    }
}
