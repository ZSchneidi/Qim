#ifndef IMAGEDATAMODEL_H
#define IMAGEDATAMODEL_H

#include <QObject>

class ImageDataModel : public QObject
{
    Q_OBJECT

    QList<QObject *> imageDataModelList;


public:
    explicit ImageDataModel(QObject *parent = 0);

    inline QList<QObject *>& getDataModel() { return imageDataModelList; }

    void debugModel();

signals:

public slots:


};

#endif // IMAGEDATAMODEL_H
