#ifndef PAINTBALL_H
#define PAINTBALL_H


#include "defense.h"
#include <QSound>



class Paintball : public Defense
{
private:
    void ameliorer();

public:
    explicit Paintball(QSound * s,bool enable,QGraphicsItem *parent = 0);
    void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );
    virtual QRectF boundingRect() const;
    QPainterPath shape() const;

    void updateDesc();


signals:

public slots:

};

#endif // PAINTBALL_H
