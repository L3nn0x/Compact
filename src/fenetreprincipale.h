#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include <QMainWindow>
#include <QString>
#include <QTextEdit>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QList>
#include <QMdiSubWindow>
#include <QListWidgetItem>
#include <QStandardItemModel>
#include <QSettings>
#include <QSignalMapper>

#include "projet.h"
#include "nouveauprojet.h"
#include "editeur.h"
#include "nouveaufichier.h"
#include "sauver.h"

namespace Ui {
    class FenetrePrincipale;
}

class FenetrePrincipale : public QMainWindow
{
    Q_OBJECT

public:
    explicit FenetrePrincipale(QWidget *parent = 0);
    ~FenetrePrincipale();

    void Modifyfont(); //modifie la font de tous les projets pour les mettre en gras

private slots:
    void on_actionFichiers_dans_le_projet_triggered(bool);
    void triggerArbre(bool);

    void on_actionFichiers_ouverts_triggered(bool);
    void triggerDocs(bool);

    void on_actionR_sultats_de_compilation_triggered(bool);
    void triggerComp(bool);

    void on_actionLabels_triggered(bool);
    void triggerLabels(bool);

    void on_actionNouveau_projet_triggered();
    void NouveauP(bool);

    void on_actionAfficher_sous_forme_d_onglets_triggered(bool);
    void on_actionAfficher_en_cascade_triggered();
    void on_actionAfficher_tout_en_m_me_temp_triggered();

    void on_actionNouveau_fichier_triggered();
    void NouveauF(bool);

    void on_actionOuvrir_triggered();

    void on_treeView_doubleClicked(QModelIndex);

    void close_sub_win(Editeur *);
    void choose_sub_win(QListWidgetItem*);

    void toggle_asterix(QString,bool);

    void on_actionEnregistrer_triggered();
    void on_actionTout_enregistrer_triggered();

    void Fermerprojet(int);

    void Sauver_return(int);

    void closeEvent(QCloseEvent *);

    void customContextMenu(QPoint);

    void AjouterFichier();

private:
    Ui::FenetrePrincipale *ui;
    NouveauProjet *projet;
    NouveauFichier *fichier;
    Sauver *sauver;

    QStandardItemModel *treeview;

    QList<Projet*> projets;
    Projet *projetPrinc;

    QSignalMapper* signalmapper;

    bool end;
};

#endif // FENETREPRINCIPALE_H
