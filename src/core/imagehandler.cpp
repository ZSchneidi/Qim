#include "imagehandler.h"
#include "core/coreengine.h"
#include "fileinfohandler.h"
#include "fileinfothread.h"

#include <QDebug>
#include <QMessageBox>

/*The image handler is declared in namespace Core*/


ImageHandler::ImageHandler()
{
    this->isSetCurImage = false;
    this->isSetDir = false;
    this->cur_file_iterator = 0;
    this->first_file_iterator = 0;
    this->last_file_iterator = 0;
    this->cur_file_index = 0;
    this->file_support_handler = new FileSupport();
}

/*initialize the cur_image QImage with the file which was
 *load via open() or drag&drop
 */
void ImageHandler::loadImage(const QString cur_file_path)
{
    this->cur_image = new QImage(cur_file_path);
    this->isSetCurImage = true;
    this->parseFolderPath(cur_file_path);
    /*check if the directory is loaded of not*/
    this->isSetDir = this->loadImageFolder(this->cur_folder_path);
    /*initFileList() takes the file_info_list as reference for storing the informations*/
    this->initFileList(this->file_info_list);
    this->cur_file_iterator = this->getFileListPosOf(this->cur_file_name,this->file_info_list);
    /*store the path in the title_str*/
    this->title_str = cur_file_path;
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
    if(this->cur_file_iterator >= this->first_file_iterator &&
       this->cur_file_iterator < this->last_file_iterator )
    {
        this->cur_file_index++;
        /*get the path of the next file in the list*/
        this->cur_file_path = this->getFilePathFromList(++this->cur_file_iterator,
                                                        this->file_info_list);
        if((*cur_file_iterator).isFile())
        {
            *this->cur_image = QImage(this->cur_file_path);
            this->title_str = this->cur_file_path;
        }
        return true;
    }
    return false;
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
    if(this->cur_file_iterator > this->first_file_iterator &&
       this->cur_file_iterator <= this->last_file_iterator)
    {
        this->cur_file_index--;
        /*get the path of the next file in the list*/
        this->cur_file_path = this->getFilePathFromList(--this->cur_file_iterator,
                                                        this->file_info_list);
        if((*cur_file_iterator).isFile())
        {
            *this->cur_image = QImage(this->cur_file_path);
            this->title_str = this->cur_file_path;
        }
        return true;
    }
    return false;
}

/*Scales the cur_image to the size of with and height*/
void ImageHandler::scaleImage(int width, int height)
{
    *this->cur_image = this->cur_image->scaled(width,height,Qt::KeepAspectRatio,Qt::SmoothTransformation);
}

/*
 *initially load the directory to cur_img_folder whenever an image was load the first time
 *if the cur_img_folder is already set or if something went wrong the method return false
 */
bool ImageHandler::loadImageFolder(QString path)
{
    this->cur_img_folder = QDir(path);
qDebug() << this->cur_img_folder.dirName();
    return true;
}

/*parse the path of the folder which contains the currently loaded image file*/
void ImageHandler::parseFolderPath(QString cur_file_path)
{
    int lindex = cur_file_path.lastIndexOf("/");
    this->cur_file_name = cur_file_path;
    /*parse the name of the currentlly loaded image out of the path*/
    this->cur_file_name = this->cur_file_name.remove(0,++lindex);
    /*set the path to the directory which contains the currently loaded image*/
    this->cur_folder_path = cur_file_path.remove(this->cur_file_name);
}

void ImageHandler::initFileList(QFileInfoList &list)
{
    list = this->cur_img_folder.entryInfoList();
    QFileInfoList::Iterator temp_it = list.begin();
    while(temp_it != list.end())
    {
        if((*temp_it).isDir())
        {
            temp_it = list.erase(temp_it);
        }
        else
        {
            /*
             *check whether the file type suffix is supported
             *problems can occur if the path contains more than one "." in the path
             *this must be solved by parsing the suffix
             */
            bool check = this->file_support_handler->isSupported((*temp_it).suffix());
            if(!check)
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
    this->initFileIterator(list);
}

/*initialize the interator for the first and the last image in the file list*/
void ImageHandler::initFileIterator(QFileInfoList &list)
{
    bool is_set_first = false;
    QFileInfoList::Iterator temp_it = list.begin();
    while(temp_it != list.end())
    {
        if((*temp_it).isFile())
        {
            if(!is_set_first)
            {
                this->first_file_iterator = temp_it;
                is_set_first = true;
            }
            temp_it++;
        }
        else
            temp_it++;
    }
    this->last_file_iterator = --temp_it;
}

/*Returns an iterator to the position of a File in the file list. */
QFileInfoList::Iterator ImageHandler::getFileListPosOf(const QString &filename, QFileInfoList &list)
{
    this->cur_file_index = 0;
    QFileInfoList::Iterator temp_it = list.begin();
    while(temp_it != list.end())
    {
        /*int representation of the iterator*/
        this->cur_file_index++;
        if((*temp_it).isFile())
        {
            if((*temp_it).fileName() == filename)
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

void ImageHandler::initImageDataModel(QList<QObject *> &model)
{
    //qDebug() << "item count " << model.count();
    if(model.count() > 0)
    {
        model.clear();
    }
    QFileInfoList::Iterator temp_it = this->file_info_list.begin();
    while(temp_it != this->file_info_list.end())
    {
        if((*temp_it).isFile())
        {
            FileInfoContainer file_info;
            file_info.name = (*temp_it).fileName();
            file_info.path = (*temp_it).absoluteFilePath();
            /*file_info.width =
            file_info.height =
            file_info.depth =
            file_info.xdpi =
            file_info.ydpi = */
            file_info.size = (*temp_it).size();
            file_info.size_str = FileInfoHandler::getSizeStr((*temp_it).size());
            file_info.type = (*temp_it).suffix();

            model.append(new ImageDataModel(file_info));

        }
        temp_it++;
    }
}
