#include "filesupport.h"
#include <map>
#include <utility>
#include <QDebug>

FileSupport::FileSupport()
{
    /*initialize the valid_files_map with all supported file types*/
    valid_files_map.insert(std::pair<QString, bool>("jpg", true));
    valid_files_map.insert(std::pair<QString, bool>("jpeg", true));
    valid_files_map.insert(std::pair<QString, bool>("JPG", true));
    valid_files_map.insert(std::pair<QString, bool>("JPEG", true));
    valid_files_map.insert(std::pair<QString, bool>("bmp", true));
    valid_files_map.insert(std::pair<QString, bool>("BMP", true));
    valid_files_map.insert(std::pair<QString, bool>("gif", true));
    valid_files_map.insert(std::pair<QString, bool>("GIF", true));
    valid_files_map.insert(std::pair<QString, bool>("png", true));
    valid_files_map.insert(std::pair<QString, bool>("PNG", true));
    supp_file_iterator = valid_files_map.begin();
}

bool FileSupport::isSupported(QString filetype)
{
    SFI iterator;
    iterator = valid_files_map.find(filetype);
    if(iterator != valid_files_map.end())
    {
        return iterator->second;
    }
    else
    {
        return false;
    }
}
