#-------------------------------------------------
#
# Project created by Yamakaky !
#
#-------------------------------------------------

# Configurations diverses
#CONFIG *= warn_off              # Le compilateur génère un minimum de warning
CONFIG *= debug                 # App plus lourde, infos de débug. À modifier en
                                # release, ou qmake -config release
TARGET = "Compact"              # Nom de l'app
VERSION = 0.1

#ICON = path_to_icon   ###### TODO #######

macx {
QMAKE_INFO_PLIST = ressources/Info.plist
}


# Génération des options du compilateur
#COMPIL_VARS = -std=gnu++0x

#macx {
#COMPIL_VARS *= -stdlib=libc++
#}

QMAKE_CXXFLAGS *= $$COMPIL_VARS
QMAKE_CFLAGS *= $$COMPIL_VARS
QMAKE_LFLAGS *= $$COMPIL_VARS


DESTDIR = ./bin/                # Emplacement du binaire final
OBJECTS_DIR = ./tmp/o/          # Emplacement des fichiers .o
MOC_DIR = ./tmp/moc/            # Emplacement des fichiers .moc
UI_DIR = ./tmp/ui/              # Emplacement des fichiers ui

include(sources.pro)

SOURCES += \
    src/maps.cpp
