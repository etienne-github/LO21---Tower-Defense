#include "mycomputer.h"
#include<QGraphicsItem>
#include <iostream>
#include <QString>
#include <QTimer>
#include "mainwindow.h"
#include "myscene.h"



using namespace std;
myComputer::myComputer(int pVie,int pCredit,QObject *parent) :
    QObject(parent)
{

    //Initialisation des grilles matricielles objectMap et constructible
    for(int i=0;i<16;i++)
    {
        for(int j=0;j<16;++j)
        {
            this->objectMap[i][j]=0; //aucun objet
            this->chemin[i][j]=0; //aucun objet
            this->constructible[i][j]=true; //constructible partout
            this->objectNameMap[i][j]=new QString(tr(""));

        }
    }
            cerr<<"vie: "<<pVie<<" | credit: "<<pCredit<<endl;
            vie=pVie;
            credit=pCredit;
            emit vieChanged(); // mise à jour du LCDNumber vie du dock
            emit creditChanged();// mise à jour du LCDNumber credit du dock

}

//GETTERS
float myComputer::getMouseX() const
{
    return this->mouseX;
}
float myComputer::getMouseY() const
{
    return this->mouseY;
}
int myComputer::getX_deb() const
{
    return this->x_deb;
}
int myComputer::getY_deb() const
{
    return this->y_deb;
}
int myComputer::getX_fin() const
{
    return this->x_fin;
}
int myComputer::getY_fin() const
{
    return this->y_fin;
}
QGraphicsItem* myComputer::getObjectMap(int i,int j) const
{
    return this->objectMap[i][j];
}
bool myComputer::isConstructible(int i,int j) const
{
    return this->constructible[i][j];
}

int myComputer::getChemin(int i, int j) const
{
    return this->chemin[i][j];
}
int myComputer::getVie() const
{
    return this->vie;
}
int myComputer::getCredit() const
{
    return this->credit;
}

QString * myComputer::getName(int i,int j) const
{
    return this->objectNameMap[i][j];
}
//SETTERS
void myComputer::setMouseX(float x)
{
    this->mouseX=x;
}

void myComputer::setMouseY(float y)
{
    this->mouseY=y;
}

void myComputer::setX_deb(int x)
{
    this->x_deb=x;
}

void myComputer::setY_deb(int y)
{
    this->y_deb=y;
}

void myComputer::setX_fin(int x)
{
    this->x_fin=x;
}

void myComputer::setY_fin(int y)
{
    this->y_fin=y;
}

void myComputer::setObjectMap(int i, int j,QGraphicsItem* object)
{
    this->objectMap[i][j]=object;
}

void myComputer::setConstructible(int i, int j, bool enable)
{
    this->constructible[i][j]=enable;
}
void myComputer::setChemin(int i, int j, int elem)
{
    this->chemin[i][j]=elem;
}

void myComputer::setVie(int vie)
{
    this->vie=vie;
    emit vieChanged();
    if(vie<=0)
    {
        dynamic_cast<MainWindow*>(this->parent())->getScene()->freeze();
        dynamic_cast<MainWindow*>(this->parent())->popGameOver();
    }
}

void myComputer::setCredit(int credit)
{
    this->credit=credit;
    emit creditChanged();
}
void myComputer::setName(int i, int j, QString* name)
{
    this->objectNameMap[i][j]=name;
}
