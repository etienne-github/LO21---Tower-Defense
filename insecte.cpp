#include "insecte.h"

 #include <QtGui/qbitmap.h>
 #include <QtGui/qpainter.h>
#include "myscene.h"
#include "mycomputer.h"
#include <iostream>
#include <QSound>
using namespace std;


extern QString * sourcePath;
 Insecte::Insecte(const QList<QPixmap> &animation,QSound * son,float taille,int dep,float vitesse,float resistance,float hp,QGraphicsScene *scene)
     :QObject(0), QGraphicsItem(0,0), currentFrame(0), vx(0), vy(0),taille(taille),dep(dep),vitesse(vitesse),resistance(resistance),hp(hp),son(son)
 {
     //SON QUAND MEURT
     QString * path = new QString(*sourcePath);
     money = new QSound(*path+"money.mp3");

     //INITIALISATION DE LA SEQUENCE D'IMAGE POUR ANIMATION
     for (int i = 0; i < animation.size(); ++i) {
         QPixmap pixmap = animation.at(i).scaled(35*taille,35*taille);
         Frame frame;
         frame.pixmap = pixmap;
         frame.shape = QPainterPath();
         frame.boundingRect = pixmap.rect();
         frames << frame;

         //JOUER LE SON DE L'INSECTE SI PAS DEJA EN LECTURE
         if(son->isFinished())
         {
             this->son->setLoops(-1);
             this->son->play();
         }
     }
     this->setTransformOriginPoint(QPoint((35*taille)/2,(35*taille)/2));

     //CONNECTION AVEC SLOT DE RETOUR A LA VITESSE NORMALE A LA FIN DU TIMER
     connect(&(this->tRalentir),SIGNAL(timeout()),this,SLOT(VitesseBackNormalPaint()));
 }


 void Insecte::advance(int phase)
 {
     if (phase == 0)
     {
         //EN FONCTION DE LA PERCELLE DE CHEMIN, AVANCER DANS UNE DIRECTION
         switch(dynamic_cast<myScene*>(this->scene())->getComputer()->getChemin(round(this->pos().y()/35),round(this->pos().x()/35)))
         {
         case 1:
             this->setRotation(-90);
             vx=0;
             vy=-1;
             break;
         case 2:
             this->setRotation(90);
             vx=0;
             vy=1;
             break;
         case 4:
             this->setRotation(0);
             vx=1;
             vy=0;
             break;
         case 5:
             this->setRotation(-45);
             vx=1/sqrt(2);
             vy=-1/sqrt(2);
             break;
         case 6:
             this->setRotation(45);
             vx=1/sqrt(2);
             vy=1/sqrt(2);
             break;
         case 8:
            this->setRotation(180);
            vx=-1;
            vy=0;
            break;
         case 9:
             this->setRotation(-135);
             vx=-1/sqrt(2);
             vy=-1/sqrt(2);
             break;
          case 10:
             this->setRotation(135);
             vx=-1/sqrt(2);
             vy=1/sqrt(2);
             break;
          case 32: //SI PANIER, RETIRER VIE ET MOURRIR
             dynamic_cast<myScene*>(this->scene())->removeInsect(this);
             dynamic_cast<myScene*>(this->scene())->getComputer()->setVie((dynamic_cast<myScene*>(this->scene())->getComputer()->getVie())-1);
             delete this;
             break;
             default: break;
         }
         dx=vx*vitesse*(35.0/50); //(vx,vy) est un vercteur unitaire, il faut lui multiplier la vitesse
         dy=vy*vitesse*(35.0/50);

         if(son->isFinished()) //SI LE SON DE L'INSECTE N'EST PAS EN COURT, LE LIRE
         {
             this->son->setLoops(-1);
             this->son->play();
         }
     }
     if (phase == 1)
     {
         changeFrame(); //IMAGE SUIVANTE
         moveBy(dx, dy); //AVANCER
     }
 }

 QRectF Insecte::boundingRect() const
 {
     return frames.at(currentFrame).boundingRect;
 }

 QPainterPath Insecte::shape() const
 {
     const Frame &f = frames.at(currentFrame);
     if (f.shape.isEmpty()) {
         QPainterPath path;
         path.addRegion(f.pixmap.createHeuristicMask());
         const_cast<Frame &>(f).shape = path;
     }
     return f.shape;
 }

 void Insecte::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/,
                                QWidget * /*widget*/)
 {
     painter->drawPixmap(0, 0, frames.at(currentFrame).pixmap);
 }


 void Insecte::recevoirDegat(float degat)
 {
    float deg = (degat-resistance);
    if (deg<0)
    {
        deg=1;
    }
    hp-=deg;


 }

 void Insecte::mourir()
 {
     dynamic_cast<myScene*>(this->scene())->getComputer()->setCredit((dynamic_cast<myScene*>(this->scene())->getComputer()->getCredit())+1);
     dynamic_cast<myScene*>(this->scene())->removeInsect(this);
     if (!son->isFinished())
     {
        son->stop();
     }
     money->setLoops(1); //SON d'argent gagné.
     money->play();
     delete this;
 }

 void Insecte::ralentir() //EFFET DU FUSIL PAINTBALL
 {
     if(!tRalentir.isActive())
     {
         vitesse=vitesse/2;
         tRalentir.setSingleShot(true);
         tRalentir.setInterval(20*50*4);
         tRalentir.start();
     }
 }

 void Insecte::VitesseBackNormalPaint()
 {
     vitesse=vitesse*2;
 }
