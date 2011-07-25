#ifndef CAFARD_H
#define CAFARD_H
#include "insecte.h"
#include <QTimer>
class Cafard: public Insecte
{
public:
    Cafard(int x,int y,float taille,QGraphicsScene *scene=0);
    void dupliquer();
    void fils2();
    void mourir();
private:
    QTimer tFils2;
    //static QList<QPixmap> sprite;
};

#endif // CAFARD_H
