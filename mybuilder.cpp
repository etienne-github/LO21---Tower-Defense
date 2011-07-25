#include "mybuilder.h"
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include "pistolet_eau.h"
#include "paintball.h"
#include "petanque.h"
#include "lance_pierre.h"
#include "musicien.h"
#include "math.h"
#include <QBrush>
#include <QPen>
#include "myscene.h"
#include "myview.h"
#include <iostream>
#include "myComputer.h"
#include "mainwindow.h"
#include "mydockwidget.h"
#include "mypushbutton.h"
#include <QTimer>
#include "defense.h"

extern QString * sourcePath;

myBuilder::myBuilder(myComputer* comp,myScene* scene,myView * view,QObject *parent) :
    QObject(parent), activated(-1), comp(comp), scene(scene), view(view),currentItem(NULL)
{
    QString * path = new QString(*sourcePath); //INITIALISATION DES SONS
    build = new QSound(*path+"build.mp3");
    wrong = new QSound(*path+"wrong.mp3");

    //CONNECTION AVEC LA VIEW  POUR RECEVOIR LES INFOS DU CURSEUR
    connect(view,SIGNAL(mouseOnScene()),this,SLOT(createCursor()));
    connect(view,SIGNAL(mouseOutScene()),this,SLOT(destroyCursor()));
    connect(view,SIGNAL(mouseDoubleClick()),this,SLOT(disableCuror()));
    connect(this,SIGNAL(switchMouseMoving()),view,SLOT(switchMouseMoving()));
    connect(view,SIGNAL(mouseMoving(float,float)),this,SLOT(updateCursor(float,float)));
    connect(view,SIGNAL(mouseClick(float,float)),this,SLOT(createDefense(float,float)));

    //CONNECTION AVEC LE DOCK POUR RECEVOIR L'ETAT DES BOUTONS
    connect(dynamic_cast<MainWindow *>(this->parent())->getDock()->getNewEau(),SIGNAL(myClicked(int)),this,SLOT(updateActivated(int)));
    connect(dynamic_cast<MainWindow *>(this->parent())->getDock()->getNewPaintball(),SIGNAL(myClicked(int)),this,SLOT(updateActivated(int)));
    connect(dynamic_cast<MainWindow *>(this->parent())->getDock()->getNewMusicien(),SIGNAL(myClicked(int)),this,SLOT(updateActivated(int)));
    connect(dynamic_cast<MainWindow *>(this->parent())->getDock()->getNewPetanque(),SIGNAL(myClicked(int)),this,SLOT(updateActivated(int)));
    connect(dynamic_cast<MainWindow *>(this->parent())->getDock()->getNewLance_pierre(),SIGNAL(myClicked(int)),this,SLOT(updateActivated(int)));

    //MATERIALISATION DE LA PORTEE DE LA TOUR 'CURSEUR' + CARRE ROUGE OU VERT SUIVANT CONTRUCTIILITE
    testSquare = new QGraphicsRectItem(0,0,35,35,NULL,NULL);
    portee = new QGraphicsEllipseItem(0,0,60,60);
    portee->setPen(QPen(Qt::white));
    testSquare->setOpacity(0.5);
    testSquare->setPen(QPen(Qt::NoPen));


}

void myBuilder::createCursor() //SI LE CURSEUR ENTRE SUR SCENE
{
    emit switchMouseMoving(); //ON DEMANDE LE TRACKING

    switch(activated) //EN FONCTION DU BOUTON ACTIF, ON FABRIQUE L'OBJET QU VA SERVIR DE CURSEUR
    {
        case 0: //FABRIQUER PISTOLET_A_EAU;
            currentItem = new Pistolet_eau( dynamic_cast<myScene *>(scene)->getSonPistolet_eau(),false,NULL);
            break;
        case 1: //FABRIQUE MUSICIEN;
            currentItem = new Musicien(dynamic_cast<myScene *>(scene)->getSonMusicien(),false,NULL);
            break;

        case 2: //FABRIQUE PETANQUE;
            currentItem = new Petanque(dynamic_cast<myScene *>(scene)->getSonPetanque(),false,NULL);
            break;

        case 3: //FABRIQUE PAINTBALL;
            //cerr<<"nouveau carré créé en ("<<round(comp->getMouseX()/35)<<";"<<round(comp->getMouseY()/35)<<")"<<endl;
            currentItem = new Paintball(dynamic_cast<myScene *>(scene)->getSonPaintball(),false,NULL);
            break;
        case 4: //FABRIQUE LANCE-PIERRE;
            currentItem = new Lance_pierre(dynamic_cast<myScene *>(scene)->getSonLance_pierre(),false,NULL);
            break;

        default :
        currentItem = NULL;
        break;
    }
    if(currentItem)
    {
    scene->addItem(testSquare); //ON DESSINE LE CARRE DE CONSTRUCTIBILITE
    scene->addItem(portee); //ON MATERIALISE LA PORTEE
    portee->setRect(0,0,dynamic_cast<Defense*>(currentItem)->getPortee()*2*35,dynamic_cast<Defense*>(currentItem)->getPortee()*2*35);
    scene->addItem(currentItem);

    }
}

void myBuilder::disableCuror() // AURAIT SERVI SI QMouseRightClickEvent existait...
{
    if(currentItem)
    {
        scene->removeItem(testSquare);
        scene->removeItem(portee);
        scene->removeItem(currentItem);
    }
}

void myBuilder::destroyCursor() //SI LE CURSEUR SORT DE LA SCENE
{
    if(currentItem)
    {
    scene->removeItem(testSquare); //ON SUPPRIME LE CURSEUR, LE TEST DE CONSTRUCTIBILITE ET LA MATERIALISATIOB DE LA PORTEE
    scene->removeItem(portee);
    scene->removeItem(currentItem);
    }
    emit switchMouseMoving();
}

void myBuilder::updateCursor(float x, float y) //SI LE CURSEUR BOUGE SUR LA SCENE
{
    if(currentItem)
    {
        //ON l'AIMENTE SUR LA GRILLE
    int tempX=(int)round((x-17)/35);
    int tempY=(int)round((y-17)/35);
     //ET ON FAIT SUIVRE LE CURSEUR, LE TEST DE CONSTRUCTIBILITE ET LA MATERIALISATIOB DE LA PORTEE
    portee->setPos(17+tempX*35-(dynamic_cast<Defense*>(currentItem)->getPortee())*35,17+tempY*35-(dynamic_cast<Defense*>(currentItem)->getPortee())*35);
   testSquare->setPos(tempX*35,tempY*35);
   currentItem->setPos(tempX*35,tempY*35);
   if (comp->isConstructible(tempY,tempX))
   {
       testSquare->setBrush(Qt::green); //VERT SI CONSTRUCTIBLE

   }
   else
   {
       testSquare->setBrush(Qt::red); //ROUGE SINON

   }

    }
}

void myBuilder::updateActivated(int i) //MET A JOUR l'ETAT DU BOUTON ACTIVE
{
    activated=i;
}


void myBuilder::createDefense(float x,float y) //SI ON CLIQUE ON CREE UNE TOUR
{
    int tempX=(int)round((x-17)/35); //SUR UNE CASE
    int tempY=(int)round((y-17)/35);

    Musicien * musicien;

    if(!currentItem) //EVITE BUG
    {
        return;
    }
    else if (comp->isConstructible(tempY,tempX)) //SI CONSTRUCTIBLE
    {

        if (comp->getCredit()>=dynamic_cast<Defense *>(currentItem)->getPrixBase())
        {
            switch(activated)
            {
                case 0: //FABRIQUE PISTOLET_A_EAU;
                    newItem = new Pistolet_eau(dynamic_cast<myScene *>(scene)->getSonPistolet_eau(),true,NULL);
                    break;

                case 1: //FABRIQUE MUSICIEN;
                    newItem = new Musicien(dynamic_cast<myScene *>(scene)->getSonMusicien(),true,NULL);
                    break;
                case 2: //FABRIQUE PETANQUE;
                    newItem = new Petanque(dynamic_cast<myScene *>(scene)->getSonPetanque(),true,NULL);
                    break;

                case 3: //FABRIQUE PAINTBALL;
                    newItem = new Paintball(dynamic_cast<myScene *>(scene)->getSonPaintball(),true,NULL);
                    break;
                case 4: //FABRIQUE LANCE-PIERRE;
                    newItem = new Lance_pierre(dynamic_cast<myScene *>(scene)->getSonLance_pierre(),true,NULL);
                    break;
                default :
                    break;


            }
            comp->setName(x,y,dynamic_cast<Defense*>(newItem)->getDesc());
            scene->addItem(newItem);
            newItem->setPos(tempX*35,tempY*35);
            comp->setConstructible(tempY,tempX,false); //DIT QUE L'EMPLACEMENT N'EST DESORMAIS PLUS CONSTUCTIBLE
            comp->setObjectMap(x,y,newItem);
            comp->setCredit(comp->getCredit()-dynamic_cast<Defense *>(currentItem)->getPrixBase()); //ON PAYE
            musicien=dynamic_cast<Musicien *>(newItem);
            if(musicien)//SI C'EST UN MUSICIEN
            {
                dynamic_cast<myScene *>(scene)->pushMusicien(dynamic_cast<Musicien*>(newItem));//ON MET A JOUR LA LISTE DE REFERETIATION DES MUSICIENS
            }
            else //SINON
            {
                dynamic_cast<myScene *>(scene)->pushDefense(dynamic_cast<Defense*>(newItem));//ON MET A JOUR LA LISTE DE REFERETIATION DES DEFENSE
            }
            dynamic_cast<myScene *>(scene)->updateMusicien(); //ON MET A JOUR LA DISTRIBUTION DE BONUS DES MUSICIENS
            build->setLoops(1);//ON JOUE LE SON DE LA CONSTRUCTION
            build->play();

        }
        else //SI PAS D'ARGENT
        {
            wrong->setLoops(1); //JOUE LE SON WRONG
            wrong->play();
        }
    }
    else //SI PAS COMSTRUTIBLE JOUE LE SON WRONG
    {
        dynamic_cast<MainWindow *>(this->parent())->getDock()->getInfoDefense()->setText(*(comp->getName(tempY,tempX)));
        wrong->setLoops(1);
        wrong->play();
    }
}

int  myBuilder::getActivated() const
{
    return this->activated;
}
