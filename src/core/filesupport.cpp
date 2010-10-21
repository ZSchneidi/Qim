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

    this->initFileSuppMap(this->config_handler->supFileFormatStr());


}

/*used to load the supported file suffix in the valid_files_map*/
void FileSupport::initFileSuppMap(QString formats)
{
    QStringList temp = formats.split(",",QString::SkipEmptyParts);
    for (int i = 0; i < temp.size(); i++)
    {
        QString temp_str = temp.at(i);
        if(temp_str.startsWith("."))
            temp_str = temp_str.remove(0,1);
        this->valid_files_map->insert(temp_str,true);
    }

    qDebug() << "supp: " << *this->valid_files_map;
    *this->supp_file_iterator = this->valid_files_map->begin();
}

bool FileSupport::isSupported(QString filetype)
{

    *this->supp_file_iterator = this->valid_files_map->find(filetype);
    if(*this->supp_file_iterator != this->valid_files_map->end())
    {
        return this->supp_file_iterator->value();
    }
    return false;
}

void FileSupport::onSupportedFormatsChanged(QString format)
{
    this->initFileSuppMap(format);
}
