#include "mydockwidget.h"
#include <iostream>
#include "mycomputer.h"
#include <QLCDNumber>
#include <QtGui/QtGui>
#include "mypushbutton.h"
#include<QPushButton>
#include "mainwindow.h"
#include "myscene.h"
#include "myView.h"

using namespace std;
myDockWidget::myDockWidget(myComputer *comp, QWidget *parent) :
    QDockWidget(parent),comp(comp)
{


    //Definition d'un contenu pour le Dock
    QWidget *contenuDock = new QWidget;
    this->setWidget(contenuDock);
    //verticalGroupBox = new QGroupBox(tr(""));

    this->setFixedSize(350,560);//Dimensionnement du Dock
    QGroupBox* infoGroupBox = new QGroupBox(tr("Informations")); //Initialisation du texte
    QGroupBox* defenseGroupBox = new QGroupBox(tr("Creer une Defense")); //Initialisation du texte
    QGroupBox* IndicateurGroupBox = new QGroupBox(tr(""));
    infoGroupBox->setFixedHeight(225);
    //QGroupeBox* sellUpdateGroupBox = newQGroupe

    //INITIALISATION DES LAYOUT ASSOCIE
    QVBoxLayout *Vlayout = new QVBoxLayout; //Mise en page verticale pour le dock
    QVBoxLayout *Infolayout = new QVBoxLayout; //Mise en page verticale pour le text d'info

    //QGridLayout *mainlayout = new QGridLayout();
    QGridLayout* gridIndicateur = new QGridLayout; //creation d'une grille pour les afficheur 7 segments
    QGridLayout* gridDefense = new QGridLayout; // creation d'un grilles pour les boutons nouvelle défense
    QGridLayout * gridSellUpdate = new QGridLayout;

    newWave = new QPushButton("Nouvelle vague !",this);
    newEau = new myPushButton(0,Qt::blue,"Eau",this);
    newMusicien = new myPushButton(1,Qt::green,"Musicien",this);
    newPetanque = new myPushButton(2,Qt::cyan,"Petanque",this);
    newPaintball = new myPushButton(3,Qt::yellow,"Painball",this);
    newLance_pierre = new myPushButton(4,Qt::magenta,"Lance-Pierre",this);
    sellDefense = new QPushButton("Vendre",this);
    sellDefense->hide();
    sellDefense->setEnabled(false);
    updateDefense = new QPushButton("Ameliorer",this);
    updateDefense->hide();
    updateDefense->setEnabled(false);
    buttonTab[0]=newEau;
    buttonTab[1]=newMusicien;
    buttonTab[2]=newPetanque;
    buttonTab[3]=newPaintball;
    buttonTab[4]=newLance_pierre;

    buttonDesc[0]=new QString("Ajouter Tireur au pistolet a eau:\n\nCible: Volants et Rampants\nPortee: 2\nCadence: 4\nFrappe: 5\nPrix: 8 credits");
    buttonDesc[1]=new QString("Ajouter Musicien:\n\nPortee: 1,5\nEffet: Bonifie de 20% les defenses a portee\nPrix: 15 credits");
    buttonDesc[2]=new QString("Ajouter Joueur de petanque:\n\nCible: Rampants\nPortee: 3\nCadence: 0,5\nFrappe: 15\nPrix: 15 credits");
    buttonDesc[3]=new QString("Ajouter Tireur au fusil paintball:\n\nCible: Volants et Rampants\nPortee: 4\nCadence: 2\nFrappe: 4\nPrix: 12 credits");
    buttonDesc[4]=new QString("Ajouter Tireur au lance-pierre:\n\nCible: Volants\nPortee: 3\nCadence: 1\nFrappe: 10\nPrix: 12 credits");


    //INITIALISATION DES AFFICHEURS 7 SEG
    LCDcredit = new QLCDNumber(this);
    LCDvie = new QLCDNumber(this);
    LCDcredit->setSegmentStyle(QLCDNumber::Filled);
    LCDvie->setSegmentStyle(QLCDNumber::Filled);

    //Connection des bouton avec les signaux envoyé par le comp, pour les mettre à jour
    connect(comp, SIGNAL(creditChanged()), this, SLOT(updateCredit()));
    connect(comp, SIGNAL(vieChanged()), this, SLOT(updateVie()));
    connect(this->newWave,SIGNAL(clicked()),dynamic_cast<MainWindow *>(this->parent())->getScene(),SLOT(newWave()));
    connect(this->updateDefense,SIGNAL(clicked()),dynamic_cast<MainWindow *>(this->parent())->getView(),SLOT(ameliorerItem()));
    connect(this->sellDefense,SIGNAL(clicked()),dynamic_cast<MainWindow *>(this->parent())->getView(),SLOT(vendreItem()));
 //connect(dynamic_cast<MainWindow *>(this->getComputer()->parent())->getDock()->getUpdateDefense(),SIGNAL(clicked()),this,SLOT(ameliorerItem()));
    //INITIALISATION DES ETIQUETTES
    infoVague = new QLabel(this);
    infoDefense = new QLabel(this);
    QLabel *txtVie = new QLabel;
    QLabel *txtCredit = new QLabel;
    txtVie->setText("Vies :");
    txtCredit->setText("Credits :");
    infoVague->setText("Cliquez sur \"Nouvelle vague !\" pour commencer !");
    infoDefense->setText("Cliquez sur un objet pour \nen obtenir des informations.");



    //Ajout des widget dans les mises en page

    //indicateur vie et credit
    gridIndicateur->addWidget(txtVie,0,0);
    gridIndicateur->addWidget(LCDvie,0,1);
    gridIndicateur->addWidget(txtCredit,1,0);
    gridIndicateur->addWidget(LCDcredit,1,1);

    //bouton défense
    gridDefense->addWidget(newEau,0,0);
    gridDefense->addWidget(newPetanque,0,2);
    gridDefense->addWidget(newMusicien,1,1);
    gridDefense->addWidget(newPaintball,2,0);
    gridDefense->addWidget(newLance_pierre,2,2);

    gridSellUpdate->addWidget(sellDefense,0,0);
    gridSellUpdate->addWidget(updateDefense,0,0);
    //information sur les défense
    Infolayout->addWidget(infoDefense);
    Infolayout->addWidget(updateDefense);
    Infolayout->addWidget(sellDefense);

    //mise en page principale
    Vlayout->addWidget(infoVague);
    Vlayout->addWidget(newWave);
    Vlayout->addWidget(IndicateurGroupBox);
    Vlayout->addWidget(defenseGroupBox);
    Vlayout->addWidget(infoGroupBox);

    //GRID INDICATION VIE ET CREDIT


    //Affectation des mises en pages
    infoGroupBox->setLayout(Infolayout);
    IndicateurGroupBox->setLayout(gridIndicateur);
    defenseGroupBox->setLayout(gridDefense);

    contenuDock->setLayout(Vlayout);

    this->setFeatures(QDockWidget::NoDockWidgetFeatures|QDockWidget::DockWidgetVerticalTitleBar);//Bare de titre verticale
    this->setWindowTitle (tr("Commandes"));


    //INITIALISATION DU DOCK
    updateVie();
    updateCredit();
    emit finished();


}


//Met à jour l'affichage du crédit avec le credit dans le comp
void myDockWidget::updateCredit()
{
    //cerr<<"Signal de changer le crédit reçu";
    this->LCDcredit->display(comp->getCredit());
    return;
}

//Met à jour l'affichage de la vie avec la vie dans le comp
void myDockWidget::updateVie()
{
    //cerr<<"Signal de changer la vie reçu";
    this->LCDvie->display(comp->getVie());
    return;
}



QPushButton * myDockWidget::getNewWave() const
{
    return this->newWave;
}

myPushButton * myDockWidget::getNewEau() const
{
    return this->newEau;
}
myPushButton * myDockWidget::getNewPetanque() const
{
    return this->newPetanque;
}
myPushButton * myDockWidget::getNewMusicien() const
{
    return this->newMusicien;
}
myPushButton * myDockWidget::getNewPaintball() const
{
    return this->newPaintball;
}

myPushButton * myDockWidget::getNewLance_pierre() const
{
    return this->newLance_pierre;
}

QLCDNumber* myDockWidget::getLCDcredit() const
{
    return this->LCDcredit;
}
QLCDNumber* myDockWidget::getLCDvie() const
{
    return this->LCDvie;
}
QLabel * myDockWidget::getInfoVague() const
{
    return this->infoVague;
}
QLabel * myDockWidget::getInfoDefense() const
{
    return this->infoDefense;
}
myComputer * myDockWidget::getComputer() const
{
    return this->comp;
}

myPushButton* myDockWidget::getButton(int i) const
{
    return this->buttonTab[i];
}

QString* myDockWidget::getButtonDesc(int i) const
{
    return this->buttonDesc[i];
}

QPushButton * myDockWidget::getUpdateDefense() const
{
    return this->updateDefense;
}

void myDockWidget::showUpdateDefense()
{
    return this->updateDefense->show();
}

void myDockWidget::showSellDefense()
{
    this->sellDefense->show();
}

void myDockWidget::hideUpdateDefense()
{
    this->updateDefense->hide();
}

void myDockWidget::hideSellDefense()
{
    this->sellDefense->hide();
}

QPushButton * myDockWidget::getSellDefense() const
{
    return this->sellDefense;
}


//SETTERS
void myDockWidget::setInfoVague(QString * s)
{
    this->infoVague->setText(*s);
}

void myDockWidget::setInfoDefense(QString * s)
{
    this->infoDefense->setText(*s);
}
void myDockWidget::setComputer(myComputer * comp)
{
    this->comp=comp;
}

