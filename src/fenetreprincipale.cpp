#include "fenetreprincipale.h"
#include "ui_fenetreprincipale.h"

FenetrePrincipale::FenetrePrincipale(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FenetrePrincipale),projetPrinc(0),end(false)
{
    ui->setupUi(this);
    ui->mdiArea->setAttribute(Qt::WA_DeleteOnClose,false);
    ui->mdiArea->setDocumentMode(true);
    showMaximized();
    treeview=new QStandardItemModel();
    ui->treeView->setModel(treeview);
    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);

    signalmapper=new QSignalMapper();

    QObject::connect(ui->treeView,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(customContextMenu(QPoint)));

    QObject::connect(ui->Arbre,SIGNAL(visibilityChanged(bool)),this,SLOT(triggerArbre(bool)));
    QObject::connect(ui->DocOuvert,SIGNAL(visibilityChanged(bool)),this,SLOT(triggerDocs(bool)));
    QObject::connect(ui->Compilation,SIGNAL(visibilityChanged(bool)),this,SLOT(triggerComp(bool)));
    QObject::connect(ui->Labels,SIGNAL(visibilityChanged(bool)),this,SLOT(triggerLabels(bool)));
    QObject::connect(ui->listWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(choose_sub_win(QListWidgetItem*)));
    QObject::connect(ui->actionFermer_le_projet,SIGNAL(triggered()),signalmapper,SLOT(map()));
    QObject::connect(signalmapper,SIGNAL(mapped(int)),this,SLOT(Fermerprojet(int)));
    signalmapper->setMapping(ui->actionFermer_le_projet,0);

    QObject::connect(ui->mdiArea,SIGNAL(subWindowActivated(QMdiSubWindow*)),this,SLOT(ChangerTitre(QMdiSubWindow*)));
}

void FenetrePrincipale::NouveauP(bool a)
{
    if(!a)
    {
        delete projet;
        return;
    }

    QStandardItem* item=new QStandardItem(projet->Get_projet());
    item->setFlags(item->flags()&~Qt::ItemIsEditable); //pour enlever l'édition du texte

    Projet* nouvP=new Projet(projet->Get_rep(),projet->Get_projet(),projet->Get_fin(),item);
    projets.push_back(nouvP);
    projetPrinc=nouvP;
    Editeur *editor=new Editeur(projet->Get_fichier()+projet->Get_fin(),projetPrinc->Get_dossier(),nouvP);
    QMdiSubWindow *win=ui->mdiArea->addSubWindow(editor,Qt::Tool);
    win->setWindowTitle(projet->Get_fichier()+projet->Get_fin());
    win->setVisible(true);
    QObject::connect(editor,SIGNAL(Fermer(Editeur*)),this,SLOT(close_sub_win(Editeur*)));
    QObject::connect(editor,SIGNAL(Change(QString,bool)),this,SLOT(toggle_asterix(QString,bool)));
    ui->listWidget->addItem(projet->Get_fichier()+projet->Get_fin());

    treeview->appendRow(nouvP->addFichier(editor));

    Modifyfont();

    delete projet;
}

FenetrePrincipale::~FenetrePrincipale()
{
    delete ui;
    delete treeview;
    delete signalmapper;
    for(QList<Projet*>::iterator it=projets.begin();it!=projets.end();++it)
        delete *it;
}

void FenetrePrincipale::NouveauF(bool a)
{ 
    if(a&&projetPrinc)
    {
        Editeur *e=new Editeur(fichier->Get_fichier()+projetPrinc->Get_fin(),projetPrinc->Get_dossier(),projetPrinc);
        QMdiSubWindow *c=ui->mdiArea->addSubWindow(e,Qt::Tool);
        c->setWindowTitle(fichier->Get_fichier()+projetPrinc->Get_fin());
        c->setVisible(true);
        QObject::connect(e,SIGNAL(Fermer(Editeur*)),this,SLOT(close_sub_win(Editeur*)));
        QObject::connect(e,SIGNAL(Change(QString,bool)),this,SLOT(toggle_asterix(QString,bool)));
        ui->listWidget->addItem(fichier->Get_fichier()+projetPrinc->Get_fin());
        projetPrinc->addFichier(e);
        Modifyfont();
    }else if(a)
    {
        Editeur *e=new Editeur(fichier->Get_fichier()+fichier->Get_fin(),fichier->Get_dossier(),0);
        QMdiSubWindow* c=ui->mdiArea->addSubWindow(e,Qt::Tool);
        c->setWindowTitle(fichier->Get_fichier()+fichier->Get_fin());
        c->setVisible(true);
        QObject::connect(e,SIGNAL(Fermer(Editeur*)),this,SLOT(close_sub_win(Editeur*)));
        QObject::connect(e,SIGNAL(Change(QString,bool)),this,SLOT(toggle_asterix(QString,bool)));
        ui->listWidget->addItem(fichier->Get_fichier()+fichier->Get_fin());
        e->setHigh();
    }
    delete fichier;
}

void FenetrePrincipale::on_actionOuvrir_triggered()
{
    QString b=QFileDialog::getOpenFileName(this,tr("Projet à ouvrir"),"/home",tr("Projet (*.proj);;Asm (*.dasm *.dcpu16)"));
    if(b.endsWith(".dasm")||b.endsWith(".dcpu16"))
    {
        QString c=b;
        int i=0;
        for(QString::iterator it=c.end();it!=c.begin();--it)
        {
            i++;
            if(*it=='/'||*it=='\\')
            {
                i-=2;
                c.remove(0,c.length()-i);
                break;
            }
        }
        Editeur *e=new Editeur(b,0);
        QMdiSubWindow* f=ui->mdiArea->addSubWindow(e,Qt::Tool);
        f->setWindowTitle(c);
        f->setVisible(true);
        QObject::connect(e,SIGNAL(Fermer(Editeur*)),this,SLOT(close_sub_win(Editeur*)));
        QObject::connect(e,SIGNAL(Change(QString,bool)),this,SLOT(toggle_asterix(QString,bool)));
        ui->listWidget->addItem(c);
        return;
    }
    QStandardItem *c=new QStandardItem();
    Projet* a=new Projet(b,c,this);
    if(!a->Get_ok())
    {
        delete c;
        delete a;
        return;
    }
    projets.push_back(a);
    projetPrinc=a;
    treeview->appendRow(a->getprojet());
    Modifyfont();
}

void FenetrePrincipale::close_sub_win(Editeur* a)
{
    QString c=a->Get_nom();
    c.push_back("*");
    QList<QListWidgetItem*> b=ui->listWidget->findItems(a->Get_nom(),Qt::MatchExactly);
    if(!b.count())
    {
        b=ui->listWidget->findItems(c,Qt::MatchExactly);
        if(b.count())
        {
            int result=QMessageBox::question(this,tr("Fichier modifié"),tr("Voulez vous sauvegarder \"%1\" ?").arg(a->Get_nom())
                                             ,QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
            if(result==QMessageBox::Yes)
                    a->sauvegarder();
            else if(result==QMessageBox::Cancel)
                return;
            a->reset();
        }
    }
    delete ui->listWidget->takeItem(0);
    QList<QMdiSubWindow*> tmp=ui->mdiArea->subWindowList();
    QMdiSubWindow* tmp2=0;
    for(QList<QMdiSubWindow*>::iterator it=tmp.begin();it!=tmp.end();++it)
        if((*it)->windowTitle()==a->Get_nom())
        {
            tmp2=*it;
            break;
        }
    ui->mdiArea->removeSubWindow(a);
    if(tmp2)
        tmp2->deleteLater();
}

void FenetrePrincipale::choose_sub_win(QListWidgetItem *a)
{
    QList<QMdiSubWindow*> b=ui->mdiArea->subWindowList();
    for(QList<QMdiSubWindow*>::iterator it=b.begin();it!=b.end();++it)
        if((*it)->windowTitle()==a->text())
        {
            ui->mdiArea->setActiveSubWindow(*it);
            break;
        }
}

void FenetrePrincipale::on_treeView_doubleClicked(QModelIndex a)
{
    if(ui->listWidget->findItems(treeview->itemFromIndex(a)->text(),Qt::MatchExactly).count())
    {
        QList<QMdiSubWindow*> b=ui->mdiArea->subWindowList();
        for(QList<QMdiSubWindow*>::iterator it=b.begin();it!=b.end();++it)
            if((*it)->windowTitle()==treeview->itemFromIndex(a)->text())
            {
                ui->mdiArea->setActiveSubWindow(*it);
                break;
            }
        return;
    }else if(!treeview->parent(a).isValid())
    {
        for(QList<Projet*>::iterator it=projets.begin();it!=projets.end();++it)
            if((*it)->getprojet()==treeview->itemFromIndex(a))
            {
                projetPrinc=*it;
                Modifyfont();
                break;
            }
    }

    QStandardItem* b=treeview->itemFromIndex(treeview->parent(a));
    for(QList<Projet*>::iterator it=projets.begin();it!=projets.end();++it)
        if((*it)->getprojet()==b)
        {
            Editeur *e=(*it)->getFichier(treeview->itemFromIndex(a));
            QMdiSubWindow *c=ui->mdiArea->addSubWindow(e,Qt::Tool);
            c->setWindowTitle(e->Get_nom());
            c->setVisible(true);
            ui->listWidget->addItem(e->Get_nom());
            break;
        }
}
