#-------------------------------------------------
#
# Project created by Yamakaky !
#
#-------------------------------------------------

# Configurations diverses
CONFIG *= warn_on               # Le compilateur génère un max de warning
CONFIG *= debug                 # App plus lourde, infos de débug. À modifier en
                                # release, ou qmake -config release
TARGET = "Mon super IDE"        # Nom de l'app
VERSION = 0.0.1

win32 {
RC_FILE = ressources/win_icon.rc
}

macx {
ICON = ressources/icone.icns
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

<<<<<<< HEAD
include(sources.pro)

SOURCES += \
    src/maps.cpp
=======


DEPENDPATH = src
INCLUDEPATH = src

HEADERS *= \
	compilo.h \
	editeur.h \
	fenetreprincipale.h \
	myhighlight.h \
	nouveaufichier.h \
	nouveauprojet.h \
	projet.h \
	sauver.h \
	verif.h
	
FORMS *= \
	fenetreprincipale.ui \
	nouveaufichier.ui \
	nouveauprojet.ui \
	sauver.ui
	
SOURCES *= \
	compilo.cpp \
	maps.cpp \
	editeur.cpp \
	fenetreprincipale.cpp \
	main.cpp \
	myhighlight.cpp \
	nouveaufichier.cpp \
	nouveauprojet.cpp \
	projet.cpp \
	sauver.cpp \
	slots.cpp \
	verif.cpp

OTHER_FILES *= \
	map_normal.txt \
	map_regs.txt \
	map_special.txt
>>>>>>> 115b1487774e6ff63378315b040a8710a8ca68a9