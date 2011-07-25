#ifndef INSECTE_H
#define INSECTE_H

#include <QGraphicsItem>
#include <QObject>
#include <QSound>
#include <iostream>
#include <QTimer>

class Insecte : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Insecte(const QList<QPixmap> &animation,QSound * son,float taille, int dep,float vitesse,float resistance,float hp, QGraphicsScene *scene = 0);
    inline int getDep() const
    { return dep; }
    inline void setFrame(int frame)
    {
        if (!frames.isEmpty()) {
            prepareGeometryChange();
            currentFrame = frame % frames.size();
        }
    }

    inline int frame() const
    { return currentFrame; }
    inline int frameCount() const
    { return frames.size(); }
    inline QPixmap image(int frame) const
    { return frames.isEmpty() ? QPixmap() : frames.at(frame % frames.size()).pixmap; }
    inline void setVelocity(qreal xvel, qreal yvel)
    { vx = xvel; vy = yvel; }
    inline qreal xVelocity() const
    { return dx; }
    inline qreal yVelocity() const
    { return dy; }
    inline float getVitesse() const
    { return vitesse;}
    inline float getHp() const
    { return hp; }
    virtual void mourir();
    virtual void recevoirDegat(float degat);
    virtual void poser(){}
    virtual void envoler(){}
    virtual void vitesseBackNormal(){}
    virtual void fils2(){}
    void ralentir();

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void advance(int phase);
public slots:
    inline void changeFrame()
    {
        this->setFrame((frame()+1)%frameCount());
    }
    virtual void slotPoser()
    {poser();}
    virtual void slotEnvoler()
    {envoler();}
    virtual void slotVitesseBackNormal()
    {vitesseBackNormal();}
    void VitesseBackNormalPaint();
    virtual void slotFils2()
    { fils2(); }

private:
    struct Frame {
        QPixmap pixmap;

        QPainterPath shape;
        QRectF boundingRect;
    };

    int currentFrame;
    QList<Frame> frames;
    qreal vx, vy,dx, dy;
    QTimer tRalentir;
protected:
    float taille; 				/*!< taille*/
    int dep;		/*!< mode de dÈplacement*/
    float vitesse;				/*!< vitesse de dÈplacement*/
    float resistance;			/*!< resistance*/
    float hp;
    QSound * son;
    QSound * money;
};

#endif
