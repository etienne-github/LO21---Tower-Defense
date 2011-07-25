#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QActionGroup>
#include "gameover.h"



namespace Ui {
    class MainWindow;
}

class myComputer;
class myScene;
class myView;
class myDockWidget;
class myBuilder;


class MainWindow : public QMainWindow
{
    Q_OBJECT


private:
    Ui::MainWindow *ui;
    myComputer * centralComputer; //Objet qui gère les variables globales vie, crédit, position de la souris etc..
    myScene *scene; //Espace de création et d'interaction des object
    myView *view; //Widget d'affichage de la scene
    myDockWidget *dock; //Interface de commande avec l'utilisateur
    myBuilder *builder; //Objet qui gère la construction des défenses
    //void mousePressEvent ( QMouseEvent * event );
    QMenu *animationMenu;
    QMenu *helpMenu;
    QAction *playAct;
    QAction *pauseAct;
    QAction *resetAct;
    QAction *quiitAct;
    QAction *aboutAct;
    QActionGroup * alignmentGroup;
    Gameover * gameover;


public:

    //CONSTRUCTOR - DESTRUCTOR
    explicit MainWindow(QString carte, QString vagues, int vie, int credit,QWidget *parent=0);
    ~MainWindow();
    void createActions();
    void createMenus();
    void popGameOver();


    //GETTERS
    myComputer * getComputer() const;
    myScene * getScene() const;
    myView * getView() const;
    myDockWidget * getDock() const;
    myBuilder * getBuilder() const;

    //SETTERS
    void setComputer(myComputer * comp);
    void setScene(myScene * scene);
    void setView(myView * view);
    void setDock(myDockWidget * dock);
    void setBuilder(myBuilder * builder);





signals:

public slots:
    void play();
    void pause();
    void reset();
    void about();
    void leaveGame();

};

#endif // MAINWINDOW_H
