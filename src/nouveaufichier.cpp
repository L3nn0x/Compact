#include "nouveaufichier.h"
#include "ui_nouveaufichier.h"

NouveauFichier::NouveauFichier(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NouveauFichier)
{
    ui->setupUi(this);
}

NouveauFichier::~NouveauFichier()
{
    delete ui;
}

QString NouveauFichier::Get_fichier()const{return ui->nom_fichier->text();}

void NouveauFichier::accept()
{
    if(!ui->nom_fichier->text().isEmpty()&&!ui->nom_fichier->text().contains(QChar('*')))
        emit Get_ok(true);
}

void NouveauFichier::reject()
{
    emit Get_ok(false);
}
