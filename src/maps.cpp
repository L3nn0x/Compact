#include "verif.h"

void init_maps()
{
    _map_normal["set"]=1;
    _map_normal["add"]=2;
    _map_normal["sub"]=3;
    _map_normal["mul"]=4;
    _map_normal["mil"]=5;
    _map_normal["dvi"]=6;
    _map_normal["dvi"]=7;
    _map_normal["mod"]=8;
    _map_normal["mdi"]=9;
    _map_normal["and"]=0xA;
    _map_normal["bor"]=0xB;
    _map_normal["xor"]=0xC;
    _map_normal["shr"]=0xD;
    _map_normal["asr"]=0xE;
    _map_normal["shl"]=0xF;
    _map_normal["ifb"]=0x10;
    _map_normal["ifc"]=0x11;
    _map_normal["ife"]=0x12;
    _map_normal["ifn"]=0x13;
    _map_normal["ifg"]=0x14;
    _map_normal["ifa"]=0x15;
    _map_normal["ifl"]=0x16;
    _map_normal["ifu"]=0x17;
    _map_normal["adx"]=0x1A;
    _map_normal["sbx"]=0x1B;
    _map_normal["sti"]=0x1E;
    _map_normal["std"]=0x1F;

    _map_special["jsr"]=1;
    _map_special["int"]=8;
    _map_special["iag"]=9;
    _map_special["ias"]=0xA;
    _map_special["rfi"]=0xB;
    _map_special["iaq"]=0xC;
    _map_special["hwn"]=0x10;
    _map_special["hwq"]=0x11;
    _map_special["hwi"]=0x12;

    _map_regs["a"]=0;
    _map_regs["b"]=1;
    _map_regs["c"]=2;
    _map_regs["x"]=3;
    _map_regs["y"]=4;
    _map_regs["z"]=5;
    _map_regs["i"]=6;
    _map_regs["j"]=7;
    _map_regs["push"]=0x18;
    _map_regs["pop"]=0x18;
    _map_regs["peek"]=0x19;
    _map_regs["pick"]=0x1A;
    _map_regs["sp"]=0x1B;
    _map_regs["pc"]=0x1C;
    _map_regs["ex"]=0x1D;
}
