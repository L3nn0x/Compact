#include "maps.h"
QMap<std::string,int> maps::init_mapN()
{
    QMap<std::string,int> map_normal;
    map_normal["set"]=1;
        map_normal["add"]=2;
        map_normal["sub"]=3;
        map_normal["mul"]=4;
        map_normal["mil"]=5;
        map_normal["dvi"]=6;
        map_normal["dvi"]=7;
        map_normal["mod"]=8;
        map_normal["mdi"]=9;
        map_normal["and"]=0xA;
        map_normal["bor"]=0xB;
        map_normal["xor"]=0xC;
        map_normal["shr"]=0xD;
        map_normal["asr"]=0xE;
        map_normal["shl"]=0xF;
        map_normal["ifb"]=0x10;
        map_normal["ifc"]=0x11;
        map_normal["ife"]=0x12;
        map_normal["ifn"]=0x13;
        map_normal["ifg"]=0x14;
        map_normal["ifa"]=0x15;
        map_normal["ifl"]=0x16;
        map_normal["ifu"]=0x17;
        map_normal["adx"]=0x1A;
        map_normal["sbx"]=0x1B;
        map_normal["sti"]=0x1E;
        map_normal["std"]=0x1F;
        return map_normal;
}

QMap<std::string,int> maps::init_mapS()
{
    QMap<std::string,int> map_special;
        map_special["jsr"]=1;
        map_special["int"]=8;
        map_special["iag"]=9;
        map_special["ias"]=0xA;
        map_special["rfi"]=0xB;
        map_special["iaq"]=0xC;
        map_special["hwn"]=0x10;
        map_special["hwq"]=0x11;
        map_special["hwi"]=0x12;
        return map_special;
}

QMap<std::string,int> maps::init_mapR()
{
    QMap<std::string,int> map_regs;
    map_regs["a"]=0;
    map_regs["b"]=1;
    map_regs["c"]=2;
    map_regs["x"]=3;
    map_regs["y"]=4;
    map_regs["z"]=5;
    map_regs["i"]=6;
    map_regs["j"]=7;
    map_regs["push"]=0x18;
    map_regs["pop"]=0x18;
    map_regs["peek"]=0x19;
    map_regs["pick"]=0x1A;
    map_regs["sp"]=0x1B;
    map_regs["pc"]=0x1C;
    map_regs["ex"]=0x1D;
    return map_regs;
}

const QMap<std::string,int> maps::_map_normal=maps::init_mapN();
const QMap<std::string,int> maps::_map_special=maps::init_mapS();
const QMap<std::string,int> maps::_map_regs=maps::init_mapR();
