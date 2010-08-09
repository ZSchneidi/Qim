#include "imagedatamodel.h"

ImageDataModel::ImageDataModel(FileInfoContainer file_info)
{

    this->m_name = file_info.name;
    this->m_path = file_info.path;

}

