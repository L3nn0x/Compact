#include "fenetreprincipale.h"
#include "ui_fenetreprincipale.h"

void FenetrePrincipale::on_actionNouveau_projet_triggered()
{
    projet=new NouveauProjet(this);
    QObject::connect(projet,SIGNAL(Get_ok(bool)),this,SLOT(NouveauP(bool)));
    projet->show();
}

void FenetrePrincipale::on_actionFichiers_dans_le_projet_triggered(bool a)
{
    ui->Arbre->setVisible(a);
}

void FenetrePrincipale::triggerArbre(bool a)
{
    ui->actionFichiers_dans_le_projet->setChecked(a);
}

void FenetrePrincipale::on_actionFichiers_ouverts_triggered(bool a)
{
    ui->DocOuvert->setVisible(a);
}

void FenetrePrincipale::triggerDocs(bool a)
{
    ui->actionFichiers_ouverts->setChecked(a);
}

void FenetrePrincipale::on_actionR_sultats_de_compilation_triggered(bool a)
{
    ui->Compilation->setVisible(a);
}

void FenetrePrincipale::triggerComp(bool a)
{
    ui->actionR_sultats_de_compilation->setChecked(a);
}

void FenetrePrincipale::on_actionLabels_triggered(bool a)
{
    ui->Labels->setVisible(a);
}

void FenetrePrincipale::triggerLabels(bool a)
{
    ui->actionLabels->setChecked(a);
}

void FenetrePrincipale::on_actionAfficher_sous_forme_d_onglets_triggered(bool a)
{
    if(a)
        ui->mdiArea->setViewMode(QMdiArea::TabbedView);
    else
        ui->mdiArea->setViewMode(QMdiArea::SubWindowView);
}

void FenetrePrincipale::on_actionAfficher_en_cascade_triggered()
{
    ui->actionAfficher_sous_forme_d_onglets->setChecked(false);
    ui->mdiArea->setViewMode(QMdiArea::SubWindowView);
    ui->mdiArea->cascadeSubWindows();
}

void FenetrePrincipale::on_actionAfficher_tout_en_m_me_temp_triggered()
{
    ui->actionAfficher_sous_forme_d_onglets->setChecked(false);
    ui->mdiArea->setViewMode(QMdiArea::SubWindowView);
    ui->mdiArea->tileSubWindows();
}

void FenetrePrincipale::on_actionNouveau_fichier_triggered()
{
    if(!projetPrinc)
        fichier=new NouveauFichier(this,false);
    else
        fichier=new NouveauFichier(this);
    QObject::connect(fichier,SIGNAL(Get_ok(bool)),this,SLOT(NouveauF(bool)));
    fichier->show();
}

void FenetrePrincipale::Modifyfont()
{
    QFont font;
    for(QList<Projet*>::iterator it=projets.begin();it!=projets.end();++it)
        (*it)->getprojet()->setFont(font);
    font.setBold(true);
    projetPrinc->getprojet()->setFont(font);

    ui->treeView->collapseAll();
    ui->treeView->expand(treeview->indexFromItem(projetPrinc->getprojet()));
}

void FenetrePrincipale::ChangerTitre(QMdiSubWindow *a)
{
    setWindowTitle((a&&!a->isFullScreen())?a->windowTitle()+" - Compact":"IDE Compact");
}

void FenetrePrincipale::toggle_asterix(QString a,bool b)
{
    QString e=a;
    e.push_back("*");
    QList<QMdiSubWindow*> c=ui->mdiArea->subWindowList();
    for(QList<QMdiSubWindow*>::iterator it=c.begin();it!=c.end();++it)
        if((*it)->windowTitle()==a||(*it)->windowTitle()==e)
        {
            (*it)->setWindowTitle(a+(b?"*":""));
            break;
        }
    QList<QListWidgetItem*> d=ui->listWidget->findItems(a,Qt::MatchExactly);
    if(d.count())
        d[0]->setText(a+(b?"*":""));
    else
    {
        d=ui->listWidget->findItems(e,Qt::MatchExactly);
        if(d.count())
            d[0]->setText(a+(b?"*":""));
    }
}

void FenetrePrincipale::on_actionEnregistrer_triggered()
{
    QMdiSubWindow* win=ui->mdiArea->activeSubWindow();
    if(!win)
        return;
    Editeur* a=(Editeur*)win->widget();
    QString tmp=a->Get_nom();
    tmp.push_back("*");

    QList<QListWidgetItem*> b=ui->listWidget->findItems(tmp,Qt::MatchExactly);

    if(b.count())
    {
        int result=QMessageBox::question(this,tr("Fichier modifi�"),tr("Voulez vous sauvegarder \"%1\" ?").arg(a->Get_nom())
                                     ,QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
        if(result==QMessageBox::Yes)
            a->sauvegarder();
        else if(result==QMessageBox::Cancel)
            return;
        b[0]->setText(b[0]->text().remove(QChar('*')));
        win->setWindowTitle(win->windowTitle().remove(QChar('*')));
    }
}


void FenetrePrincipale::on_actionTout_enregistrer_triggered()
{
    QList<QListWidgetItem*> a=ui->listWidget->findItems("*",Qt::MatchContains);
    if(!a.count())
        return;
    sauver=new Sauver(a,0,this);
    sauver->show();
    QObject::connect(sauver,SIGNAL(ok(int)),this,SLOT(Sauver_return(int)));
}

void FenetrePrincipale::closeEvent(QCloseEvent *b)
{
    if(end||!ui->listWidget->findItems("*",Qt::MatchContains).count())
    {
        b->accept();
        return;
    }
    QList<QListWidgetItem*> a=ui->listWidget->findItems("*",Qt::MatchContains);
    sauver=new Sauver(a,true,this);
    sauver->show();
    QObject::connect(sauver,SIGNAL(ok(int)),this,SLOT(Sauver_return(int)));
    b->ignore();
}

void FenetrePrincipale::Sauver_return(int b)
{
    end=true;
    bool x=sauver->Get_signal();
    sauver->close();
    if((!b||b==-1)&&!x)
        return;
    else if(!b&&x)
    {
        this->close();
        return;
    }
    QList<QMdiSubWindow*> z=ui->mdiArea->subWindowList();
    for(QList<QMdiSubWindow*>::iterator it=z.begin();it!=z.end();++it)
        ((Editeur*)(*it)->widget())->sauvegarder();
    if(x)
    {
        this->close();
        return;
    }
}

void FenetrePrincipale::customContextMenu(QPoint a)
{
    QMenu* menu=new QMenu();
    menu->addAction(tr("Ajouter fichier(s)"),this,SLOT(AjouterFichier()));
    signalmapper->setMapping(menu->addAction(tr("Fermer projet"),signalmapper,SLOT(map())),1);
    menu->exec(QCursor::pos());
}

void FenetrePrincipale::AjouterFichier()
{
    QMessageBox::information(this,"Ajoutons un fichier","une boite de dialogue");
}

void FenetrePrincipale::Fermerprojet(int sender)
{
    QModelIndexList list=ui->treeView->selectionModel()->selectedIndexes();
    QString tmp="Pas de s�lection";
    if(list.count()&&sender==1)
    {
        tmp.clear();
        tmp=treeview->itemFromIndex(list[0])->text();
    }
    QMessageBox::information(this,tr("Fermer le projet"),tr("Projet en cours : %1\nProjet s�lectionn� : %2").arg(projetPrinc->Get_name())
                             .arg(tmp));
}

void FenetrePrincipale::on_actionCompiler_triggered()
{
    //on_actionTout_enregistrer_triggered();
    if(!projetPrinc)
    {
        QMessageBox::critical(this,tr("Erreur de compilation"),tr("Impossible de trouver le projet principal."));
        return;
    }
    QString hexa=projetPrinc->Compiler();
    bool ok=projetPrinc->compi_ok();
    QMap<QString,int> labels=projetPrinc->Get_labels();
    if(!ok)
    {
        ui->sortieCompilation->setTextFormat(Qt::RichText);
        ui->sortieCompilation->setText(tr("<font color=\"red\">La compilation a �chou�e.</font>"));
        return;
    }
    ui->sortieCompilation->setText(tr("La compilation a r�ussi !"));
    ui->liste_labels->clear();
    for(QMap<QString,int>::const_iterator it=labels.begin();it!=labels.end();++it)
    {
        QString tmp2;
        tmp2.setNum(it.value());
        QString tmp=it.key()+"\t"+tmp2;
        ui->liste_labels->addItem(tmp);
    }
}
