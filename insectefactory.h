#ifndef INSECTEFACTORY_H
#define INSECTEFACTORY_H
#include<QString>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include<QFile>
#include <fstream>
#include <iostream>
#include <QTextStream>
#include <QObject>
#include <QThread>



class insectBatchNode
{
public:
    explicit insectBatchNode();
    QString type;
    float taille;
    int nombre;
    int pas;
};

class insectQueueNode
{
public :
    explicit insectQueueNode();
    explicit insectQueueNode(QString type,float taille, int pas);
    QString type;
    float taille;
    int pas;
};

class InsecteFactory : public QObject
{
    Q_OBJECT
    virtual QGraphicsItem* newItem (QString className, int x,int y, float taille, QGraphicsItem* parent=0);
    //void Reinitialiser(QString nomFicher);

    QFile * file;
    QGraphicsScene * scene;
    QTextStream * stream;
    int tickCounter;
    bool listenTick;
    int x_deb;
    int y_deb;
    protected:
public:
    explicit InsecteFactory(QString vague,QGraphicsScene * parent=0,QObject* objectParent=0);
    void createWave(QList<insectBatchNode> batch);
    QList<insectBatchNode> nextWave();
    QList<insectQueueNode> queue;
signals:
    void switchTick();
public slots:
    void incrementTickCounter();


};




#endif // INSECTEFACTORY_H


//Il faut lire des triplet "type";taille(float);nombre(int);pas(int);
