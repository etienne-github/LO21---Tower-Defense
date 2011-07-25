#ifndef MYDOCKWIDGET_H
#define MYDOCKWIDGET_H

#include <QWidget>
#include<QDockWidget>


class myPushButton;
class QPushButton;
class QLCDNumber;
class QLabel;
class myComputer;


class myDockWidget : public QDockWidget
{
    Q_OBJECT
private:
    //myPushButton * buttonTab[5];
    QPushButton *newWave; //Bouton nouvelle vague
    myPushButton *newEau; //Bouton nouvelle défense pistolet à eau
    myPushButton *newPetanque; //Bouton nouvelle défense Pétanque
    myPushButton *newMusicien; //Bouton nouvelle défense musicien
    myPushButton *newPaintball; //Bouton nouvelle defense Paintball
    myPushButton *newLance_pierre; //Bouton nouvelle defense Lance_pierre
    QLCDNumber* LCDcredit; //Afficheur 7 segment pour les crédit
    QLCDNumber* LCDvie; //Afficheur 7 segment pour la vie
    QLabel *infoVague; //Text d'information sur les vagues d'ennemis
    QLabel *infoDefense; //Text d'information sur les defenses ou objet cliqué
    myComputer * comp; //Référence au gestionnaire principal
    QPushButton *sellDefense;
    QPushButton *updateDefense;
public:
    myPushButton * buttonTab[5];
    QString * buttonDesc[5];
    //CONSTRUCTOR
    explicit myDockWidget(myComputer* comp, QWidget *parent = 0);
    //GETTERS
   // QGroupBox * getVerticalGroupBox() const;
    QPushButton * getNewWave() const;
    myPushButton * getNewEau() const;
    myPushButton * getNewPetanque() const;
    myPushButton * getNewMusicien() const;
    myPushButton * getNewPaintball() const;
    myPushButton * getNewLance_pierre() const;
    QLCDNumber* getLCDcredit() const;
    QLCDNumber* getLCDvie() const;
    QLabel * getInfoVague() const;
    QLabel * getInfoDefense() const;
    myComputer * getComputer() const;
    myPushButton* getButton(int i) const;
    QString* getButtonDesc(int i) const;
    QPushButton * getUpdateDefense() const;
    QPushButton * getSellDefense() const;
    void showUpdateDefense();
    void showSellDefense();
    void hideUpdateDefense();
    void hideSellDefense();


    //void setVerticalGroupBox();
    //void setNewWave();
    //void setNewEau();
    //void setNewPetanque();
    //void setNewMusicien();
    //void setNewPaintball();
    //void setLCDcredit(int i);
    //void setLCDvie(int i);
    void setInfoVague(QString * s);
    void setInfoDefense(QString * s);
    void setComputer(myComputer * comp);
signals:
    void finished();
public slots:
    void updateVie(); //met à jour l'afficheur de la vie en fonction de comp->vie
    void updateCredit(); //met à jour l'afficheur du credit en fonction de comp->credit
};

#endif // MYDOCKWIDGET_H
