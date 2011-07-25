#ifndef MYCOMPUTER_H
#define MYCOMPUTER_H

#include <QObject>

class QGraphicsItem;

class myComputer : public QObject
{
    Q_OBJECT
private :
    float mouseX; //Position x de la souris quand elle survole la scene
    float mouseY; //Position y de la souris quand elle survole la scene
    int x_deb; //Indice matriciel x du point d'appartition des ennemis
    int y_deb; //Indice matriciel y du point d'appartition des ennemis
    int x_fin; //Indice matriciel x du point but des ennemis
    int y_fin; //Indice matriciel y du point but des ennemis
    QGraphicsItem* objectMap[16][16]; //Repertoire des objets présents sur la scène
    int chemin[16][16];
    bool constructible[16][16]; //mappage matriciel booléen de la scène pour indiquer si l'emplacement est constructible
    QString * objectNameMap[16][16];
    int vie; //vie courante du joueur
    int credit; //crédit courant du joueur
public:
    //CONSTRUCTORS - DESTRUCTOR
    myComputer(int vie, int credit, QObject * parent=0);
    //~myComputer();
    //GETTERS
    float getMouseX() const;
    float getMouseY() const;
    int getX_deb() const;
    int getY_deb() const;
    int getX_fin() const;
    int getY_fin() const;
    QGraphicsItem* getObjectMap(int i,int j) const;
    bool isConstructible(int i,int j) const;
    QString* getName(int i,int j) const;
    int getChemin(int i,int j) const;
    int getVie() const;
    int getCredit() const;
    //SETTERS
    void setMouseX(float x);
    void setMouseY(float y);
    void setX_deb(int x);
    void setY_deb(int y);
    void setX_fin(int x);
    void setY_fin(int y);
    void setObjectMap(int i, int j,QGraphicsItem* object);
    void setConstructible(int i, int j, bool enable);
    void setChemin(int i,int j,int elem);
    void setName(int i, int j, QString* name);
    void setVie(int vie);
    void setCredit(int credit);
signals:
  void vieChanged(); //est envoyé lorsque la vie du joueur est modifiée (-> mise à jour du LCDNumber dans le Dock)
  void creditChanged();  //est envoyé lorsque les crédits du joueur sont modifiés (-> mise à jour du LCDNumber dans le Dock)

};

#endif // MYCOMPUTER_H
