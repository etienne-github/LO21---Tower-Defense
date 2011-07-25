#include "myscene.h"
#include "mycomputer.h"
#include "QtGui/QtGui"
#include"MainWindow.h"
#include <iostream>
#include <fstream>
#include <QPixmap>
#include <QBrush>
#include <QObject>
#include <QString>
#include "fourmi.h"
#include "guepe.h"
#include "cafard.h"
#include"moustique.h"
#include"mydockwidget.h"
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include "projectile.h"
#include <QSound>
#include "petanque.h"
#include "paintball.h"
#include "musicien.h"
extern QString * sourcePath;

using namespace std;

myScene::myScene(QString carte,QString vague,myComputer* comp,QMainWindow* parent) :
    QGraphicsScene(parent),ref(comp),stateTick(-1)
{
    this->setSceneRect(0, 0, 560, 560); //dimensionnement de la scene
    this->setItemIndexMethod(QGraphicsScene::NoIndex);
    this->charger_map(carte); //chargement des éléments graphiques depuis map.txt

    QString * path = new QString(*sourcePath);

    QPixmap fourmi1 =QPixmap(*path+"fourmi1.png")/*.scaled(35,35)*/;
    QPixmap fourmi2 =QPixmap(*path+"fourmi2.png")/*.scaled(35,35)*/;
    QPixmap fourmi3 =QPixmap(*path+"fourmi3.png")/*.scaled(35,35)*/;


    QPixmap guepe1 =QPixmap(*path+"guepe1.png")/*.scaled(35,35)*/;
    QPixmap guepe2 =QPixmap(*path+"guepe2.png")/*.scaled(35,35)*/;

    QPixmap moustique1 =QPixmap(*path+"moustique1.png")/*.scaled(35,35)*/;
    QPixmap moustique2 =QPixmap(*path+"moustique2.png")/*.scaled(35,35)*/;

    QPixmap cafard1 =QPixmap(*path+"cafard1.png")/*.scaled(35,35)*/;
    QPixmap cafard2 =QPixmap(*path+"cafard2.png")/*.scaled(35,35)*/;
    QPixmap cafard3 =QPixmap(*path+"cafard3.png")/*.scaled(35,35)*/;


    //SEQUENCES + SONS INSECTES
    animationFourmi<<fourmi1;
    animationFourmi<<fourmi1;
    animationFourmi<<fourmi2;
    animationFourmi<<fourmi2;
    animationFourmi<<fourmi3;
    animationFourmi<<fourmi3;
    sonFourmi = new QSound(*path+"fourmi.mp3");

    animationCafard<<cafard1;
    animationCafard<<cafard1;
    animationCafard<<cafard2;
    animationCafard<<cafard2;
    animationCafard<<cafard3;
    animationCafard<<cafard3;
    sonCafard= new QSound (*path+"cafard.mp3");

    animationGuepe<<guepe1;
    animationGuepe<<guepe1;
    animationGuepe<<guepe2;
    animationGuepe<<guepe2;
    sonGuepe= new QSound (*path+"guepe.mp3");

    animationMoustique<<moustique1;
    animationMoustique<<moustique1;
    animationMoustique<<moustique2;
    animationMoustique<<moustique2;
    sonMoustique= new QSound(*path+"moustique.mp3");
    sonPistolet_eau = new QSound(*path+"pistolet-eau.mp3");
    sonMusicien = new QSound(*path+"musicien.mp3");
    sonPaintball = new QSound(*path+"paintball.mp3");
    sonPetanque = new QSound(*path+"petanque.mp3");
    sonLance_pierre = new QSound(*path+"lance-pierre.mp3");

    //LANCEMENT DU TIMER PRINCIPAL
    timerId = this->startTimer(20);

    //CREATION DE L'INSECTE FACTORY
    this->vague = new InsecteFactory(vague,this,0);


    //CONNECTION AVEC LE SIGNAL D'ACTIVATION/DESACTIVATION DE L'ENVOIE DE LA POSITION DU CURSEUR
    connect(this->vague,SIGNAL(switchTick()),this,SLOT(switchTick()));

    //CONNECTION AVEC LE SLOT DE CREATION DES INSECTE DANS INSECTEFACTORY
    connect(this,SIGNAL(tick()),this->vague,SLOT(incrementTickCounter()));



}


//CHARGEMENT DE LA MAP
void myScene::charger_map(QString carte)
{
    QString * path = new QString(*sourcePath);
    path->append(carte);
    int temp;
    int prev;
    int x_deb,y_deb;
    int i = 0;
    int x = 0;
    int y = 0;
    int elem[16][16]; //tableau temporaire pour conserver la configuration de la scène


    //DEFINITION DES ENTITES PARCELLES D'HERBE, PARCELLES DE BOUE, DIFFERENTS MORCEAUX DE CHEMIN, PANIER
    QGraphicsRectItem* rect;

    //récuperation des images
    QPixmap pix_boue (":/Terrain/boue.jpg");
    QPixmap pix_herbe (":/Terrain/herbe.jpg");
    QPixmap pix_panier (":/Terrain/panier.png");
    QPixmap pix_N (":/Terrain/N.jpg");
    QPixmap pix_NE (":/Terrain/N_E.jpg");
    QPixmap pix_E (":/Terrain/N_E.jpg");
    QPixmap pix_SE (":/Terrain/S_E.jpg");
    QPixmap pix_S (":/Terrain/S.jpg");
    QPixmap pix_SO (":/Terrain/S_O.jpg");
    QPixmap pix_O (":/Terrain/O.jpg");
    QPixmap pix_NO (":/Terrain/N_O.jpg");

    //redimensionnement des images
    QPixmap pix_boue_scaled = pix_boue.scaled(35,35);
    QPixmap pix_herbe_scaled = pix_herbe.scaled(35,35);
    QPixmap pix_panier_scaled = pix_panier.scaled(35,35);
    QPixmap pix_N_scaled = pix_N.scaled(35,35);
    QPixmap pix_NE_scaled = pix_NE.scaled(35,35);
    QPixmap pix_E_scaled = pix_E.scaled(35,35);
    QPixmap pix_SE_scaled = pix_SE.scaled(35,35);
    QPixmap pix_S_scaled = pix_S.scaled(35,35);
    QPixmap pix_SO_scaled = pix_SO.scaled(35,35);
    QPixmap pix_O_scaled = pix_O.scaled(35,35);
    QPixmap pix_NO_scaled = pix_NO.scaled(35,35);

    //Definition des Brush
    QBrush panier (pix_panier_scaled);
    QBrush boue (pix_boue_scaled);
    QBrush herbe (pix_herbe_scaled);
    QBrush N (pix_N_scaled);
    QBrush NE (pix_NE_scaled);
    QBrush E (pix_E_scaled);
    QBrush SE (pix_SE_scaled);
    QBrush S (pix_S_scaled);
    QBrush SO (pix_SO_scaled);
    QBrush O (pix_O_scaled);
    QBrush NO (pix_NO_scaled);

    //on ouvre le fichier map.txt
    ifstream map((const char*)path->toLocal8Bit(), ios::in); // on ouvre le fichier en lecture

            if(map)  // si l'ouverture a réussi
            {
                while((!map.eof())&&(i<(16*16))) //tant qu'on a pas lu le fichier en entier
                {

                    x = i/16; //x = l'indice des lignes
                    y = i%16; //y = l'indice des colonnes
                    //cerr<<"i : "<<i<<"    -      x : "<<x<<"       -      y :"<<y<<endl;
                    map >> temp; // on lit l'entier

                    if((x<16)&&(y<16)) {elem[x][y]=temp;ref->setChemin(x,y,temp);} //si on est sur la scène mettre l'indice dans elem
                    //(elem sera utilisé dans la seconde partie de la fonction)

                        if (temp==0){ //si 0 -> herb
                            rect = new QGraphicsRectItem(y*35,x*35,35,35); // On construit un rectangle
                            rect->setBrush(herbe); // on le "paint" avec la brush herbe
                            rect->setPen(QPen(Qt::NoPen)); //On efface les bordures
                            ref->setObjectMap(x,y,rect); //on place l'objet dans le répertoire du gestionnaire principal
                            this->addItem(ref->getObjectMap(x,y)); //on affiche l'objet sur la scène
                            ref->setName(x,y,new QString(tr("Terrain de type herbe : \n- constructible")));
                        }
                        if (temp>10)
                        {

                            if (temp==64) // si 64 -> boue
                            {

                            rect = new QGraphicsRectItem(y*35,x*35,35,35);
                            rect->setBrush(boue);
                            rect->setPen(QPen(Qt::NoPen));
                            ref->setName(x,y,new QString(tr("Terrain boueux :\n- inconstructible")));
                            ref->setObjectMap(x,y,rect);
                            ref->setConstructible(x,y,false);
                            this->addItem(ref->getObjectMap(x,y));
                            }
                            else if (temp==32) // si 32 -> Panier
                            {
                                rect = new QGraphicsRectItem(y*35,x*35,35,35);
                                rect->setBrush(panier);
                                rect->setPen(QPen(Qt::NoPen));
                                ref->setObjectMap(x,y,rect);
                                this->addItem(ref->getObjectMap(x,y));
                                ref->setName(x,y,new QString(tr("Votre Pic-nic :\nProtegez-le !!")));
                                ref->setConstructible(x,y,false);
                                ref->setX_fin(x);
                                ref->setY_fin(y);
                            }
                            else // sinon c'est le début
                            {
                            this->ref->setX_deb(x); //Mise à jour des coordonées du début dans le gestionnaire principal
                            this->ref->setY_deb(y);
                            ref->setName(x,y,new QString(tr("Terrain de type sentier : \n- inconstructible")));
                            elem[x][y]=temp-16;
                            ref->setChemin(x,y,temp-16);//Stockage de la valeur -12
                            }

                        }
                        i++; //mise à jour de x et y;

                }
                //Si on veut faire apparaitre un chemin avec des coudes il est nécessaire de faire la différence par exemple entre un element 6 (= Sud-Ouest)
                //qui sert de jonction entre un sud et un ouest et un 6 qui sert de jonction entre un est et un sud, car les coudes ne seront pour le même 6 pas les mêmes.

                //Idee : Parcourir le chemin depuis le début jusqu'au panier en construisant pas à pas le bon élément graphique

                x=ref->getX_deb(); // on se place au début
                y=ref->getY_deb();

                prev=elem[x][y];// on initialise l'élément "précédent" avec l'élément de départ
                int ok = 0; // indique si on est arrivé au panier

                while(!ok) //tant que pas arrivé au panier
                {
                    switch (elem[x][y]) //on regarde quelle est l'élément à afficher
                    {
                    case 1://si NORD, pas de problème on affiche un nord
                        prev=elem[x][y];
                        rect = new QGraphicsRectItem(y*35,x*35,35,35);//on cree l'objet
                        rect->setBrush(QBrush(O)); //= brush Ouest, voir les fichiers jpg pour comprendre
                        rect->setPen(QPen(Qt::NoPen));
                        ref->setObjectMap(x,y,rect);//on le referencie
                        ref->setConstructible(x,y,false);//on indique que l'emplacement n'est plus constructible
                        this->addItem(ref->getObjectMap(x,y)); // on l'affiche
                        x--; // on se dirige vers le prochain tronçon de chemin
                        break;

                    case 2://si SUD, pas de problème on affiche un sud
                        prev=elem[x][y];
                        rect = new QGraphicsRectItem(y*35,x*35,35,35);
                        rect->setBrush(O);
                        rect->setPen(QPen(Qt::NoPen));
                        ref->setObjectMap(x,y,rect);
                        ref->setConstructible(x,y,false);
                        this->addItem(ref->getObjectMap(x,y));
                        x++;
                        break;

                    case 4://si EST, pas de problème on affiche un sud
                        prev=elem[x][y];
                        rect = new QGraphicsRectItem(y*35,x*35,35,35);
                        rect->setBrush(S);
                        rect->setPen(QPen(Qt::NoPen));
                        ref->setObjectMap(x,y,rect);
                        ref->setConstructible(x,y,false);
                        this->addItem(ref->getObjectMap(x,y));
                        y++;
                        break;

                    case 8://si OUEST, pas de problème on affiche un ouest
                        prev=elem[x][y];
                        rect = new QGraphicsRectItem(y*35,x*35,35,35);
                        rect->setBrush(S);
                        rect->setPen(QPen(Qt::NoPen));
                        ref->setObjectMap(x,y,rect);
                        ref->setConstructible(x,y,false);
                        this->addItem(ref->getObjectMap(x,y));
                        y--;//ON VA A GAUCHE
                        break;

                    case 5: //si NORD-EST, on ne sait pas si on doit afficher un coude du sud vers est, ou de ouest vers le nord
                        switch(prev) // on regarde donc dans quelle direction on arrive
                        {
                        case 1://SI ON ARRIVE AVEC UNE DIRECTION SUD
                                rect = new QGraphicsRectItem(y*35,x*35,35,35);
                                rect->setBrush(NO); //ON MET UN COUDE NO = sud vers ouest
                                rect->setPen(QPen(Qt::NoPen));
                                ref->setObjectMap(x,y,rect);
                                this->addItem(ref->getObjectMap(x,y));
                                ref->setConstructible(x,y,false);
                                prev=4; //ET ON REPART AVEC UNE DIRECTION E
                                y++;//ON VA A DROITE
                                break;

                        case 4://SI ON ARRIVE AVEC UNE DIRECTION EST
                                rect = new QGraphicsRectItem(y*35,x*35,35,35);
                                rect->setBrush(SE); //ON MET UN COUDE SE = ouest vers nord
                                rect->setPen(QPen(Qt::NoPen));
                                ref->setObjectMap(x,y,rect);
                                this->addItem(ref->getObjectMap(x,y));
                                ref->setConstructible(x,y,false);
                                prev=1; //ET ON REPART AVEC UNE DIRECTION S
                                x--;//ON MONTE
                                break;

                        default: break;
                        }
                        break;



                    case 6: //SUD-EST, même systeme
                            switch(prev)
                            {
                            case 2://SI ON ARRIVE AVEC UNE DIRECTION SUD
                                rect = new QGraphicsRectItem(y*35,x*35,35,35);
                                rect->setBrush(SO); //ON MET UN COUDE SO
                                rect->setPen(QPen(Qt::NoPen));
                                ref->setObjectMap(x,y,rect);
                                this->addItem(ref->getObjectMap(x,y));
                                ref->setConstructible(x,y,false);
                                prev=4; //ET ON REPART AVEC UNE DIRECTION O
                                y++;//ON VA A GAUCHE
                                break;
                            case 4://SI ON ARRIVE AVEC UNE DIRECTION EST
                                rect = new QGraphicsRectItem(y*35,x*35,35,35);
                                rect->setBrush(NE); //ON MET UN COUDE NE
                                rect->setPen(QPen(Qt::NoPen));
                                ref->setObjectMap(x,y,rect);
                                this->addItem(ref->getObjectMap(x,y));
                                ref->setConstructible(x,y,false);
                                prev=2; //ET ON REPART AVEC UNE DIRECTION SUD
                                x++;//ON DESCEND
                                break;
                            default: break;
                            }
                            break;

                    case 10://SUD-OUEST, même systeme
                        switch(prev)
                        {
                        case 2://SI ON ARRIVE AVEC UNE DIRECTION SUD
                                rect = new QGraphicsRectItem(y*35,x*35,35,35);
                                rect->setBrush(SE); //ON MET UN COUDE SE
                                rect->setPen(QPen(Qt::NoPen));
                                ref->setObjectMap(x,y,rect);
                                this->addItem(ref->getObjectMap(x,y));
                                ref->setConstructible(x,y,false);
                                prev=8; //ET ON REPART AVEC UNE DIRECTION O
                                y--;//ON VA A DROITE
                                break;

                        case 8://SI ON ARRIVE AVEC UNE DIRECTION EST
                                rect = new QGraphicsRectItem(y*35,x*35,35,35);
                                rect->setBrush(NO); //ON MET UN COUDE NO
                                rect->setPen(QPen(Qt::NoPen));
                                ref->setObjectMap(x,y,rect);
                                this->addItem(ref->getObjectMap(x,y));
                                ref->setConstructible(x,y,false);
                                prev=2; //ET ON REPART AVEC UNE DIRECTION S
                                x++;//ON DESCEND

                                break;

                        default: break;
                        }
                        break;

                    case 9://NORD-OUEST, même systeme
                        switch(prev)
                        {
                        case 1://SI ON ARRIVE AVEC UNE DIRECTION SUD
                                rect = new QGraphicsRectItem(y*35,x*35,35,35);
                                rect->setBrush(NE); //ON MET UN COUDE NE
                                rect->setPen(QPen(Qt::NoPen));
                                ref->setObjectMap(x,y,rect);
                                this->addItem(ref->getObjectMap(x,y));
                                ref->setConstructible(x,y,false);
                                prev=8; //ET ON REPART AVEC UNE DIRECTION O
                                y--;//ON VA A GAUCHE
                                break;

                        case 8://SI ON ARRIVE AVEC UNE DIRECTION EST
                                rect = new QGraphicsRectItem(y*35,x*35,35,35);
                                rect->setBrush(SO); //ON MET UN COUDE SO
                                rect->setPen(QPen(Qt::NoPen));
                                ref->setObjectMap(x,y,rect);
                                this->addItem(ref->getObjectMap(x,y));
                                ref->setConstructible(x,y,false);
                                prev=1; //ET ON REPART AVEC UNE DIRECTION S
                                x--;//ON MONTE
                                break;

                        default: break;
                        }
                        break;
                    default: //SINON = PANIER
                        prev=elem[x][y];
                        rect = new QGraphicsRectItem(y*35,x*35,35,35);
                        rect->setBrush(QBrush(O));
                        rect->setPen(QPen(Qt::NoPen));
                        ref->setObjectMap(x,y,rect);
                        this->addItem(ref->getObjectMap(x,y));
                        ref->setConstructible(x,y,false);
                        rect = new QGraphicsRectItem(y*35,x*35,35,35);
                        rect->setBrush(panier);
                        rect->setPen(QPen(Qt::NoPen));
                        ref->setObjectMap(x,y,rect);
                        this->addItem(ref->getObjectMap(x,y));
                        x--;
                        ok=1;//ON EST ARRIVE A LA FIN DU CHEMIN, ON SORT
                        break;
                    }
                    if (ok!=1)
                    {
                    ref->setName(x,y,new QString(tr("Terrain de type sentier :\n- inconstructible")));
                    }
                    /*1 = chemin vers le Nord
                    2 = chemin vers le Sud
                    4 = chemin vers l’Est
                    8 = chemin vers l’Ouest
                    5 = chemin vers le NE
                    6 = chemin vers le SE
                    9 = chemin vers le NO
                    10 = chemin vers le SO
                    Une des valeurs précédentes + 16 = case de départ
                    32 = arrivée des ennemis*/


                }
                map.close();  // on ferme le fichier
            }
            else  // sinon
                    cerr << "Impossible d'ouvrir le fichier !" << endl;

}


//GETTER
myComputer * myScene::getComputer() const
{
    return this->ref;
}
//SETTER
myComputer * myScene::setComputer(myComputer * comp)
{
    this->ref=comp;
}

void myScene::timerEvent(QTimerEvent *) //A CHAQUE TICK D'HORLOGE
{
    this->advance(); //FAIRE VIVRE LES OBJETS
    collisionCheck(); //VERIFIER LES COLLISIONS

    if(stateTick==1) //ENVOYER UN SIGNAL SI DEMANDE
    {
        emit tick();
    }
}


void myScene::newWave() //LANCE LA VAGUE
{
    this->vague->createWave(this->vague->nextWave());
}

//MISE A JOURS DES DIFFERENTES LISTES DE REFERENTIATION

InsecteFactory * myScene::getVague() const
{
    return this->vague;
}

void myScene::pushInsect(Insecte * insecte)
{
    listeInsecte<<insecte;
}

void myScene::pushDefense(Defense * defense)
{
    listeDefense<<defense;
}

void myScene::pushMusicien(Musicien * musicien)
{
    listeMusicien<<musicien;
}

void myScene::removeInsect(Insecte * insecte)
{
    listeInsecte.removeAt(listeInsecte.indexOf(insecte));
}

void myScene::removeMusicien(Musicien * musicien)
{
    listeMusicien.removeAt(listeMusicien.indexOf(musicien));
}

void myScene::removeDefense(Defense * defense)
{
    this->removeEveryProjectileFrom(defense);
    listeDefense.removeAt(listeDefense.indexOf(defense));
}


//DETECTION DES COLISIONS

void myScene::collisionCheck()
{
    Defense* defense;
    Insecte* insecte;
    Projectile * projectile;
    Petanque * petanque;
    Paintball * paintball;
    Guepe * guepe;
    Cafard * cafard;
    int typeE;
    int typeD;
    int typeP;

    foreach(insecte,listeInsecte) //POUR CHAQUE INSECTE PRESENT SUR LA SCENE
    {
        foreach(projectile,listeProjectile) //POUR CHAQUE PROJECTILE PRESENT SUR LA SCENE
        {
            if(insecte->collidesWithItem(projectile)) //SI COLLISION
            {

                typeP=projectile->getType();
                typeE=insecte->getDep();
                if(typeP==3) //SI LE PROJETILE EST TIRE DEPUIS DEFENSE RAMPANT+VOLANT
                {
                     projectile->detruire(); //DETRUIRE LE PROJ
                    insecte->recevoirDegat(projectile->getDegat());//AFFLIGER DES DEGATS


                }
                else if(typeE==typeP) //SI LE TYPE D'INSECTE CORRESPOND AU TYPE DE TOUR
                {
                    projectile->detruire(); //IDEM
                    insecte->recevoirDegat(projectile->getDegat());

                }

            }

        }

        foreach(defense,listeDefense) //POUR CHAQUE DEFENSE
        {
            if(defense->canShoot()) //SI LA TOUR EST DANS UNE PHASE OU ELLE PEUT TIRER
            {
                if(defense->collidesWithItem(insecte)) // ET SI IL Y A COLLISION
                {
                    typeE=insecte->getDep();
                    typeD=defense->getType();

                    if(typeD==3) //SI VOLANT + RAMPANT
                    {
                            //ON TIRE, ON REFERENCIE LE PROJ,ON AJUSTE LA ROTATION DE LA TOUR, ET ON EMPECHE LA DEFENSE DE RETIRER
                            projectile = new Projectile (defense->getSound(),defense->getTailProj(),defense->getType(),defense->getFrappe(),defense->getVitProj(),defense->getColProj(),defense,insecte,0);
                            this->addItem(projectile);
                            listeProjectile<<projectile;
                            defense->disableShoot();
                            defense->suivre(insecte);

                    }
                    else if(typeD==typeE) //SI LE TYPE CORRESPOND
                    {
                        //IDEM
                        projectile = new Projectile (defense->getSound(),defense->getTailProj(),defense->getType(),defense->getFrappe(),defense->getVitProj(),defense->getColProj(),defense,insecte,0);
                        this->addItem(projectile);
                        listeProjectile<<projectile;
                        defense->disableShoot();
                        defense->suivre(insecte);

                    }
                }
            }
        }
        if(insecte->getHp()<=0) //SI L'INSECTE EN MEURT
        {
            if (guepe=dynamic_cast<Guepe*>(insecte)) //SI C'EST UNE GUEPE,
            {
                zoneDegat(guepe->pos().x(),guepe->pos().y(),1.5,guepe->getDegatZone()); //DEGAT DE ZONE
            }
            insecte->mourir();
        }
    }
}


void myScene::switchTick()
{
    stateTick=stateTick*-1;
}

void myScene::removeEveryProjectileFrom(Defense* defense)
{
    Projectile* projectile;
    foreach(projectile,listeProjectile)
    {
        if(projectile->getSource()==defense)
        {
            this->removeProjectile(projectile);
            delete projectile;
        }
    }
}

void myScene::removeProjectile(Projectile * projectile)
{
    listeProjectile.removeAt(listeProjectile.indexOf(projectile));
}

QSound * myScene::getSonPistolet_eau() const
{
    return this->sonPistolet_eau;
}
QSound * myScene::getSonPaintball() const
{
    return this->sonPaintball;
}
QSound * myScene::getSonPetanque() const
{
    return this->sonPetanque;
}
QSound * myScene::getSonLance_pierre() const
{
    return this->sonLance_pierre;
}
QSound * myScene::getSonMusicien() const
{
   return this->sonMusicien;
}

void myScene::zoneDegat(qreal x,qreal y,qreal rayon, float degat) //CREER UN CERCLE, SI DES INSECTES DANS CE CERCLE, LEUR AFFLIGER LE DEGAT
{
    QGraphicsEllipseItem * zone = new QGraphicsEllipseItem(x-(rayon*35),y-(rayon*35),rayon*2*35,rayon*2*35);
    zone->setPen(QPen(Qt::red));
    zone->setBrush(QBrush(Qt::NoBrush));
    this->addItem(zone);
    Insecte * insecte;
    foreach(insecte,listeInsecte)
    {
        if(insecte->collidesWithItem(zone))
        {
            insecte->recevoirDegat(degat);
        }
    }
   this->removeItem(zone);

}

void myScene::updateMusicien() //MET A JOUR LES EFFET DIFFUSER PAR LES MUSICIENS
{
    Musicien * musicien;
    int maxPercent;
    Defense * defense;

    foreach(defense,listeDefense) //POUR CHAQUE TOUR PRESENTE SUR LA MAP
    {
        maxPercent=0;
        foreach(musicien,listeMusicien) //POUR CHAQUE MUSICIEN
        {
            if(defense->collidesWithItem(musicien)) //EN COLISION,
            {
                if(maxPercent<musicien->getPercent()) //DETERMINER LE POURCENTAGE MAXIMUM DES MUSICIEN A PORTEE
                {
                    maxPercent=musicien->getPercent();
                }
            }

        }
        defense->checkUpgrade(maxPercent); //APPLIQUER CE POURCENTAGE
    }

}

myScene::~myScene()
{
    QList<QGraphicsItem *> list = this->items();
    QList<QGraphicsItem *>::Iterator it = list.begin();
    for (; it != list.end(); ++it)
    {
            if ( *it )
                delete *it;
    }

}

void myScene::freeze() //MET LE JEU EN PAUSE
{
    this->killTimer(timerId);
}

void myScene::unfreeze() //REMET EN JEU
{
    timerId=this->startTimer(20);
}


//LES DEFENSES AYANT UN CERCLE DE PORTEE INVISIBLE INCLU DANS LEUR BOUNDING RECT, SI LA PORTEE D'UNE TOUR EN RECOUVRE UNE AUTRE,
//CETTE DERNIERE N'EST PLUS CLIQUABLE, C'EST LA PORTEE QUI RECUPERE LE CLIQUE, IL FAUT DONC GERER LA PROFONDEUR DES TOURS, CLIQUE ET NON CLIQUE
void myScene::setFront(Defense * defenseItem)
{
    Defense * defense;
    foreach(defense,listeDefense) //POUR TOUTES LES TOURS NON CLIQUER
    {
        if(defense!=defenseItem)
        {
            defense->setZValue(2000); //METTRE LA PROFONDEUR A 2000
        }
    }
}
