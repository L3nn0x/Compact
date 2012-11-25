#include <QtGui/QApplication>
#include "fenetreprincipale.h"
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator translator;
    translator.load(QString("Compact_") + locale);
    app.installTranslator(&translator);
    
    FenetrePrincipale fenetre;
    fenetre.show();

    return app.exec();
}
