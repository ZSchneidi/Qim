#ifndef IMAGEHANDLER_H
#define IMAGEHANDLER_H

#include<QImage>


/*
The image handler provides all functions needed to store
switch or access the loaded image data
*/
class ImageHandler
{

private:
    QImage *pre_image;
    QImage *cur_image;
    QImage *pos_image;

    QPixmap *pre_image_pix;
    QPixmap *cur_image_pix;
    QPixmap *pos_image_pix;

    bool isSetPreImage;
    bool isSetCurImage;
    bool isSetPosImage;


public:

    ImageHandler();

    void setPreImage();
    void setCurrImage(QString filepath);
    void setPostImage();
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
