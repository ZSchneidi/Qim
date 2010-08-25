#include "fileinfohandler.h"
#include "ui_fileinfohandler.h"

#include <QDebug>
#include <QString>

FileInfoHandler::FileInfoHandler(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileInfoHandler)
{
    this->ui->setupUi(this);

    this->connect(this->ui->close_button,SIGNAL(clicked()),this,SLOT(close()));

    this->file_name_value = new QTableWidgetItem();
    this->file_width_value = new QTableWidgetItem();
    this->file_height_value = new QTableWidgetItem();
    this->file_depth_value = new QTableWidgetItem();
    this->file_xdpi_value = new QTableWidgetItem();
    this->file_ydpi_value = new QTableWidgetItem();
    this->file_size_value = new QTableWidgetItem();
    this->file_type_value = new QTableWidgetItem();
    this->file_lchange_value = new QTableWidgetItem();

    this->ui->fileinfotable->setItem(0,1,this->file_name_value);
    this->ui->fileinfotable->setItem(1,1,this->file_width_value);
    this->ui->fileinfotable->setItem(2,1,this->file_height_value);
    this->ui->fileinfotable->setItem(3,1,this->file_depth_value);
    this->ui->fileinfotable->setItem(4,1,this->file_xdpi_value);
    this->ui->fileinfotable->setItem(5,1,this->file_ydpi_value);
    this->ui->fileinfotable->setItem(6,1,this->file_size_value);
    this->ui->fileinfotable->setItem(7,1,this->file_type_value);
    this->ui->fileinfotable->setItem(8,1,this->file_lchange_value);


    /*to define how the file info dialog behaves you can use the WindowFlags*/
    this->setWindowFlags(Qt::Dialog);

}

void FileInfoHandler::updateFileInfo(const QFileInfo &file_info, const QImage &image)
{
    this->setNameValue(file_info.fileName());
    this->setWidthValue(image.width());
    this->setHeigthValue(image.height());
    this->setDepthValue(image.depth());
    this->setXdpiValue(image.dotsPerMeterX());
    this->setYdpiValue(image.dotsPerMeterY());
    this->setSizeValue(file_info.size());
    this->setSizeString(file_info.size());
    this->setTypeValue(file_info.suffix());
    this->setLChangeValue(file_info.lastModified());

    this->writeToTable();

}

void FileInfoHandler::writeToTable()
{
    this->setItemValue(0,1,file_info.name);
    this->setItemValue(1,1,QString::number(file_info.width));
    this->setItemValue(2,1,QString::number(file_info.height));
    this->setItemValue(3,1,QString::number(file_info.depth));
    this->setItemValue(4,1,QString::number(file_info.xdpi));
    this->setItemValue(5,1,QString::number(file_info.ydpi));
    this->setItemValue(6,1,file_info.size_str);
    this->setItemValue(7,1,file_info.type);
    this->setItemValue(8,1,file_info.lchange.toString());

}

void FileInfoHandler::setItemValue(int row, int column, QString text)
{
    this->ui->fileinfotable->item(row,column)->setText(text);
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
    delete this->ui;
}
