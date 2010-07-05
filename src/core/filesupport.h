#ifndef FILESUPPORT_H
#define FILESUPPORT_H

#include <QString>
#include <map>

/*
 *FileSupport class provides information
 *of supported image file types as well as
 *method to determine wether an specific
 *file type is supported or not
 */
class FileSupport
{
    /*
     *map container which provides the information if
     *a file is valid or not.
     */
    typedef std::map<QString,bool> suppFile;
    suppFile valid_files_map;

    typedef suppFile::iterator SFI;
    SFI supp_file_iterator;

public:

    FileSupport();

    bool isSupported(QString filetype);

};

#endif // FILESUPPORT_H
