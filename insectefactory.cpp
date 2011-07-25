#include "insectefactory.h"
#include<QString>
#include <QGraphicsItem>
#include "fourmi.h"
#include "cafard.h"
#include "guepe.h"
#include "moustique.h"
#include<iostream>
#include<QTextStream>
#include <QTimer>
#include<QThread>
#include"mainwindow.h"
#include"mydockwidget.h"
#include "myscene.h"
#include "insecte.h"
#include "mycomputer.h"
using namespace std;

extern QString * sourcePath;

//L'insecte factory lit le fichier des vagues

//l'interprete en faisant un liste :
// ...--->15 Fourmi de taille 1 a 20 ms d'écart--->1 guepe de taille 1.3 à 25 ms d'ecart--->...

//Transforme cette première liste en une liste

// ---> Fourmi de taille 1 après 20 ms --> Fourmi de taille 1 après 20 ms -->...15 X puis...---> Guepe de taille 1.3 ms-->...

//Demande l'envoi du tick d'horloge par myScene

//Depile le premier insecte de la list, attend le temps donné et le crée.
//Depile le deuxieme insecte de la liste, attend et le cree
//                     .
//                     .
//                     .

//Quand pile vide : Demander l'arret de l'envoi du tick d'horloge


InsecteFactory::InsecteFactory(QString vague,QGraphicsScene* parent, QObject* objectParent):QObject(objectParent),scene(parent),tickCounter(0),listenTick(true)
{
    x_deb=dynamic_cast<myScene*>(scene)->getComputer()->getY_deb(); //probleme changement de repere getY refile le bon x et vice versa
    y_deb=dynamic_cast<myScene*>(scene)->getComputer()->getX_deb();
    QString * path = new QString(*sourcePath);
    path->append(vague);
    cerr<<(const char *)path->toLocal8Bit()<<endl;

    file = new QFile((const char*)path->toLocal8Bit());
    QString line;
    if (file->open(QIODevice::ReadOnly))
    {
            cerr<<"Le fichier vague a été ouvert correctement"<<endl;
            stream = new QTextStream(file);
    }
    else
    {
            cerr<<"Probleme avec le fichier des vagues"<<endl;
    }
}

insectBatchNode::insectBatchNode()
{

}

insectQueueNode::insectQueueNode()
{

}

insectQueueNode::insectQueueNode(QString type,float taille, int pas):type(type),taille(taille),pas(pas)
{

}

//void InsecteFactory::Reinitialiser(QString nomFicher);
QList<insectBatchNode> InsecteFactory::nextWave()
{
    int packetfield=0;
    QString * buffer = new QString();
    QString * description = new QString();
    QString line;
    insectBatchNode * temp;
    QList<insectBatchNode> batch;

    line = stream->readLine();

    if(!line.isNull())
    {
        line.append(QString(1,';'));
        int i=0;
        while(line.at(i)!=';')
        {
            //cerr<<QString(1,line.at(i)).toStdString();
            description->append(QString(1,line.at(i)));
            i++;
            //cerr<<"On passe par la desc a la  "<<i<<"eme fois"<<endl;
        }
            //cerr<<"La ligne n'est pas nulle"<<endl;        // line of text excluding '\n'
            //cerr<<line.toStdString()<<endl;
            dynamic_cast<MainWindow *>(scene->parent())->getDock()->setInfoVague(description);
            temp = new insectBatchNode;
            for(int j=i+1;j<line.size();j++)
            {

                if((line.at(j)==';')||(line.at(j)==':'))
                {
                    switch(packetfield%4)
                    {
                    case 0:
                        //cerr<<"On a fini le type :"<<buffer->toStdString()<<endl;
                        temp->type=*buffer;
                        break;
                    case 1:
                        //cerr<<"On a fini la taille :"<<buffer->toStdString()<<endl;
                        temp->taille=buffer->toFloat();
                        break;
                    case 2:
                       // cerr<<"On a fini le nombre :"<<buffer->toStdString()<<endl;
                        temp->nombre=buffer->toInt();
                        break;
                    case 3:
                       // cerr<<"On a fini le pas :"<<buffer->toStdString()<<endl;
                        temp->pas=buffer->toInt();
                        batch<<*temp;
                        temp = new insectBatchNode();
                        break;
                    }

                    buffer = new QString(); // ON REFAIT UN CHAMP
                    packetfield++; //ON CHANGE DE CHAMP
                }
                else
                {
                    //cerr<<"On passe par la concat a la "<<j<<"eme fois"<<endl;
                    buffer->append(QString(1,line.at(j)));  //SI PAS UN PT VIRGULE ON CONCAT
                    //cerr<<QString(1,line.at(j)).toStdString();
                }

            }
            //cerr<<"on envoie un batch de taille "<<batch.size()<<endl;
            return batch;
    }

    else
    {
        //cerr<<"La ligne est null";
        file->close();
    }


}

void InsecteFactory::createWave(QList<insectBatchNode> batch)
{
    //cerr<<"on arrive dans la fonction createWave"<<endl;
    insectBatchNode currentNode;
    insectQueueNode * temp;
    for(int i=0;i<batch.size();i++)
    {
       // cerr<<"on passe dans la boucle batch "<<i<<" fois"<<endl;
        currentNode=batch.at(i);
        for(int j=0;j<currentNode.nombre;j++)
       {
            temp=new insectQueueNode(currentNode.type,currentNode.taille,currentNode.pas);
            //cerr<<"on add une fourmi";
            queue<<*temp;



        }
        emit switchTick();
    }
}


QGraphicsItem* InsecteFactory::newItem(QString className, int x,int y, float taille, QGraphicsItem* parent) {
    QGraphicsItem* retval = 0;
    if (className == "fourmi") {
        //cerr<<"on creer une fourmi"<<endl;
        retval = new Fourmi(x,y,taille,scene);
    } else if (className == "cafard") {
        //cerr<<"on creer un cafard"<<endl;
        retval = new Cafard(x,y,taille,scene);
    } else if (className == "guepe") {
        //cerr<<"on creer une guepe"<<endl;
        retval = new Guepe(x,y,taille,scene);
    } else if (className == "moustique") {
       // cerr<<"on creer un moustique"<<endl;
    retval = new Moustique(x,y,taille,scene);
    } else {
     //cerr<<"Classe non reconnue"<<endl;
    }
    return retval;
}

void InsecteFactory::incrementTickCounter()
{
    if(!queue.empty())
    {
        //cerr<<"limite: "<<queue.first().pas<<endl;

        if (tickCounter<queue.first().pas)
        {
            tickCounter++;
            //cerr<<"tickCounter: "<<tickCounter<<endl;
            //cerr<<"limite: "<<queue.first().pas<<endl;
        }
        else
        {
            Insecte * newInsect = dynamic_cast<Insecte *>(newItem(queue.first().type,x_deb,y_deb,queue.first().taille));
            dynamic_cast<myScene*>(scene)->pushInsect(newInsect);
            scene->addItem(newInsect);
            queue.removeAt(0);
            tickCounter=0;
            //cerr<<"size: "<<queue.size()<<endl;
        }

    }
    else
    {
        tickCounter=0;
        emit switchTick();
    }


}


