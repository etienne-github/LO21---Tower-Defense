#ifndef FOURMI_H
#define FOURMI_H
#include "insecte.h"
#include <QGraphicsScene>
#include <QList>
#include <QTimer>
class Fourmi: public Insecte
{
public:
    Fourmi(int x,int y,float taille,QGraphicsScene *scene=0);
    void recevoirDegat(float degat);
    void accelerer();
    void vitesseBackNormal();
private:
    QTimer tAccelerer;
    //static QList<QPixmap> sprite;
};
#endif // FOURMI_H
