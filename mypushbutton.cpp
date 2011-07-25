#include "mypushbutton.h"
#include <iostream>
#include <QWidget>
#include<QPushButton>
#include<QPalette>
#include<QtGui/QtGui>
#include<QColor>
#include"mydockwidget.h"
#include"mypushbutton.h"
using namespace std;

myPushButton::myPushButton(int i, QColor c,QString s, myDockWidget *parent) :
    /*QObject(parent),*/ QPushButton(s,parent),i(i),enable(false)
{
    this->dock=parent;
    this->setStyle(new QPlastiqueStyle);
    basicPalette = new QPalette(this->palette());
    pressedPalette = new QPalette(c);
    connect(dynamic_cast<myDockWidget*>(this->parent()),SIGNAL(finished()),this,SLOT(myLink()));

}

void myPushButton::mousePressEvent(QMouseEvent * e)
{
    this->setStyle(new QPlastiqueStyle);
    if(!enable) //SI PAS CLIQUER DISPO
    {
        this->setPalette(*pressedPalette);  //METTRE LA PALETTE DE COULEUR BOUTON ENFONCE
        this->enable =true;
        emit myClicked(this->i); //ENVOIE : JE SUIS i ET JE SUIS CLIQUE
    }
    else //SI DISPO
    {
        this->setPalette(*basicPalette); //METTRE LA COULEUR BASIQUE DU BOUTON CLIQUABLE
        this->enable=false;
        emit myClicked(-1); //ENVOIE AUCUN BOUTON CLIQUE
    }



}

void myPushButton::myUnable()
{
    this->setPalette(*basicPalette);
    this->enable=false;
}

void myPushButton::myLink() //MET A JOUR LE TABLEAU DES BOUTONS
{

    for (int j=0;j<5;j++)
    {
         if(j!=this->i)
         {
             connect(this->dock->buttonTab[j],SIGNAL(myClicked(int)),this,SLOT(myUnable()));
         }
    }
}

int myPushButton::getI() const
{
    return i;
}

void myPushButton::enterEvent(QEvent *) //A L'ENTREE DU SURVOL
{
    if(!this->enable) //SI PAS PRECEDEMENT DISP
    {
    this->sauvegarde= QString(this->dock->getInfoDefense()->text()); //SAUVEGARDER L'ETAT DES LA DESCRIPTION ACTUELLE ET DES BOUTONS
    this->sauvegarde_sell = this->dock->getSellDefense()->isVisible();
    this->sauvegarde_update =  this->dock->getUpdateDefense()->isVisible();


    //CACHER VENDRE/AMELIORER
    this->dock->hideSellDefense();
    this->dock->hideUpdateDefense();
    this->dock->setInfoDefense(this->dock->getButtonDesc(this->i)); //ET METTRE LA NOUVELLES DESC
    }

}

void myPushButton::leaveEvent(QEvent *) // EN SORTIE
{
    if(!this->enable) //SI ON SORT DU SURVOL SANS AVOIR CLIQUE
    {
        this->dock->setInfoDefense(&sauvegarde); // ON REMETER LES INFO DANS L'ETAT SAUVEGARDE

        if(sauvegarde_sell)
        {

            this->dock->showSellDefense();
        }

        if(sauvegarde_update)
        {

           this->dock->showUpdateDefense();
        }
    }

}
