#ifndef GUEPE_H
#define GUEPE_H
#include "insecte.h"
#include <QGraphicsScene>
#include <QList>
class Guepe: public Insecte
{
public:
    Guepe(int x,int y,float taille,QGraphicsScene *scene=0);
    float getDegatZone() const;
private:
    float degatZone;
    //static QList<QPixmap> sprite;
};
#endif // GUEPE_H
