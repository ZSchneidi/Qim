#include "fileinfohandler.h"
#include "ui_fileinfohandler.h"

#include <QDebug>
#include <QString>

FileInfoHandler::FileInfoHandler(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileInfoHandler)
{
    ui->setupUi(this);

    connect(ui->close_button,SIGNAL(clicked()),this,SLOT(close()));

    file_name_value = new QTableWidgetItem();
    file_width_value = new QTableWidgetItem();
    file_height_value = new QTableWidgetItem();
    file_depth_value = new QTableWidgetItem();
    file_xdpi_value = new QTableWidgetItem();
    file_ydpi_value = new QTableWidgetItem();
    file_size_value = new QTableWidgetItem();
    file_type_value = new QTableWidgetItem();
    file_lchange_value = new QTableWidgetItem();

    ui->fileinfotable->setItem(0,1,file_name_value);
    ui->fileinfotable->setItem(1,1,file_width_value);
    ui->fileinfotable->setItem(2,1,file_height_value);
    ui->fileinfotable->setItem(3,1,file_depth_value);
    ui->fileinfotable->setItem(4,1,file_xdpi_value);
    ui->fileinfotable->setItem(5,1,file_ydpi_value);
    ui->fileinfotable->setItem(6,1,file_size_value);
    ui->fileinfotable->setItem(7,1,file_type_value);
    ui->fileinfotable->setItem(8,1,file_lchange_value);


    /*to define how the file info dialog behaves you can use the WindowFlags*/
    setWindowFlags(Qt::Dialog);

}

void FileInfoHandler::updateFileInfo(const QFileInfo &file_info, const QImage &image)
{
    setNameValue(file_info.fileName());
    setWidthValue(image.width());
    setHeigthValue(image.height());
    setDepthValue(image.depth());
    setXdpiValue(image.dotsPerMeterX());
    setYdpiValue(image.dotsPerMeterY());
    setSizeValue(file_info.size());
    setSizeString(file_info.size());
    setTypeValue(file_info.suffix());
    setLChangeValue(file_info.lastModified());

    writeToTable();

}

void FileInfoHandler::writeToTable()
{
    setItemValue(0,1,file_info.name);
    setItemValue(1,1,QString::number(file_info.width));
    setItemValue(2,1,QString::number(file_info.height));
    setItemValue(3,1,QString::number(file_info.depth));
    setItemValue(4,1,QString::number(file_info.xdpi));
    setItemValue(5,1,QString::number(file_info.ydpi));
    setItemValue(6,1,file_info.size_str);
    setItemValue(7,1,file_info.type);
    setItemValue(8,1,file_info.lchange.toString());

}

void FileInfoHandler::setItemValue(int row, int column, QString text)
{
    ui->fileinfotable->item(row,column)->setText(text);
}


/*used to determin the file size*/
QString FileInfoHandler::getSizeOf(qint64 size)
{
    QString size_str;
    double file_size = 0.0;
    double tmp = size;
    int conv_lvl = 0;
    for(;;)
    {
        tmp = (tmp/1024);
        if(tmp < 1.0)
        {
             break;
        }
        file_size = tmp;
        conv_lvl++;
    }
    size_str = size_str.number(precision(file_size,2));

    switch(conv_lvl)
    {
        case 0: size_str.append(" Byte");
                break;
        case 1: if(file_size > 100)
                    size_str = size_str.number((int)file_size);
                size_str.append(" KB");
                break;
        case 2: size_str.append(" MB");
                break;
        case 3: size_str.append(" GB");
                break;
        case 4: size_str.append(" TB");
                break;
    }
    return size_str;
}

double FileInfoHandler::precision(double x, int precision)
{
    double temp = pow(10.0, precision);
    x *= temp;
    //x += 0.5;
    x = floor(x);
    x /= temp;
    return x;
}

double FileInfoHandler::round(double x, int precision)
{
    double temp = pow(10.0, precision);
    x *= temp;
    x += 0.5;
    x = floor(x);
    x /= temp;
    return x;
}


FileInfoHandler::~FileInfoHandler()
{
    delete ui;
}
