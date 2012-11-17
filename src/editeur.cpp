#include "editeur.h"

Editeur::Editeur(QString name,void* proj,QWidget *parent) :
    QTextEdit(parent),nom(name),modified(false),fichier(name),projet(proj)
{
    setUndoRedoEnabled(true);
    int i=0;
    for(QString::iterator it=nom.end();it!=nom.begin();--it)
    {
        i++;
        if(*it=='/'||*it=='\\')
        {
            i-=2;
            nom.remove(0,nom.length()-i);
            break;
        }
    }
    QFile a(name);
    if(!a.open(QIODevice::ReadOnly))
        return;
    char *buff=new char[1024];
    QString b;
    while(!a.atEnd())
    {
        if(a.readLine(buff,1024*sizeof(char))==-1)
        {
            a.close();
            delete[] buff;
            return;
        }
        b+=QString(buff);
    }
    b.remove(QChar('\r'),Qt::CaseInsensitive);
    setPlainText(b);
    buffer=b;
    a.close();
    delete[] buff;

    QObject::connect(this,SIGNAL(textChanged()),this,SLOT(TChange()));
}

Editeur::Editeur(QString nom,QString dossier,void* proj,QWidget *parent) :
    QTextEdit(parent),nom(nom),modified(false),projet(proj)
{
    setUndoRedoEnabled(true);
    fichier=dossier+nom;
    QFile tmp(fichier);
    if(!tmp.exists())
    {
        tmp.open(QIODevice::ReadWrite);
        tmp.close();
    }
    QObject::connect(this,SIGNAL(textChanged()),this,SLOT(TChange()));
}

void Editeur::closeEvent(QCloseEvent *a)
{
    a->ignore();
    emit Fermer(this);
}

Editeur::~Editeur()
{
    delete high;
    projet=0;
}

void Editeur::TChange()
{
    toPlainText()==buffer?modified=false:modified=true;
    emit Change(nom,modified);
}

void Editeur::sauvegarder()
{
    QFile a(fichier);
    if(!a.open(QIODevice::WriteOnly|QIODevice::Truncate))
        return;
    QTextStream b(&a);
    b<<toPlainText();
    a.close();
    buffer=toPlainText();
}

void Editeur::reset()
{
    setPlainText(buffer);
}

void Editeur::setHigh(map &a, map &b, map &c)
{
    high=new MyHighlight(document(),a,b,c);
    high->rehighlight();
}
