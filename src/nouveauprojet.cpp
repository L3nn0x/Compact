#include "nouveauprojet.h"
#include "ui_nouveauprojet.h"

NouveauProjet::NouveauProjet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NouveauProjet)
{
    ui->setupUi(this);
}

NouveauProjet::~NouveauProjet()
{
    delete ui;
}

void NouveauProjet::accept()
{
    if(!ui->fichier_nom->text().isEmpty()&&!ui->Chemin->text().isEmpty()
            &&!ui->projet_nom->text().isEmpty()&&!ui->fichier_nom->text().contains(QChar('*')))
        emit Get_ok(true);
}

void NouveauProjet::reject()
{
    emit Get_ok(false);
}

void NouveauProjet::on_toolButton_clicked()
{
    ui->Chemin->setText(QFileDialog::getExistingDirectory(this,
                                                          tr("Choisissez un dossier"),"/home",
                                                          QFileDialog::ShowDirsOnly
                                                          | QFileDialog::DontResolveSymlinks)+QDir::toNativeSeparators("/"));
}

QString NouveauProjet::Get_projet()const {return ui->projet_nom->text();}
QString NouveauProjet::Get_fichier()const {return ui->fichier_nom->text();}
QString NouveauProjet::Get_fin()const {return ui->fin_nom->currentText();}
QString NouveauProjet::Get_rep()const {return ui->Chemin->text();}
