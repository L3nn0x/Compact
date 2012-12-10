#ifndef PROJET_H
#define PROJET_H

#include <QList>
#include <QStandardItem>
#include <QFile>
#include <QChar>
#include <QMainWindow>

#include "editeur.h"
#include "compilo.h"

class Projet
{
public:
    Projet(QString,QString,QString,QStandardItem*);
    Projet(QString&,QStandardItem*,QMainWindow*);
    ~Projet();

    QStandardItem* addFichier(Editeur*,bool open=false);
    Editeur* getFichier(QStandardItem*);
    QStandardItem* getprojet(){return item;}
    QString Get_fin()const;
    bool Get_ok()const{return ok;}
    QString Get_dossier()const{return dossier;}
    QString Get_name()const{return name;}

    QString Compiler();

protected:
    QString dossier;
    QString name;
    QList<Editeur*> fichiers;
    QString fin_fichier;
    QStandardItem* item;
    bool ok;

    C* compilo;
};

#endif // PROJET_H
