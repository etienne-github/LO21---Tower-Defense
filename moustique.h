#ifndef MOUSTIQUE_H
#define MOUSTIQUE_H

#include "insecte.h"
#include <QGraphicsScene>
#include <QList>
#include <QTimer>
class Moustique: public Insecte
{
public:
    Moustique(int x,int y,float taille,QGraphicsScene *scene=0);
    void recevoirDegat(float degat);
    void poser();
    void envoler();
private:
    QTimer tPoser,tEnvoler;
    //static QList<QPixmap> sprite;

};
#endif // MOUSTIQUE_H
