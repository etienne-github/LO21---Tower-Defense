#include "mainwindow.h"
#include <iostream>
#include "ui_mainwindow.h"
#include <QtGui/QtGui>
#include "math.h"
#include "myscene.h"
#include "myview.h"
#include "mycomputer.h"
#include "mydockwidget.h"
#include "mybuilder.h"
#include <QList>
#include "gameover.h"
#include "newpartie.h"

extern Gameover * go;
extern Newpartie * np;

using namespace std;

MainWindow::MainWindow(QString carte, QString vague, int vie, int credit,QWidget *parent) :QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    cerr<<"vie: "<<vie<<" | credit: "<<credit<<endl;

    //INITIALISATION DES DIFFERENTS MODULE DE LA FENETRE PRINCIPALE
    this->setFixedSize(910,560); //Dimensionnement de la fenètre globale
    this->setComputer(new myComputer(vie,credit,this)); //Creation du gestionnaire principale
    this->setScene(new myScene(carte,vague,this->centralComputer,this)); //creation de la scène
    this->setView(new myView(this->centralComputer,scene)); //creation de la vue
    this->getView()->setFixedSize(560,560); //dimensionnement de la vue
    this->setDock(new myDockWidget(this->centralComputer,this)); //creation de l'IHM
    this->setBuilder(new myBuilder(this->centralComputer,scene,view,this)); //creation du gestionnaire de construction
    addDockWidget(Qt::RightDockWidgetArea, this->getDock()); //Positionnement de l'IHM à gauche
    setCentralWidget(this->getView()); //Positionnement de la scène au milieu
    createActions(); //initialisation des actions du menu
    createMenus(); //creation du menu
    setWindowTitle(tr("LO21 - Tower Defense - GIROT - DAHMANI - MAZUR")); //ajout du titre de la fenetre
    gameover = new Gameover;


}

MainWindow::~MainWindow()
{
    delete ui;
}



//GETTERS
myComputer * MainWindow::getComputer() const
{
    return this->centralComputer;
}
myScene * MainWindow::getScene() const
{
    return this->scene;
}
myView * MainWindow::getView() const
{
    return this->view;
}
myDockWidget * MainWindow::getDock() const
{
    return this->dock;
}
myBuilder * MainWindow::getBuilder() const
{
    return this->builder;
}
//SETTERS
void MainWindow::setComputer(myComputer * comp)
{
    this->centralComputer = comp;
}

void MainWindow::setScene(myScene * scene)
{
    this->scene=scene;
}
void MainWindow::setView(myView * view)
{
    this->view=view;
}

void MainWindow::setDock(myDockWidget * dock)
{
    this->dock=dock;
}

void MainWindow::setBuilder(myBuilder * builder)
{
    this->builder=builder;
}


void MainWindow::createActions()
 {

    playAct = new QAction(tr("&Reprendre"), this);
    //resetAct->setShortcuts("‚åò + r");
    playAct->setStatusTip(tr("Reprend la partie"));
    connect(playAct, SIGNAL(triggered()), this, SLOT(play()));
    playAct->setEnabled(false);

    resetAct = new QAction(tr("&Nouvelle partie"), this);
    //resetAct->setShortcuts("‚åò + r");
    resetAct->setStatusTip(tr("Charge une nouvelle partie"));
    connect(resetAct, SIGNAL(triggered()), this, SLOT(reset()));

     pauseAct = new QAction(tr("&Mettre en pause"), this);
     //pauseAct->setShortcuts("‚åò + s");
     pauseAct->setStatusTip(tr("Met le jeu en pause"));
     connect(pauseAct, SIGNAL(triggered()), this, SLOT(pause()));

     quiitAct = new QAction(tr("Sortir du jeu"), this);
     quiitAct->setStatusTip(tr("Hey"));
     connect(quiitAct, SIGNAL(triggered()), this, SLOT(leaveGame()));

     aboutAct = new QAction(tr("&Information"), this);
     //aboutAct->setShortcuts("‚åò + a");
     aboutAct->setStatusTip(tr("Affiche des informations"));
     connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));


     alignmentGroup = new QActionGroup(this);
     alignmentGroup->addAction(pauseAct);
     alignmentGroup->addAction(resetAct);
     alignmentGroup->addAction(aboutAct);
     alignmentGroup->addAction(quiitAct);
}


void MainWindow::createMenus()
 {
     animationMenu = menuBar()->addMenu(tr("&Menu"));
     animationMenu->addAction(playAct);
     animationMenu->addAction(pauseAct);
     animationMenu->addAction(resetAct);
     animationMenu->addSeparator();
     animationMenu->addAction(quiitAct);
     helpMenu = menuBar()->addMenu(tr("&Informations"));
     helpMenu->addAction(aboutAct);
 }


void MainWindow::play()
{
    this->scene->unfreeze();
    playAct->setEnabled(false);
    pauseAct->setEnabled(true);
};
void MainWindow::pause()
{
    this->scene->freeze();
    playAct->setEnabled(true);
    pauseAct->setEnabled(false);

};
void MainWindow::reset()
{
    np = new Newpartie();
    np->show();
    this->close();

};
void MainWindow::about(){};

void MainWindow::leaveGame()
{qApp->closeAllWindows();};

void MainWindow::popGameOver()
{
    cerr<<"on pop le GO"<<endl;
    go = new Gameover();
    go->show();
}
