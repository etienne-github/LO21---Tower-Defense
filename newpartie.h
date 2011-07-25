#ifndef NEWPARTIE_H
#define NEWPARTIE_H

#include <QWidget>
#include <QtGui/QtGui>
#include <QPushButton>

class Newpartie : public QWidget
{
    Q_OBJECT
private:
    QPushButton * ok;
    QComboBox * maps;
    QComboBox * vagues;
    QComboBox * difficultes;
public:
    explicit Newpartie(QWidget *parent = 0);

signals:

public slots:
    void load();
};

#endif // NEWPARTIE_H
