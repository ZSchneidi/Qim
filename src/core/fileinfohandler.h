#ifndef FILEINFOHANDLER_H
#define FILEINFOHANDLER_H

#include <QWidget>
#include <QTableWidgetItem>
#include <QDateTime>
#include <QFileInfo>
#include <math.h>

namespace Ui {
    class FileInfoHandler;
}

/*this class can store all major and minor file informations
 *and is used by the ImageHandler::initImageDataModel() function
 *to store the information in the
 */
class FileInfoContainer
{
public:
    QString name;
    QString path;
    QString type;
    QString size_str;
    double size;
    int width;
    int height;
    int depth;
    double xdpi;
    double ydpi;
    QDateTime lchange;

};

/*this class set all informations of a file in the FileInfoContainer*/
class FileInfoHandler : public QWidget
{
    Q_OBJECT

    /*the FileInfoContainer provides several informations about an image file*/
    FileInfoContainer file_info;

    /*QTableWidget is provided by the form*/

    QTableWidgetItem *file_name_value;
    QTableWidgetItem *file_width_value;
    QTableWidgetItem *file_height_value;
    QTableWidgetItem *file_depth_value;
    QTableWidgetItem *file_xdpi_value;
    QTableWidgetItem *file_ydpi_value;
    QTableWidgetItem *file_size_value;
    QTableWidgetItem *file_type_value;
    QTableWidgetItem *file_lchange_value;

    /*used to write the values in the ui table*/
    inline void setItemValue(int row, int column, QString text);

    inline void setNameValue(QString name) {file_info.name = name;}
    inline void setWidthValue(int value) { file_info.width = value;}
    inline void setHeigthValue(int value) {file_info.height = value;}
    inline void setDepthValue(int value) {file_info.depth = value;}
    inline void setXdpiValue(int value) {file_info.xdpi = round(((double)value/100)*2.54, 0);}
    inline void setYdpiValue(int value) {file_info.ydpi = round(((double)value/100)*2.54, 0);}
    inline void setSizeValue(qint64 value) {file_info.size = (double)value;}
    inline void setSizeString(qint64 value) {file_info.size_str = getSizeOf(value);}
    inline void setTypeValue(QString type) {file_info.type = type;}
    inline void setLChangeValue(QDateTime date) {file_info.lchange = date;}

    QString getSizeOf(qint64 size);

public:

    QString getSizeStr(qint64 size) {return getSizeOf(size); }
    QString getDateStr(QDateTime date ) {return date.toString();}
    double getXDpi(int dotspermeterx) {return round(((double)dotspermeterx/100)*2.54, 0);}
    double getYDpi(int dotspermetery) {return round(((double)dotspermetery/100)*2.54, 0);}
    double precision(double x, int precision);
    double round(double x, int precision);

    void updateFileInfo(const QFileInfo &file_info, const QImage &image);

    explicit FileInfoHandler(QWidget *parent = 0);
    ~FileInfoHandler();

    void writeToTable();

private:
    Ui::FileInfoHandler *ui;
};

#endif // FILEINFOHANDLER_H
