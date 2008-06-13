#include "filesupport.h"
#include <map>
#include <utility>
#include <QDebug>

FileSupport::FileSupport(ConfigHandler *config_handler) : QObject()
{
    this->config_handler = config_handler;
    this->valid_files_map = new QMap<QString,bool>;
    this->supp_file_iterator = new QMap<QString,bool>::iterator;

    /*initialize the valid_files_map with all supported file types*/

    this->initFileSuppMap(this->config_handler->FileFormatBlacklistStr());


}

/**
  *used to load the supported file suffix in the valid_files_map
  */
void FileSupport::initFileSuppMap(QString formats)
{
    QStringList temp = formats.split(",",QString::SkipEmptyParts);
    for (int i = 0; i < temp.size(); i++)
    {
        QString temp_str = temp.at(i);
        temp_str = temp_str.right((temp_str.length() - temp_str.lastIndexOf("."))-1);
        this->valid_files_map->insert(temp_str,true);
    }

    qDebug() << "supp: " << *this->valid_files_map;
    *this->supp_file_iterator = this->valid_files_map->begin();
}

/** this is a deprecated version of the support validation use the ifFileSupported() method to validate files*/
bool FileSupport::isSupported(QString filetype)
{

    *this->supp_file_iterator = this->valid_files_map->find(filetype);
    if(*this->supp_file_iterator == this->valid_files_map->end())
    {
        return this->supp_file_iterator->value();
    }
    return false;
}

/**
  * this is a major priority function which is used to determine whether a file is supported
  * or not.
  * in the first step the suffix is used to determine if the file is wished to be loaded
  * if it is the file will be analysed to determine its actual file format via magic number
  * recognition
  */
bool FileSupport::isFileSupported(QString filename)
{
    QString parsed_suffix = filename.right((filename.length()-filename.lastIndexOf("."))-1);
    qDebug() << "suffix " << parsed_suffix;
    *this->supp_file_iterator = this->valid_files_map->find(parsed_suffix);
    if( *this->supp_file_iterator == this->valid_files_map->end())
    {
        qDebug() << "file is ok";
    }
    else
    {
        qDebug() << "do not load this file";
    }



    return false;

}



void FileSupport::onSupportedFormatsChanged(QString format)
{
    this->initFileSuppMap(format);
}
