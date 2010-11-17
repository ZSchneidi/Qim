#include <QtGui/QApplication>
#include "core/coreengine.h"
#include <QTranslator>
#include <QLocale>
#include <QDebug>

QStringList getArguments(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    QStringList argumetn_list;
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
    argumetn_list = getArguments(argc, argv);
    qDebug() << argumetn_list;
    if(argumetn_list.count() > 1)
    {
        w.openFromArgument(argumetn_list.at(1));
        //QMessageBox::warning(0,"debug",argumetn_list.at(1));
    }
    /*
    for(int i = 0; i < argumetn_list.count(); i++)
    {
        QMessageBox::warning(0,"debug",QString::number(i)+". "+(QString)"parameter " + argumetn_list.at(i));
    }
    */
    return a.exec();

}

QStringList getArguments(int argc, char *argv[])
{
    QStringList strlist;
    int i = 0;
    for (i = 0; i < argc; i++)
    {
        strlist.append((QString)argv[i]);
    }
    return strlist;
}

