#ifndef COMPILO_H_INCLUDED
#define COMPILO_H_INCLUDED

#include <iostream>
#include <boost/tokenizer.hpp>
#include <fstream>
#include <cctype>
#include <sstream>
#include <iostream>
#include "verif.h"

//mettre en minuscule
struct my_tolower
{
    char operator()(char c) const
    {
        return std::tolower(static_cast<unsigned char>(c));
    }
};

struct sentence{
int nbmots; //nombre de mots en hexa
bool islabel; //la ligne est un label
bool dat; //la ligne est un dat
std::string before; //la ligne non coupee
std::vector<std::string> coupe; //la ligne coupee
std::vector<int> hex; //la traduction hexa de la ligne
std::string label; //le label de la ligne
sentence *next; //la prochaine ligne
};

//juste par flemme de tout reecrire
typedef boost::tokenizer<boost::char_separator<char> > c_tok;

//classe principale du compilateur
class C
{
    public:
        C(std::string="no file");
        ~C();

        //fonction principale. Verifie le programme puis le compile
        void compilation(const std::string&,const std::string&);

        std::string compilation(const std::string&);

        //cherche les labels
        void labels();

        //deplace les labels pour une optimisation maximum
        void deplaceLabels();

        //lecture du fichier
        void lectureF(const std::string&);
        //coupe les phrases en mots
        void couper();
        //transforme les mots en code hexa
        void compiler();
        //recolle les codes hexa pour en faire un seul string
        void recoller();
        //ecrire dans un fichier le resultat
        void ecrireF(const std::string&);

        std::string _codeH;
        QMap<std::string,int> _map_labels;

    protected:
        QMap<std::string,std::string> _map_conf;

    private:
        struct sentence* _phrases;

        void opcode_normal(struct sentence*);
        void opcode_special(struct sentence*);
        int adresse(std::vector<std::string>&,int*,bool second);
        int nombre(std::string &it);
        int getlabel(int);
};
#endif // COMPILO_H_INCLUDED


// !fonction ->appel de fonction
//si . -> relatif
