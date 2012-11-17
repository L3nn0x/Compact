#ifndef COMPILO_H_INCLUDED
#define COMPILO_H_INCLUDED

#include <iostream>
#include <boost/tokenizer.hpp>
#include <fstream>
#include <cctype>
#include <sstream>
#include "verif.h"

struct sentence{
int nbmots; //nombre de mots en hexa
bool islabel; //la ligne est un label
QString before; //la ligne non coupee
QVector<QString> coupe; //la ligne coupee
QVector<int> hex; //la traduction hexa de la ligne
QString label; //le label de la ligne
sentence *next; //la prochaine ligne
};

//juste par flemme de tout reecrire
typedef boost::tokenizer<boost::char_separator<char> > c_tok;

//classe principale du compilateur
class C
{
    public:
        C(QString="no file");
        ~C();

        //fonction principale. Verifie le programme puis le compile
        void compilation(const QString&,const QString&);

        //cherche les labels
        void labels();

        //lecture du fichier
        void lectureF(const QString&);
        //coupe les phrases en mots
        void couper();
        //transforme les mots en code hexa
        void compiler();
        //recolle les codes hexa pour en faire un seul string
        void recoller();
        //ecrire dans un fichier le resultat
        void ecrireF(const QString&);

        QString _codeH;
        QMap<QString,int> _map_labels;

    protected:
        QMap<QString,QString> _map_conf;

    private:
        struct sentence* _phrases;

        void opcode_normal(struct sentence*);
        void opcode_special(struct sentence*);
        int adresse(QVector<QString>&,int*,bool second);
        int nombre(QString &it);
        int getlabel(int);
};
#endif // COMPILO_H_INCLUDED


// !fonction ->appel de fonction
//si . -> relatif
