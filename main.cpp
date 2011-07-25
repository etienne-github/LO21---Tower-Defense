#include <QtGui/QApplication>
#include <QtGui/QtGui>
#include "mainwindow.h"
#include <iostream>
#include "newpartie.h"
#include <QString>

using namespace std;

MainWindow *w;
Gameover *go;
Newpartie * np;
QString * sourcePath;

int main(int argc, char *argv[])
{
    std::cerr<<"METTRE LE CHEMIN ABSOLU DE VOTRE EMPLACEMENT SOURCE DANS LA VARIABLE \"sourcePath\" DE \"main.cpp\""<<endl;


    QApplication a(argc, argv);

        sourcePath = new QString("/Users/etiennegirot/Library/Mail Downloads/TowerDefense 2/");


    np = new Newpartie;
    np->show();
    return a.exec();
}
