#ifndef IMAGEDATAMODEL_H
#define IMAGEDATAMODEL_H

#include <QObject>
#include "fileinfohandler.h"

class ImageDataModel : public QObject
{
    Q_OBJECT
    /*The NOTIFY signal in the property is used to emit a signal when the property vlaue is changed
    but it is optional. Don't know why I get a message: depends on non-NOTIFYable properties when using
    without NOTIFY*/
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(QString path READ path CONSTANT)

public:
    ImageDataModel(FileInfoContainer file_info );

    inline QString name() const {return m_name; }
    inline QString path() const {return m_path; }
    inline QString sizeStr() const {return m_filesize_str; }
    inline int width() const {return m_width; }
    inline int heigth() const {return m_heigth; }
    inline int depth() const {return m_depth; }
    inline int xdpi() const {return m_xdpi; }
    inline int ydpi() const {return m_ydpi; }
    inline int size() const {return m_size; }

private:

    /*property values have to initiate in the construcor
    they are CONSTANT properties*/
    QString  m_name;
    QString  m_path;
    QString m_filesize_str;
    QString m_ldate;
    int m_width;
    int m_heigth;
    int m_depth;
    int m_xdpi;
    int m_ydpi;
    int m_size;

};

#endif // IMAGEDATAMODEL_H
