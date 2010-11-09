#include "imagedataentry.h"

ImageDataEntry::ImageDataEntry(FileInfoContainer file_info)
{

    this->m_name = file_info.name;
    this->m_path = file_info.path;
    this->m_width = file_info.width;
    this->m_height = file_info.height;
    this->m_ydpi = file_info.ydpi;
    this->m_xdpi = file_info.xdpi;
    this->m_size_str = file_info.size_str;
    this->m_size = file_info.size;
    this->m_depth = file_info.depth;

}

