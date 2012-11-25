#include <QtGui/QApplication>
#include "fenetreprincipale.h"
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString locale = QLocale::system().name().section('_', 0, 0);

    QTranslator translator;
    QTranslator translator2;
    translator.load(QString("Compact_") + locale);
    translator2.load(QString("qt_")+locale);
    a.installTranslator(&translator2);
    a.installTranslator(&translator);
    FenetrePrincipale w;
    w.show();

    return a.exec();
}
