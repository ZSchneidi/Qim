#include "imagedatamodel.h"
#include <QDebug>

ImageDataModel::ImageDataModel(QObject *parent) :
    QObject(parent)
{

    this->imageDataModelList.clear();

}


void ImageDataModel::debugModel()
{
    //qDebug() << "anzahl einträge " << this->imageDataModelList.count();
}
