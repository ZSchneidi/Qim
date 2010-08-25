#include "filesupport.h"
#include <map>
#include <utility>
#include <QDebug>

FileSupport::FileSupport()
{
    /*initialize the valid_files_map with all supported file types*/
    this->valid_files_map.insert(std::pair<QString, bool>("jpg", true));
    this->valid_files_map.insert(std::pair<QString, bool>("jpeg", true));
    this->valid_files_map.insert(std::pair<QString, bool>("JPG", true));
    this->valid_files_map.insert(std::pair<QString, bool>("JPEG", true));
    this->valid_files_map.insert(std::pair<QString, bool>("bmp", true));
    this->valid_files_map.insert(std::pair<QString, bool>("BMP", true));
    this->valid_files_map.insert(std::pair<QString, bool>("gif", true));
    this->valid_files_map.insert(std::pair<QString, bool>("GIF", true));
    this->valid_files_map.insert(std::pair<QString, bool>("png", true));
    this->valid_files_map.insert(std::pair<QString, bool>("PNG", true));
    this->supp_file_iterator = this->valid_files_map.begin();
}

bool FileSupport::isSupported(QString filetype)
{
    SFI iterator;
    iterator = this->valid_files_map.find(filetype);
    if(iterator != this->valid_files_map.end())
    {
        return iterator->second;
    }
    return false;
}
