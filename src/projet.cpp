#include "projet.h"

Projet::Projet(QString rep,QString nom,QString fin,QStandardItem *item)
    :dossier(rep),name(nom),fin_fichier(fin),item(item),ok(true),compilo(new C)
{}

QStandardItem* Projet::addFichier(Editeur* a,bool open)
{
    a->setHigh(compilo->_map_normal,compilo->_map_special,compilo->_map_regs);
    fichiers.push_back(a);
    QStandardItem *h=new QStandardItem(a->Get_nom());
    h->setFlags(h->flags()&~Qt::ItemIsEditable);
    item->appendRow(h);

    QFile file(dossier+name+QString(".proj"));
    if(open)
        return item;
    if(file.exists())
    {
        if(!file.open(QIODevice::WriteOnly|QIODevice::Append))
            return item;
        QTextStream b(&file);
        b<<a->Get_nom()<<endl;
        file.close();
        return item;
    }else
    {
        if(!file.open(QIODevice::WriteOnly|QIODevice::Append))
            return item;
        QTextStream b(&file);
        b<<name<<endl<<fin_fichier<<endl<<a->Get_nom()<<endl;
        file.close();
        return item;
    }
}

QString Projet::Get_fin()const{return fin_fichier;}

Projet::~Projet()
{
    for(QList<Editeur*>::iterator it=fichiers.begin();it!=fichiers.end();++it)
        delete *it;
    delete compilo;
    item=0;
}

Projet::Projet(QString &a, QStandardItem *b,QMainWindow *z):item(b),ok(false),compilo(new C)
{
    dossier=a;
    int i=0;
    for(QString::iterator it=dossier.end();it!=dossier.begin();--it)
    {
        i++;
        if(*it=='/'||*it=='\\')
        {
            i-=2;
            dossier.chop(i);
            break;
        }
    }

    QFile c(a);
    if(!c.open(QIODevice::ReadOnly))
        return;
    char *buff=new char[1024];
    qint64 l=c.readLine(buff,1024*sizeof(char));
    if(l==-1)
    {
        c.close();
        delete[] buff;
        return;
    }

    //ici il faudra un parseur pour le xml
    name=QString(buff);
    name.remove(QChar('\r'),Qt::CaseInsensitive);
    name.remove(QChar('\n'),Qt::CaseInsensitive); //pour le \r et le \n
    b->setText(name);
    b->setFlags(b->flags()&~Qt::ItemIsEditable);
    l=c.readLine(buff,1024*sizeof(char));
    if(l==-1)
    {
        c.close();
        delete[] buff;
        return;
    }
    fin_fichier=QString(buff).remove(QChar('\n'),Qt::CaseInsensitive);
    fin_fichier.remove(QChar('\r'),Qt::CaseInsensitive);

    while(!c.atEnd())
    {
        l=c.readLine(buff,1024*sizeof(char));
        if(l==-1)
        {
            c.close();
            delete[] buff;
            return;
        }
        QString tmp=QString(buff);
        tmp.remove(QChar('\n'),Qt::CaseInsensitive);
        tmp.remove(QChar('\r'),Qt::CaseInsensitive);
        Editeur* editor=new Editeur(dossier+tmp,this);
        QObject::connect(editor,SIGNAL(Fermer(Editeur*)),z,SLOT(close_sub_win(Editeur*)));
        QObject::connect(editor,SIGNAL(Change(QString,bool)),z,SLOT(toggle_asterix(QString,bool)));
        addFichier(editor,true);
    }
    c.close();
    delete[] buff;
    ok=true;
}

Editeur* Projet::getFichier(QStandardItem *a)
{
    for(QList<Editeur*>::iterator it=fichiers.begin();it!=fichiers.end();++it)
        if((*it)->Get_nom()==a->text())
            return *it;
    return 0;
}
