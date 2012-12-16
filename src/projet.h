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
    int Get_tabulation()const{return Ltab;}
    void Set_tabulation(int a){Ltab=a;}

    QString Compiler();
    QMap<QString,int> Get_labels()const;
    bool compi_ok()const{return compilo->Get_result();}


protected:
    QString dossier;
    QString name;
    QList<Editeur*> fichiers;
    QString fin_fichier;
    QStandardItem* item;
    bool ok;
    int Ltab;

    C* compilo;
};

#endif // PROJET_H
