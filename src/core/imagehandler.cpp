#include "imagehandler.h"
#include "core/coreengine.h"

#include <QDebug>
#include <QMessageBox>

/*The image handler is declared in namespace Core*/

ImageHandler::ImageHandler()
{
    isSetPreImage = false;
    isSetCurImage = false;
    isSetPosImage = false;
    isSetDir = false;

    cur_file_iterator = 0;
    first_file_iterator = 0;
    last_file_iterator = 0;
    cur_file_index = 0;

    file_support_handler = new FileSupport();
}

void ImageHandler::setPreImage()
{

}

/*initialize the cur_image QImage with the file which was
 *load via open() or drag&drop
 */
void ImageHandler::loadImage(const QString cur_file_path)
{
    bool dir_load = false;
    if(isSetCurImage)
    {
        cur_image->~QImage();
        isSetCurImage = false;
    }
    cur_image = new QImage(cur_file_path);
    isSetCurImage = true;
    parseFolderPath(cur_file_path);
    /*check if the directory is loaded of not*/
    dir_load = loadImageFolder(cur_folder_path);
    initFileList(file_info_list);
    cur_file_iterator = getFileListPosOf(cur_file_name, file_info_list);

}

void ImageHandler::setPostImage()
{

}

/*
 *initialize the cur_image with the
 *next possible image in the QFileInfoList
 *returns false if there is is no other image in the list
 *returns true if next image was loaded
 */
bool ImageHandler::loadNextImage()
{
    /*if the file iterator doesn't already refer the last file*/
    if(cur_file_iterator >= first_file_iterator && cur_file_iterator < last_file_iterator )
    {
        cur_file_index++;
        /*get the path of the next file in the list*/
        cur_file_name = getFilePathFromList(++cur_file_iterator,file_info_list);
        qDebug() << "new file: " << cur_file_name;
        if((*cur_file_iterator).isFile())
        {
            *cur_image = QImage(cur_file_name);
        }
    }
    else
    {
        return false;
    }
    return true;
}

/*
 *initialize the cur_image with the
 *previous image in the QFileInfoList if the first image isn't load
 *returns false if there is is no other image in the list
 *returns true if next image was loaded
 */
bool ImageHandler::loadPrevImage()
{
    /*if the file iterator doesn't already refer the last file*/
    if(cur_file_iterator > first_file_iterator && cur_file_iterator <= last_file_iterator)
    {
        cur_file_index--;
        /*get the path of the next file in the list*/
        cur_file_name = getFilePathFromList(--cur_file_iterator,file_info_list);
        if((*cur_file_iterator).isFile())
        {
            *cur_image = QImage(cur_file_name);
        }
    }
    else
    {
        return false;
    }
    return true;
}

/*Scales the cur_image to the size of with and height*/
void ImageHandler::scaleImage(int width, int height)
{

    *cur_image = cur_image->scaled(width,height,Qt::KeepAspectRatio,Qt::SmoothTransformation);
}

/*
 *initially load the directory to cur_img_folder whenever an image was load the first time
 *if the cur_img_folder is already set or if something went wrong the method return false
 */
bool ImageHandler::loadImageFolder(QString path)
{
    if(!isSetDir)
    {
        cur_img_folder = QDir(path);
        isSetDir = true;
        return true;
    }
    else
        return false;

}

/*parse the path of the folder which contains the currently loaded image file*/
void ImageHandler::parseFolderPath(QString cur_file_path)
{
    int lindex = cur_file_path.lastIndexOf("/");
    cur_file_name = cur_file_path;
    /*parse the name of the currentlly loaded image out of the path*/
    cur_file_name = cur_file_name.remove(0,++lindex);
    /*set the path to the directory which contains the currently loaded image*/
    cur_folder_path = cur_file_path.remove(cur_file_name);

}

void ImageHandler::initFileList(QFileInfoList &list)
{
    list = cur_img_folder.entryInfoList();
    QFileInfoList::Iterator temp_it = list.begin();
    while(temp_it != list.end())
    {
        if((*temp_it).isDir())
        {
            temp_it = list.erase(temp_it);
        }
        else
        {
            if(!file_support_handler->isSupported((*temp_it).completeSuffix()))
            {
                temp_it = list.erase(temp_it);
                if(temp_it == list.end())
                {
                    break;
                }
            }
            else
                temp_it++;
        }
    }
    initFileIterator(list);
}

/*initialize the interator for the first and the last image in the file list*/
void ImageHandler::initFileIterator(QFileInfoList &list)
{
    bool is_set_first = false;
    QFileInfoList::Iterator temp_it = list.begin();

    while(temp_it != list.end())
    {
        qDebug() << "file- " << (*temp_it).fileName();
        if( (*temp_it).isFile() )
        {
            if(!is_set_first)
            {
                first_file_iterator = temp_it;
                is_set_first = true;
            }
            temp_it++;
        }
        else
            temp_it++;
    }
    last_file_iterator = --temp_it;

}
/*Returns an iterator to the position of a File in the file list. */
QFileInfoList::Iterator ImageHandler::getFileListPosOf(const QString &filename, QFileInfoList &list)
{
    cur_file_index = 0;
    QFileInfoList::Iterator temp_it = list.begin();
    while(temp_it != list.end())
    {
        /*int representation of the iterator*/
        cur_file_index++;
        if( (*temp_it).isFile() )
        {
            if( (*temp_it).fileName() == filename )
            {
                return temp_it;
            }
        }
        temp_it++;
    }
    return temp_it;
}

/*Returns a QString which holds the */
QString ImageHandler::getFilePathFromList(const QFileInfoList::Iterator position, QFileInfoList &list)
{
    QFileInfoList::Iterator temp_it = list.begin();
    while(temp_it < position && temp_it != list.end())
    {
        temp_it++;
    }
    return (*temp_it).filePath();
}
