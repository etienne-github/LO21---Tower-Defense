#ifndef MYBUILDER_H
#define MYBUILDER_H

#include <QObject>
#include <QSound>

class myComputer;
class myScene;
class myView;
class QGraphicsItem;
class QGraphicsRectItem;
class QGraphicsEllipseItem;
class QPainter;
class QTimer;
class QString;

using namespace std;
class myBuilder : public QObject
{
    Q_OBJECT
public:
    explicit myBuilder(myComputer* comp, myScene* scene,myView* view, QObject *parent = 0);
    int getActivated() const;
private:
    int activated;
    myComputer* comp;
    myScene* scene;
    myView* view;    
    QGraphicsRectItem * testSquare;
    QGraphicsEllipseItem * portee;
    QGraphicsItem * currentItem;
    QGraphicsItem * newItem;
    QTimer * timer;
    int x_deb;
    int y_deb;
    QSound *build;
    QSound *wrong;


signals:
    void switchMouseMoving();
public slots:
    void disableCuror();
    void createCursor();
    void destroyCursor();
    void updateCursor(float x, float y);
    void updateActivated(int i);
    void createDefense(float x, float y);
    //void infoWarning(QString * desc);
};

#endif // MYBUILDER_H
