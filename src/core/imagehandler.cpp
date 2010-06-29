#include "imagehandler.h"
#include "core/coreengine.h"

#include <QDebug>

/*The image handler is declared in namespace Core*/

ImageHandler::ImageHandler()
{

    isSetPreImage = false;
    isSetCurImage = false;
    isSetPosImage = false;

}

void ImageHandler::setPreImage()
{

}

void ImageHandler::setCurrImage(QString filepath)
{

    if(isSetCurImage)
    {
        cur_image->~QImage();
        isSetCurImage = false;
    }
    cur_image = new QImage(filepath);
    isSetCurImage = true;
    parseFolderPath(filepath);
    loadImageFolder(cur_folder_path);

    initFileList();

}

void ImageHandler::setPostImage()
{

}

void ImageHandler::scaleImage(int width, int height)
{

    *cur_image = cur_image->scaled(width,height,Qt::KeepAspectRatio,Qt::SmoothTransformation);
}

void ImageHandler::loadImageFolder(QString path)
{
    /*initialize the current image folder*/
    cur_img_folder = QDir(path);

}

void ImageHandler::parseFolderPath(QString filepath)
{
    /*parse the path of the folder which contains the currently loaded image file*/
    int lindex = filepath.lastIndexOf("/");
    cur_file_name = filepath;
    cur_file_name = cur_file_name.remove(0,lindex);
    cur_folder_path = filepath.remove(cur_file_name);

}

void ImageHandler::initFileList()
{

    file_info_list = cur_img_folder.entryInfoList();
    file_iterator = file_info_list.begin();

    qDebug() << "iterate files!" ;
    while(file_iterator != file_info_list.end())
    {
        if( (*file_iterator).isFile() )
            {
            qDebug() << (*file_iterator).fileName() ;
            }
        ++file_iterator;
    }

}
