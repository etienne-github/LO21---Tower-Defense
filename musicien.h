#ifndef MUSICIEN_H
#define MUSICIEN_H

#include "defense.h"
#include <QSound>



class Musicien : public Defense
{
private:
    void ameliorer();
    int percent;

public:
    void updateDesc();
    explicit Musicien(QSound * s,bool enable,QGraphicsItem *parent = 0);
    void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );
    virtual QRectF boundingRect() const;
    QPainterPath shape() const;
    int getPercent() const;
    ~Musicien();
   // void updateDesc();

signals:

public slots:

};

#endif // MUSICIEN_H
