#ifndef SAUVER_H
#define SAUVER_H

#include <QDialog>
#include <QAbstractButton>
#include <QList>
#include <QListWidget>

namespace Ui {
class Sauver;
}

class Sauver : public QDialog
{
    Q_OBJECT
    
public:
    explicit Sauver(QWidget *parent = 0);
    Sauver(QList<QListWidgetItem*>,bool,QWidget *parent=0);
    ~Sauver();

    bool Get_signal()const{return signal;}

public slots:
    void on_buttonBox_clicked(QAbstractButton*);
    void reject();

signals:
    void ok(int);
    
private:
    Ui::Sauver *ui;

    bool signal;
};

#endif // SAUVER_H
