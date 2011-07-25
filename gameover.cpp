#include "gameover.h"
#include "mainwindow.h"
#include "newpartie.h"

extern MainWindow * w;
extern Newpartie * np;


//FENETRE DE GAME OVER -> REJOUER OU QUITTER ?

Gameover::Gameover(QWidget *parent) :
    QWidget(parent)
{
    texte = new QLabel("Vous avez perdu !!\nLes insectes ont eu raison de votre pic-nic...");
    quitter = new QPushButton("Quitter",this);
    newPartie = new QPushButton("Nouvelle Partie",this);
    QGroupBox* buttonGroupBox = new QGroupBox(tr(""));
    QHBoxLayout *buttonLayout = new QHBoxLayout; //Mise en page verticale pour le dock
    QVBoxLayout *mainLayout = new QVBoxLayout; //Mise en page verticale pour le dock
    buttonLayout->addWidget(newPartie);
    buttonLayout->addWidget(quitter);
    buttonGroupBox->setLayout(buttonLayout);
    mainLayout->addWidget(texte);
    mainLayout->addWidget(buttonGroupBox);
    this->setLayout(mainLayout);
    setWindowTitle(tr("Game Over..."));
    connect(this->newPartie,SIGNAL(clicked()),this,SLOT(reload()));
    connect(this->quitter,SIGNAL(clicked()),qApp,SLOT(closeAllWindows()));
}

void Gameover::reload()
{
    w->close();
    np = new Newpartie;
    np->show();
    this->close();
}

void Gameover::leaveGame()
{

}
