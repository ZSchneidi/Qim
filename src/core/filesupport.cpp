#include "filesupport.h"
#include <map>
#include <utility>
#include <QDebug>

FileSupport::FileSupport(ConfigHandler *config_handler) : QObject()
{
    this->config_handler = config_handler;
    this->blacklisted_files_map = new QMap<QString,bool>;
    this->blacklisted_file_iterator = new QMap<QString,bool>::iterator;

    /*initialize the valid_files_map with all supported file types*/

    this->initFileBlacklistMap(this->config_handler->FileFormatBlacklistStr());


}

/**
  *used to load the supported file suffix in the valid_files_map
  */
void FileSupport::initFileBlacklistMap(QString formats)
{
    this->blacklisted_files_map->clear();
    QStringList temp = formats.split(",",QString::SkipEmptyParts);
    for (int i = 0; i < temp.size(); i++)
    {
        QString temp_str = temp.at(i);
        temp_str = temp_str.right((temp_str.length() - temp_str.lastIndexOf("."))-1);
        this->blacklisted_files_map->insert(temp_str,true);
    }
    //qDebug() << "supp: " << *this->blacklisted_files_map;
    *this->blacklisted_file_iterator = this->blacklisted_files_map->begin();
}

/**
  * this is a major priority function which is used to determine whether a file is supported
  * or not.
  * in the first step the suffix is used to determine if the file is wished to be loaded
  * if it is valid the file will be analysed to determine its actual file format via
  * QImageReader::imageFormat()
  */
bool FileSupport::isFileSupported(QString filename)
{
    QString parsed_suffix = filename.right((filename.length()-filename.lastIndexOf("."))-1);
    *this->blacklisted_file_iterator = this->blacklisted_files_map->find(parsed_suffix);
    if( *this->blacklisted_file_iterator == this->blacklisted_files_map->end())
    {
        /*if the file format is not blacklisted*/
        if(QImageReader::imageFormat(filename) != "")
            return true;
        else
            return false;
    }
    else
    {
        /*if the file format is blacklisted*/
        return false;
    }
}

void FileSupport::onBlacklistedFormatsChanged(QString format)
{
    this->initFileBlacklistMap(format);
}
