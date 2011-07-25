#ifndef PISTOLET_EAU_H
#define PISTOLET_EAU_H


#include "defense.h"
#include <QSound>



class Pistolet_eau : public Defense
{
private:

    void updateDesc();

public:
    explicit Pistolet_eau(QSound *s,bool enable,QGraphicsItem *parent = 0);
    void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );
    virtual QRectF boundingRect() const;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*);
    void ameliorer();
    QPainterPath shape() const;
signals:

public slots:
   // void isClicked();

};

#endif // PISTOLET_EAU_H
