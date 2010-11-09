#ifndef IMAGEDATAENTRY_H
#define IMAGEDATAENTRY_H

#include <QObject>
#include "fileinfohandler.h"

/*
 *The ImageDataModel class is design to record various informations about every
 *image file that was found in the loaded folder.
 *ImageDataModel class is used by ImageHandler::initImageDataModel() to create a list
 *of informations of all images
 */
class ImageDataEntry : public QObject
{
    Q_OBJECT
    /*The NOTIFY signal in the property is used to emit a signal when the property vlaue is changed
    but it is optional. Don't know why I get a message: depends on non-NOTIFYable properties when using
    without NOTIFY*/
    Q_PROPERTY(QString m_name READ name CONSTANT)
    Q_PROPERTY(QString m_path READ path CONSTANT)
    Q_PROPERTY(QString m_sizeStr READ sizeStr CONSTANT)
    Q_PROPERTY(int m_width READ width CONSTANT)
    Q_PROPERTY(int m_height READ height CONSTANT)
    Q_PROPERTY(int m_xdpi READ xdpi CONSTANT)
    Q_PROPERTY(int m_ydpi READ ydpi CONSTANT)
    Q_PROPERTY(int m_size READ size CONSTANT)

public:
    ImageDataEntry(FileInfoContainer file_info );

    inline QString name() const {return m_name; }
    inline QString path() const {return m_path; }
    inline QString sizeStr() const {return m_size_str; }
    inline int width() const {return m_width; }
    inline int height() const {return m_height; }
    inline int depth() const {return m_depth; }
    inline int xdpi() const {return m_xdpi; }
    inline int ydpi() const {return m_ydpi; }
    inline int size() const {return m_size; }

private:

    /*property values have to initiate in the construcor
    they are CONSTANT properties*/
    QString  m_name;
    QString  m_path;
    QString m_size_str;
    QString m_ldate;
    int m_width;
    int m_height;
    int m_depth;
    int m_xdpi;
    int m_ydpi;
    int m_size;

};

#endif // IMAGEDATAENTRY_H
