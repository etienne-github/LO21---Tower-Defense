#ifndef COMPUTER_H
#define COMPUTER_H
#include <QGraphicsItem>
#include <QtGui/QtGui>
class Computer
{
    Q_OBJECT
public:
    Computer();
    int x_deb;
    int y_deb;
    int x_fin;
    int y_fin;
    QGraphicsItem* objectMap[16][16];
    bool constructible[16][16];
    int vie;
    int credit;
signals:
  void vieChanged();
  void creditChanged();

};

#endif // COMPUTER_H
