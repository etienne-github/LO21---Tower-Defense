#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QWidget>
#include <QtGui/QtGui>

class Gameover : public QWidget
{
    Q_OBJECT
private:
    QLabel * texte;
    QPushButton * quitter;
    QPushButton  *newPartie;
public:
    explicit Gameover(QWidget *parent = 0);

signals:

public slots:
    void reload();
    void leaveGame();

};

#endif // GAMEOVER_H
