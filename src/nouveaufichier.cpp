#include "nouveaufichier.h"
#include "ui_nouveaufichier.h"

NouveauFichier::NouveauFichier(QWidget *parent,bool shadow) :
    QDialog(parent),m_shadow(shadow),
    ui(new Ui::NouveauFichier)
{
    ui->setupUi(this);
    if(shadow)
    {
        ui->frame->hide();
    }
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

QString NouveauFichier::Get_fin()const
{
    return ui->comboBox->currentText();
}

QString NouveauFichier::Get_dossier()const
{
    return ui->lineEdit->text();
}

void NouveauFichier::on_toolButton_clicked()
{
    ui->lineEdit->setText(QFileDialog::getExistingDirectory(this,
                                                          tr("Choisissez un dossier"),"/home",
                                                          QFileDialog::ShowDirsOnly
                                                          | QFileDialog::DontResolveSymlinks)+QDir::toNativeSeparators("/"));
}
