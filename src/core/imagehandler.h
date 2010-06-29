#ifndef IMAGEHANDLER_H
#define IMAGEHANDLER_H

#include<QImage>
#include <QImage>
#include <QDir>
#include <QString>
#include <QFileInfoList>

/*
The image handler provides all functions needed to store
switch or access the loaded image data
*/
class ImageHandler
{

private:
    QString filepath;
    QString cur_folder_path;
    QString cur_file_name;

    QImage *pre_image;
    QImage *cur_image;
    QImage *pos_image;

    QPixmap *pre_image_pix;
    QPixmap *cur_image_pix;
    QPixmap *pos_image_pix;

    bool isSetPreImage;
    bool isSetCurImage;
    bool isSetPosImage;

    QDir cur_img_folder;

    QFileInfoList file_info_list;
    QFileInfoList::Iterator file_iterator;

    void setPreImage();
    void setPostImage();
    void loadImageFolder(QString path);
    void parseFolderPath(QString filepath);
    void initFileList();

public:

    ImageHandler();

    void setCurrImage(QString filepath);
    void scaleImage(int width, int height);

    /*to get read-only access to private QImage objects use: */
    inline const QImage& PreImage() const { return *pre_image; };
    inline const QImage& CurImage() const { return *cur_image; };
    inline const QImage& PosImage() const { return *pos_image; };
    inline const QPixmap& PreImagePix() const { return *pre_image_pix; };
    inline const QPixmap& CurImagePix() const { return *cur_image_pix; };
    inline const QPixmap& PosImagePix() const { return *pos_image_pix; };

};





#endif // IMAGEHANDLER_H
