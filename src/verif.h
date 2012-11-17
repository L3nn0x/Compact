#ifndef VERIF_H_INCLUDED
#define VERIF_H_INCLUDED

#include <QMap>
#include <QVector>
#include <QString>

QMap<QString,int> map_normal={{"set",1},{"add",2},{"sub",3},{"mul",4},
                              {"mil",5},{"dvi",6},{"dvi",7},{"mod",8},
                              {"mdi",9},{"and",0xA},{"bor",0xB},{"xor",0xC},
                              {"shr",0xD},{"asr",0xE},{"shl",0xF},{"ifb",0x10},
                              {"ifc",0x11},{"ife",0x12},{"ifn",0x13},
                              {"ifg",0x14},{"ifa",0x15},{"ifl",0x16},{"ifu",0x17},
                              {"adx",0x1A},{"sbx",0x1B},{"sti",0x1E},{"std",0x1F}};
QMap<QString,int> map_special={{"jsr",1},{"int",8},{"iag",9},{"ias",0xA},
                               {"rfi",0xB},{"iaq",0xC},{"hwn",10},{"hwq",11},
                               {"hwi",12}};
QMap<QString,int> map_regs={{"a",0},{"b",1},{"c",2},{"x",3},{"y",4},{"z",5},
                            {"i",6},{"j",7},{"push",0x18},{"pop",0x18},
                            {"peek",0x19},{"pick",0x1A},{"sp",0x1B},{"pc",0x1C},
                            {"ex",0x1D}};

//La classe de verification du programme
class verif
{
    public:
        verif();

        bool verification(); //La fonction principale de la verification
        QVector<QString> correction();

        QVector<QString> analyse(){return verification()?_code:correction();}

    protected:
        QVector<QString> _code;

        QMap<QString,QString> _map_conf;
};

#endif // VERIF_H_INCLUDED
