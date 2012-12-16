#ifndef NOUVEAUFICHIER_H
#define NOUVEAUFICHIER_H

#include <QDialog>
#include <QString>
#include <QFileDialog>

namespace Ui {
class NouveauFichier;
}

class NouveauFichier : public QDialog
{
    Q_OBJECT
    
public:
    explicit NouveauFichier(QWidget *parent,bool shadow=true);
    ~NouveauFichier();

    QString Get_fichier()const;

    QString Get_fin()const;
    QString Get_dossier()const;
    int Get_tabulation()const;

private slots:
    void accept();
    void reject();

    void on_toolButton_clicked();

signals:
    void Get_ok(bool);
    
private:
    bool m_shadow;
    Ui::NouveauFichier *ui;
};

#endif // NOUVEAUFICHIER_H
