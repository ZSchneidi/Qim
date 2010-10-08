#include <QtGui/QApplication>
#include "core/coreengine.h"
#include <QTranslator>
#include <QLocale>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*implementation of the Qt translation*/
        //QTranslator translator;
    /*
    the "qim_lang_de_DE.qm" is the binary source for all string in
    the app which should be translated. Take a look at the ascii version of the
    translation file in src/theme/lang/qim_lang_de_DE.ts

    with system().name() the application detects the language code for the currently
    running machine the german code is "de_DE"
    */
        //QString transfile = QString ("theme/lang/qim_lang_%1").arg(QLocale::system().name());
        //translator.load(transfile, a.applicationDirPath());
    /*
    the QApplication has to initialize the language by calling installTranslator()
    comment out the a.installTranslator() line to see what happens without translation
    the app appears in the default english language.
    */
        //a.installTranslator(&translator);
    /*
    after initializing the language instatiate the Core object and show
    this is only a first test of the internationalization function.
    */
    CoreEngine w;
    //w.show();

    return a.exec();

}
