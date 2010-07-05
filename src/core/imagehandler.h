#ifndef IMAGEHANDLER_H
#define IMAGEHANDLER_H

#include<QImage>
#include <QImage>
#include <QDir>
#include <QString>
#include <QFileInfoList>
#include <QFile>
#include <QObject>

#include "filesupport.h"

/*
 *The image handler provides all functions needed to store
 *switch or access the loaded image data.
 *The image handler also provides QDir - directory handler
 *as well as the list of all supported files in the directory.
 */
class ImageHandler
{

private:

    /*provides the path to the folder which was initialzed by loadImageFolder()*/
    QString cur_folder_path;
    /*provides only the name of the file which is currentlly loaded*/
    QString cur_file_name;
    /*provides the path to the the loaded image file*/
    QString cur_file_path;

    QFile *cur_image_file;

    QImage *pre_image;
    QImage *cur_image;
    QImage *pos_image;

    QPixmap *pre_image_pix;
    QPixmap *cur_image_pix;
    QPixmap *pos_image_pix;

    QDir cur_img_folder;

    QFileInfoList file_info_list;
    /*reference to the currently loaded file*/
    QFileInfoList::Iterator cur_file_iterator;
    /*reference to the first file in the file_info_list*/
    QFileInfoList::Iterator first_file_iterator;
    /*reference to the last file in the file_info_list*/
    QFileInfoList::Iterator last_file_iterator;

    /*provides all information about supported file types*/
    FileSupport *file_support_handler;

    /*will be updated by getFileListPosOf() */
    int cur_file_index;

    /*setter*/
    /*not in use*/
    void setPreImage();
    /*not in use*/
    void setPostImage();
    void parseFolderPath(QString cur_file_path);
    void initFileList(QFileInfoList &list);
    void initFileIterator(QFileInfoList &list);

    bool loadImageFolder(QString path);

    /*getter*/
    QFileInfoList::Iterator getFileListPosOf(const QString &filename , QFileInfoList &list);

    QString getFilePathFromList(const QFileInfoList::Iterator position, QFileInfoList &list);

public:

    /*not in use*/
    bool isSetPreImage;
    /*is used to verify whether the cur_image is already loaded*/
    bool isSetCurImage;
    /*not in use*/
    bool isSetPosImage;
    /*is used to verify whether a directory is already loaded by loadImageFolder()*/
    bool isSetDir;

    ImageHandler();
    /*setter*/
    /*
     *loadNext and loadPrev iterate from first image to last image
     *and stop at begin() and end() looping isn't implement yet
     */
    bool loadNextImage();
    bool loadPrevImage();
    void loadImage(const QString cur_file_path);
    void scaleImage(int width, int height);

    /*getter*/

    /*to get read-only access to private QImage objects use: */
    inline const QImage& getPreImage() const { return *pre_image; };
    inline const QImage& getCurImage() const { return *cur_image; };
    inline const QImage& getPosImage() const { return *pos_image; };
    inline const QPixmap& getPreImagePix() const { return *pre_image_pix; };
    inline const QPixmap& getCurImagePix() const { return *cur_image_pix; };
    inline const QPixmap& getPosImagePix() const { return *pos_image_pix; };

};





#endif // IMAGEHANDLER_H
