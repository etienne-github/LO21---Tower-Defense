#ifndef LANCE_PIERRE_H
#define LANCE_PIERRE_H
#include "defense.h"
#include <QSound>


class Lance_pierre : public Defense
{
private:
    void ameliorer();

public:
    explicit Lance_pierre(QSound * son,bool enable,QGraphicsItem *parent = 0);
    void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );
    virtual QRectF boundingRect() const;
    QPainterPath shape() const;
    void updateDesc();
signals:

public slots:

};

#endif // LANCE_PIERRE_H
