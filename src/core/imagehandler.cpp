#include "imagehandler.h"
#include "core/coreengine.h"

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

}

void ImageHandler::setPostImage()
{

}

void ImageHandler::scaleImage(int width, int height)
{

    *cur_image = cur_image->scaled(width,height,Qt::KeepAspectRatio,Qt::SmoothTransformation);
}
