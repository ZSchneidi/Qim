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

class FileInfoHandler : public QWidget
{
    Q_OBJECT

    /*the convert_str is used to convert numbers into a string*/
    QString convert_str;

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

    void setItemValue(int row, int column, QString text);
    void setNameValue(QString text);
    void setWidthValue(int value);
    void setHeigthValue(int value);
    void setDepthValue(int value);
    void setXdpiValue(int value);
    void setYdpiValue(int value);
    void setSizeValue(qint64 value);
    void setTypeValue(QString text);
    void setLChangeValue(QDateTime date);

public:

    void updateFileInfo(const QFileInfo &file_info, const QImage &image);

    explicit FileInfoHandler(QWidget *parent = 0);
    ~FileInfoHandler();

    QString getSizeOf(qint64 size);
    double precision(double x, int precision);
    double round(double x, int precision);

private:
    Ui::FileInfoHandler *ui;
};

#endif // FILEINFOHANDLER_H
