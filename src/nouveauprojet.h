#ifndef NOUVEAUPROJET_H
#define NOUVEAUPROJET_H

#ifndef __WIN32__
#define __WIN32__ 0
#endif

#include <QDialog>
#include <QString>
#include <QFileDialog>

namespace Ui {
class NouveauProjet;
}

class NouveauProjet : public QDialog
{
    Q_OBJECT
    
public:
    explicit NouveauProjet(QWidget *parent = 0);
    ~NouveauProjet();

    QString Get_projet()const;
    QString Get_fichier()const;
    QString Get_fin()const;
    QString Get_rep()const;

private slots:
    void on_toolButton_clicked();
    void accept();
    void reject();

signals:
    void Get_ok(bool);

private:
    Ui::NouveauProjet *ui;
};

#endif // NOUVEAUPROJET_H
