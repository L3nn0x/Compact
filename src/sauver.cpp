#include "sauver.h"
#include "ui_sauver.h"

Sauver::Sauver(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Sauver)
{
    ui->setupUi(this);
}

Sauver::Sauver(QList<QListWidgetItem*> a,QCloseEvent *sig, QWidget *parent):QDialog(parent),ui(new Ui::Sauver),
    signal(sig)
{
    ui->setupUi(this);
    for(QList<QListWidgetItem*>::iterator it=a.begin();it!=a.end();++it)
        ui->listWidget->addItem((*it)->text());
}

Sauver::~Sauver()
{
    delete ui;
}

void Sauver::reject()
{
    emit ok(0);
}

void Sauver::on_buttonBox_clicked(QAbstractButton *a)
{
    QDialogButtonBox::StandardButton b=ui->buttonBox->standardButton(a);
    if(b==QDialogButtonBox::SaveAll)
        emit ok(1);
    else if(b==QDialogButtonBox::Discard)
        emit ok(-1);
    else
        emit ok(0);
}
