#ifndef VERIF_H_INCLUDED
#define VERIF_H_INCLUDED

#include <QMap>
#include <vector>
#include <string>

static QMap<std::string,int> _map_normal;
static QMap<std::string,int> _map_special;
static QMap<std::string,int> _map_regs;

void init_maps();

//La classe de verification du programme
class verif
{
    public:
        verif(std::vector<std::string>&,QMap<std::string,std::string>&);

        bool verification(); //La fonction principale de la verification
        std::vector<std::string> correction();

        std::vector<std::string> analyse(){return verification()?_code:correction();}

    protected:
        std::vector<std::string> _code;

        QMap<std::string,std::string> _map_conf;
};

#endif // VERIF_H_INCLUDED
