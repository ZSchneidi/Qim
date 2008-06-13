#ifndef FILESUPPORT_H
#define FILESUPPORT_H

#include <QString>
#include <QMap>

#include "core/confighandler.h"

class ConfigHandler;

/*
 *FileSupport class provides information
 *of supported image file types as well as
 *methods to determine wether an specific
 *file type is supported or not
 */
class FileSupport : public QObject
{
    Q_OBJECT
    /*
     *QMap container which provides the information whether
     *a file is valid or not.
     */
    QMap<QString,bool> *valid_files_map;
    QMap<QString,bool>::iterator *supp_file_iterator;

    ConfigHandler *config_handler;

    void initFileSuppMap(QString formats);

public slots:

    void onSupportedFormatsChanged(QString format);

public:

    FileSupport(ConfigHandler *config_handler);

    bool isSupported(QString filetype);
    bool isFileSupported(QString filename);



};

#endif // FILESUPPORT_H
