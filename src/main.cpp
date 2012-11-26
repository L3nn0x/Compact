#include <QtGui/QApplication>
#include "fenetreprincipale.h"
#include <QTranslator>
#include <QLibraryInfo>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QString locale = QLocale::system().name().section('_', 0, 0);

    QTranslator translator;
    translator.load(QString("Compact_") + locale);
    app.installTranslator(&translator);

    QTranslator translator2;
    translator2.load(QString("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&translator2);
    
    FenetrePrincipale fenetre;
    fenetre.show();

    return app.exec();
}
