#include "imagedatamodel.h"
#include <QDebug>

ImageDataModel::ImageDataModel(QObject *parent) :
    QObject(parent)
{

    this->imageDataModelList.clear();

}


void ImageDataModel::debugModel()
{
    //qDebug() << "anzahl eintr�ge " << this->imageDataModelList.count();
}
