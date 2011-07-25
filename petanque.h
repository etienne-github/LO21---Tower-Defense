#ifndef PETANQUE_H
#define PETANQUE_H

#include "defense.h"
#include <QSound>



class Petanque : public Defense
{
private:
    void ameliorer();
    float degatZone;

public:
    explicit Petanque(QSound * s,bool enable,QGraphicsItem *parent = 0);
    void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );
    virtual QRectF boundingRect() const;
    QPainterPath shape() const;
    void updateDesc();
    float getDegatZone() const;

signals:

public slots:

};

#endif // PETANQUE_H
