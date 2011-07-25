#ifndef MYSCENE_H
#define MYSCENE_H

#include <QtGui/QtGui>


#include <QWidget>
#include <QTimer>
#include "insectefactory.h"
#include "insecte.h"
#include "defense.h"
#include "projectile.h"
#include <QSound>
#include "musicien.h"

class myComputer;


class myScene : public QGraphicsScene
{
    Q_OBJECT

private :
    myComputer* ref;
    void charger_map(QString carte); //Fonction de chargement de la configuration initial de la scene à partir du fichier map.txt

    void timerEvent(QTimerEvent *);
    InsecteFactory * vague;
    QList<Defense*> listeDefense;
    QList<Insecte*> listeInsecte;
    QList<Projectile *> listeProjectile;
    QList<Musicien *> listeMusicien;
    int stateTick;
public:
    ~myScene();
    void updateMusicien();
    void removeEveryProjectileFrom(Defense* defense);
    void setFront(Defense * defenseItem);
    void zoneDegat(qreal x,qreal y,qreal rayon, float degat);
    QList<QPixmap> animationFourmi;
    QList<QPixmap> animationGuepe;
    QList<QPixmap> animationCafard;
    QList<QPixmap> animationMoustique;
    QSound *sonFourmi;
    QSound *sonCafard;
    QSound *sonMoustique;
    QSound *sonGuepe;
    QSound *sonPistolet_eau;
    QSound *sonLance_pierre;
    QSound *sonMusicien;
    QSound *sonPaintball;
    QSound *sonPetanque;
    int timerId;
    //CONSTRUCTOR
    explicit myScene(QString carte,QString vague,myComputer* comp = 0, QMainWindow* parent = 0);
    //GETTER
    myComputer * getComputer() const;
    //SETTER
    myComputer * setComputer(myComputer * comp);
    InsecteFactory * getVague() const;
    void pushInsect(Insecte * insecte);
    void pushDefense(Defense * defense);
    void pushMusicien(Musicien *);
    void removeInsect(Insecte * insecte);
    void removeDefense(Defense * defense);
    void removeProjectile(Projectile * projectile);
    void removeMusicien(Musicien *);
    void collisionCheck();
    QSound * getSonPistolet_eau() const;
    QSound * getSonPaintball() const;
    QSound * getSonPetanque() const;
    QSound * getSonLance_pierre() const;
    QSound * getSonMusicien() const;
    void freeze();
    void unfreeze();

    //OTHER

signals:
    void tick();

public slots:
    void newWave();
    void switchTick();


};

#endif // MYSCENE_H
