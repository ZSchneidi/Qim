#ifndef IMAGEHANDLER_H
#define IMAGEHANDLER_H

#include<QImage>
#include <QImage>
#include <QDir>
#include <QString>
#include <QFileInfoList>
#include <QFile>
#include <QObject>

#include "core/coreengine.h"
#include "filesupport.h"
#include "imagedatamodel.h"


class CoreEngine;
class FileSupport;

/*
 *The image handler provides all functions needed to store
 *switch or access the loaded image data.
 *The image handler also provides QDir - directory handler
 *as well as the list of all supported files in the directory.
 */
class ImageHandler : public FileInfoHandler
{

private:

    /*provides the path to the folder which was initialzed by loadImageFolder()*/
    QString cur_folder_path;
    /*provides only the name of the file which is currentlly loaded*/
    QString cur_file_name;
    /*provides the path to the the loaded image file*/
    QString cur_file_path;
    /*this string is used by the updateMainTitle() function from coreengine*/
    QString title_str;

    QFileInfo cur_image_file;

    QImage *pre_image;
    QImage *cur_image;
    QImage *pos_image;

    QPixmap *pre_image_pix;
    QPixmap *cur_image_pix;
    QPixmap *pos_image_pix;

    QDir cur_img_folder;

    /*list of all images in the current directory*/
    QFileInfoList file_info_list;
    /*reference to the currently loaded file*/
    QFileInfoList::Iterator cur_file_iterator;
    /*reference to the first file in the file_info_list*/
    QFileInfoList::Iterator first_file_iterator;
    /*reference to the last file in the file_info_list*/
    QFileInfoList::Iterator last_file_iterator;

    /*provides all information about supported file types*/
    FileSupport *file_support_handler;

    /*the coreengine provides all major features used by several classes */
    CoreEngine *core;

    /*will be initialized by getFileListPosOf() and updated by loadNextImage() or loadPrevImage()*/
    int cur_file_index;

    /*setter*/
    void parseFolderPath(QString cur_file_path);
    void initFileList(QFileInfoList &list);
    void initFileIterator(QFileInfoList &list);

    bool loadImageFolder(QString path);

    /*getter*/
    QFileInfoList::Iterator getFileListPosOf(const QString &filename , QFileInfoList &list);
    QFileInfoList::Iterator getFileListPosOfIndex(const int index, QFileInfoList &list);

    QString getFilePathFromList(const QFileInfoList::Iterator position, QFileInfoList &list);

public:

    ImageHandler(CoreEngine *core);

    /*is used to verify whether the cur_image is already loaded*/
    bool isSetCurImage;
    /*is used to verify whether a directory is already loaded by loadImageFolder()*/
    bool isSetDir;

    /*setter*/
    /*
     *loadNext and loadPrev iterate from first image to last image
     *and stop at begin() and end() looping isn't implement yet
     */
    bool loadNextImage();
    bool loadPrevImage();
    void loadImage(const QString cur_file_path);
    void scaleImage(int width, int height);

    /**/
    void freeImageFolder();

    /*this setter method is used to initialize the data model for the qml
    interface with all data of the images*/
    void initImageDataModel(QList<QObject *> & model);

    /*set the file_index of the image_handler to index*/
    void setCurFileIndex(int index);

    /*getter*/
    /*returns a string with the path of the current file for the main title*/
    inline const QString& getTitleStr() const {return title_str; }
    inline const QFileInfo& getCurImageFileInfo() const {return (*cur_file_iterator);}
    inline const FileSupport* getFileSupport() const { return this->file_support_handler; }

    /*to get read-only access to private QImage objects use: */
    inline const QImage& getPreImage() const { return *pre_image; }
    inline const QImage& getCurImage() const { return *cur_image; }
    inline const QImage& getPosImage() const { return *pos_image; }
    inline const QPixmap& getPreImagePix() const { return *pre_image_pix; }
    inline const QPixmap& getCurImagePix() const { return *cur_image_pix; }
    inline const QPixmap& getPosImagePix() const { return *pos_image_pix; }
    inline const int getCurFileIndex() const { return cur_file_index; }

    /*redirected method calls*/
    bool isFileSupported(QString filename);

};





#endif // IMAGEHANDLER_H
