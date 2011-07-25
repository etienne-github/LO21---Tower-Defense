#include "newpartie.h"
#include "mainwindow.h"

extern MainWindow * w;

//FENETRE DE SELECTION DE LA CARTE, LA DIFFICULTE ET LES VAGUES

Newpartie::Newpartie(QWidget *parent) :
    QWidget(parent)
{
    ok = new QPushButton(tr("Commencer !"));
    maps = new QComboBox(this);
    vagues = new QComboBox(this);
    difficultes = new QComboBox(this);
    maps->addItem("Carte 1");
    maps->addItem("Carte 2");
    maps->addItem("Carte 3");
    vagues->addItem("Motif 1");
    vagues->addItem("Motif 2");
    vagues->addItem("Motif 3");
    difficultes->addItem("Facile");
    difficultes->addItem("Moyen");
    difficultes->addItem("Difficile");
    QFormLayout *mainlayout = new QFormLayout;
    mainlayout->addRow("Choisissez votre carte:", maps);
    mainlayout->addRow("Choissisez vos vagues d'insectes: ", vagues);
    mainlayout->addRow("Choissisez votre difficulte: ", difficultes);
    mainlayout->addRow("", ok);
    setWindowTitle(tr("Nouvelle Partie"));
    this->setLayout(mainlayout);
    connect(this->ok,SIGNAL(clicked()),this,SLOT(load()));

}

void Newpartie::load()
{
    QString carte;
    QString vague;
    QString difficulte;
    int vie;
    int credit;
    switch(this->vagues->currentIndex())
    {
    case 0:
        vague="waves.txt";
        break;
    case 1:
        vague="waves2.txt";
        break;
    case 2:
        vague="waves3.txt";
        break;

    default:
        vague="waves.txt";
        break;

    }
    switch(this->maps->currentIndex())
    {
    case 0:
        carte="map.txt";
        break;
    case 1:
        carte="map2.txt";
        break;

    case 2:
        carte="map3.txt";
        break;

    default:
        carte="map.txt";
        break;
    }
    switch(this->difficultes->currentIndex())
    {
    case 0:
        vie=20;
        credit=60;
        break;
    case 1:
        vie=15;
        credit=40;
        break;
    case 2:
        vie=10;
        credit=25;
        break;

    default:
        vie=20;
        credit=60;
        break;
    }
    w = new MainWindow(carte,vague,vie,credit,0);
    w->show();
    this->close();
}
