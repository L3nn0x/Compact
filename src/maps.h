#ifndef MAPS_H
#define MAPS_H

#include <QMap>
#include <string>

class maps{
public:
    static QMap<std::string,int> init_mapN();
    static QMap<std::string,int> init_mapS();
    static QMap<std::string,int> init_mapR();
    static const QMap<std::string,int> _map_normal;
    static const QMap<std::string,int> _map_special;
    static const QMap<std::string,int> _map_regs;
};

#endif // MAPS_H
