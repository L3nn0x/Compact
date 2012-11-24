#ifndef EDITEUR_H
#define EDITEUR_H

#include <QTextEdit>
#include <QFile>
#include <QCloseEvent>
#include <QTextStream>

#include "myhighlight.h"

class Editeur : public QTextEdit
{
    Q_OBJECT
public:
    explicit Editeur(QString,void*,QWidget *parent = 0);
    explicit Editeur(QString,QString,void*,QWidget* parent=0);

    QString Get_nom()const{return nom;}
    bool Get_modified()const{return modified;}
    void* Get_parent()const{return projet;}

    void sauvegarder();
    void reset();

    void setHigh();

    ~Editeur();
    
signals:
    void Fermer(Editeur*);
    void Change(QString,bool);

public slots:
    void closeEvent(QCloseEvent *);
    void TChange();
    
private:
    QString nom;
    bool modified;
    QString buffer;
    QString fichier;
    void* projet;

    MyHighlight* high;
};

#endif // EDITEUR_H
