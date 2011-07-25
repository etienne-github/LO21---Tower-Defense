#ifndef DEFENSE_H
#define DEFENSE_H

#include <QGraphicsItem>
#include <QTimer>
#include <QSound>

class Insecte;
class QGraphicsItem;

class Defense :public QObject,public QGraphicsItem //CLASSE ABSTRAITE
{
    Q_OBJECT
public:
    //CONSTRUCTOR
    explicit Defense(QGraphicsItem *parent = 0);
    explicit Defense(QSound * son, bool enable,float portee,float cadence,float frappe,int niveau, int type,int prixBase,int prixLvl1,int prixLvl2,float vitProj,float tailleProj,QColor couleurProj,QGraphicsItem *parent=0);
    virtual ~Defense();
    void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );
    virtual QRectF boundingRect() const;
    QPainterPath shape() const;
    //GETTERS
    float getPortee() const;
    float getCadence() const;
    float getFrappe() const;
    int getNiveau() const;
    int getType() const;
    int getPrixBase() const;
    int getPrixLvl1() const;
    int getPrixLvl2() const;
    bool canShoot() const;
    float getTailProj();
    float getVitProj();
    QColor getColProj();
    QSound * getSound() const;
    void suivre(Insecte * insecte);

    QString* getDesc() const;
    //SETTERS
    void setPortee(float portee);
    void setCadence(float cadence);
    void setFrappe(float frappe);
    void setNiveau(int niveau);
    void setType(int type);
    void setDesc(QString * desc);
    virtual void ameliorer()=0; //fonction virtuelle pure$
    virtual void updateDesc()=0;
    int revendre();
    void disableShoot();
    void checkUpgrade(int percent);

protected:
        bool enable;
        float portee;
        float cadence;
        float frappe;
        int niveau;
        int type;
        int prixBase;
        int prixLvl1;
        int prixLvl2;
        QString * desc;
        QTimer tCadence;
        bool shoot;
        float vitProj;
        QColor couleurProj;
        float tailleProj;
        QSound * son;
        QSound * wrong;
        int upgrade;
        //virtual void mousePressEvent(QEvent*);

        //QGraphicsItem * sprite; //Image associé à l'objet

signals:

public slots:
     void enableShoot();


};

#endif // DEFENSE_H
