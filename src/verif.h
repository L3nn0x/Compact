#ifndef VERIF_H_INCLUDED
#define VERIF_H_INCLUDED

#include <vector>

#include "maps.h"

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

//La classe de verification du programme
class verif
{
public:
    verif(struct sentence*);
    bool Get_ok()const{return ok;}

    std::vector<std::string> correction();
    bool verification();

protected:
    bool ok;

    std::vector<std::string> _code;

};

#endif // VERIF_H_INCLUDED
