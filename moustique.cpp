#include "moustique.h"
#include "myScene.h"
#include <QList>
#include <QGraphicsItem>
#include <QObject>
#include <QTimer>
#include <iostream>

using namespace std;

Moustique::Moustique(int x, int y,float taille,QGraphicsScene *scene): Insecte(dynamic_cast<myScene*>(scene)->animationMoustique,dynamic_cast<myScene*>(scene)->sonMoustique,taille,2,2,1,6,scene)
{
    hp=6*pow(taille,2);
    resistance=1*pow(taille,2);
    vitesse=2+taille/2;
    this->setPos(x*35,y*35);
    connect(&(this->tPoser),SIGNAL(timeout()),this,SLOT(slotEnvoler()));
    connect(&(this->tEnvoler),SIGNAL(timeout()),this,SLOT(slotPoser()));
    tEnvoler.setSingleShot(true);
    tEnvoler.setInterval(20*50*7);
    tEnvoler.start();
}

/*
//EN VOL
resistance=1*pow(taille,2);
vitesse=2+taille/2;

//AU SOL
resistance=15*taille;
vitesse=1+taille/2;
*/

void Moustique::recevoirDegat(float degat)
{
    float deg = (degat-resistance);
    if (deg<0)
    {
        deg=1;
    }
    hp-=deg;
    if(dep=2) //si pas déjà en marche, se poser
    {
        tEnvoler.stop();
        tPoser.setSingleShot(true);
        tPoser.setInterval(20*50*3);
        tPoser.start();
        this->poser();
    }

}

void Moustique::poser()
{
    resistance=15*taille; //mise a jour des caracteristiques
    vitesse=1+taille/2;
    dep=1;
    this->setScale(0.8); //retressissement pour simuler la pose au sol
    tPoser.setSingleShot(true); // declenchement de la tempo avant renvol
    tPoser.setInterval(20*50*3);
    tPoser.start(); //a la fin de poser, envoler
}

void Moustique::envoler()
{
    resistance=1*pow(taille,2); //mise à jour des caracteristiques
    vitesse=2+taille/2;
    this->setScale(1); // regrossissement pour simuler le vol
    dep=2;
    tEnvoler.setSingleShot(true); //tempo avant pose
    tEnvoler.setInterval(20*50*7);
    tEnvoler.start(); //a la fin de envoler.poser
}
