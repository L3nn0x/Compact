#ifndef NOUVEAUFICHIER_H
#define NOUVEAUFICHIER_H

#include <QDialog>
#include <QString>

namespace Ui {
class NouveauFichier;
}

class NouveauFichier : public QDialog
{
    Q_OBJECT
    
public:
    explicit NouveauFichier(QWidget *parent = 0);
    ~NouveauFichier();

    QString Get_fichier()const;

private slots:
    void accept();
    void reject();

signals:
    void Get_ok(bool);
    
private:
    Ui::NouveauFichier *ui;
};

#endif // NOUVEAUFICHIER_H
