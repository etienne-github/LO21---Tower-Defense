#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <QGraphicsItem>
#include <QSound>
class Insecte;
class Defense;

class Projectile : public QGraphicsItem
{
private:
    float degat;
    float Vitesse;
    qreal dx;
    qreal dy;
    float taille;
    int type;
    QColor couleur;
    Defense * source;
    Insecte * destination;
public:
    explicit Projectile(QSound * son,float taille,int type, float degat, float Vitesse, QColor couleur, Defense* source, Insecte * cible, QGraphicsItem *parent=0);
    void advance(int phase);

    ~Projectile();
    void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
    int getType() const;
    float getDegat() const;
    Defense * getSource() const;
    void detruire();
    QRectF boundingRect() const;
    QPainterPath shape() const;
    QSound * son;
};

#endif // PROJECTILE_H
