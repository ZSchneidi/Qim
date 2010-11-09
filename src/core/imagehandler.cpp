#include "imagehandler.h"
#include "core/coreengine.h"
#include "fileinfohandler.h"
#include "fileinfothread.h"

#include <QDebug>
#include <QMessageBox>

/*The image handler is declared in namespace Core*/


ImageHandler::ImageHandler(CoreEngine *core)
{
    this->core = core;
    this->isSetCurImage = false;
    this->isSetDir = false;
    this->cur_file_iterator = 0;
    this->first_file_iterator = 0;
    this->last_file_iterator = 0;
    this->cur_file_index = 0;
    this->file_support_handler = new FileSupport(this->core->getConfigHandler());
}

/**
 *initialize the cur_image QImage with the file which was
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

/**
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
        /*get the path of the next file in the list*/
        this->cur_file_path = this->getFilePathFromList(++this->cur_file_iterator,
                                                        this->file_info_list);
        this->cur_file_index++;
        if((*cur_file_iterator).isFile())
        {
            /*the cur_image is temporary not needed becaus the image will be loaded in the qml engine*/
            //*this->cur_image = QImage(this->cur_file_path);
            this->title_str = this->cur_file_path;
        }
        return true;
    }
    return false;
}

/**
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
        /*get the path of the next file in the list*/
        this->cur_file_path = this->getFilePathFromList(--this->cur_file_iterator,
                                                        this->file_info_list);
        this->cur_file_index--;
        if((*cur_file_iterator).isFile())
        {
            /*the cur_image is temporary not needed becaus the image will be loaded in the qml engine*/
            //*this->cur_image = QImage(this->cur_file_path);
            this->title_str = this->cur_file_path;
        }
        return true;
    }
    return false;
}

/** Scales the cur_image to the size of with and height*/
void ImageHandler::scaleImage(int width, int height)
{
    /*the cur_image is temporary not needed becaus the image will be loaded in the qml engine*/
    //*this->cur_image = this->cur_image->scaled(width,height,Qt::KeepAspectRatio,Qt::SmoothTransformation);
}

/**
 *initially load the directory to cur_img_folder whenever an image was load the first time
 *if the cur_img_folder is already set or if something went wrong the method return false
 */
bool ImageHandler::loadImageFolder(QString path)
{
    this->cur_img_folder = QDir(path);
    return true;
}

/**
 *to obtain the path of the folder which contains the loaded image
 *this method isolates the image file name from the absolute path
 *whath remains is the path to the folder
 */
void ImageHandler::parseFolderPath(QString cur_file_path)
{
    int lindex = cur_file_path.lastIndexOf("/");
    this->cur_file_name = cur_file_path;
    /*parse the name of the currentlly loaded image out of the path*/
    this->cur_file_name = this->cur_file_name.remove(0,++lindex);
    /*set the path to the directory which contains the currently loaded image*/
    this->cur_folder_path = cur_file_path.remove(this->cur_file_name);
}
/**
 *in this step the list of QFileInfos will be cleaned from unnecessary data
 *all not supported files and subdirectories will be ereased from the list
 */
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
            if(!this->file_support_handler->isFileSupported((*temp_it).absoluteFilePath()))
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

/**
 *initialize the interator for the first and the last image in the file list
 *this is needed in a later state to determine whether the current iterator
 *is pointing on the first or the last file in the list
 */
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

/**
 *returns an iterator to the position of a File in the file list
 *this information is used to check where the current iterator points on
 *to check if the user can load a previous or a next image
 *what isn't possible if the user is already at the first or last position
 */
QFileInfoList::Iterator ImageHandler::getFileListPosOf(const QString &filename, QFileInfoList &list)
{
    this->cur_file_index = 0;
    QFileInfoList::Iterator temp_it = list.begin();
    while(temp_it != list.end())
    {
        if((*temp_it).isFile())
        {
            if((*temp_it).fileName() == filename)
            {
                return temp_it;
            }
        }
        /*int representation of the iterator*/
        this->cur_file_index++;
        temp_it++;
    }
    return temp_it;
}


QFileInfoList::Iterator ImageHandler::getFileListPosOfIndex(const int index, QFileInfoList &list)
{
    int i;
    QFileInfoList::Iterator temp_it = list.begin();
    for(i = 0; i < index ; i++)
    {
        temp_it++;
    }
    return temp_it;

}

/**
 *returns a QString which contains the absolute path to the file (list entry)
 *on which the iterator points
 */
QString ImageHandler::getFilePathFromList(const QFileInfoList::Iterator position, QFileInfoList &list)
{
    QFileInfoList::Iterator temp_it = list.begin();
    while(temp_it < position && temp_it != list.end())
    {
        temp_it++;
    }
    return (*temp_it).filePath();
}

/**
 *the ImageDataModel is used by the qml engine the picture list on the visual layer
 *needs a model from which the list gets the data that should be shown
 *this data model contains all information the list needs to operate with the images
 *that were loaded.
 *the file path is used to load the images on screen in the qml view
 *other informations are shown in the list and the details for each image
 *
 * !!!THIS IS CURRENTLY UNDER CONSTRUCTION!!!
 */
void ImageHandler::initImageDataModel(QList<QObject *> &model)
{
    if(model.count() > 0)
    {
        model.clear();
    }
    QFileInfoList::Iterator temp_it = this->file_info_list.begin();
    QImage temp_img;
    while(temp_it != this->file_info_list.end())
    {
        if((*temp_it).isFile())
        {
            temp_img = QImage((*temp_it).absoluteFilePath());
            FileInfoContainer file_info;
            file_info.name = (*temp_it).fileName();
            file_info.path = (*temp_it).absoluteFilePath();
            file_info.width = temp_img.width();
            file_info.height = temp_img.height();
            file_info.depth = temp_img.depth();
            file_info.xdpi = temp_img.dotsPerMeterX();
            file_info.ydpi = temp_img.dotsPerMeterY();
            file_info.size = (*temp_it).size();
            file_info.size_str = FileInfoHandler::getSizeStr((*temp_it).size());
            file_info.type = (*temp_it).suffix();

            model.append(new ImageDataEntry(file_info));
        }
        temp_it++;
    }
}

/** used to synchronize the index of the currently selected image file called by the CoreEngine::setQmlIndex(int index)*/
void ImageHandler::setCurFileIndex(int index)
{
    this->cur_file_index = index;
    this->cur_file_iterator = this->getFileListPosOfIndex(index,this->file_info_list);
}

bool ImageHandler::isFileSupported(QString filename)
{
    return this->file_support_handler->isFileSupported(filename);
}


