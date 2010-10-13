#include "backgroundcolorpicker.h"


#include <QDebug>
BackgroundColorPicker::BackgroundColorPicker(QWidget *parent) :
    QLabel(parent)
{

    QString temp = "#ffffff";
    this->updateLabelColor(temp);
    this->setGeometry(80,3,20,20);

    this->background_color = QColor();

}



void BackgroundColorPicker::mousePressEvent(QMouseEvent *ev)
{

    this->background_color = QColorDialog::getColor();
    if(this->background_color.isValid())
    {
        this->updateLabelColor(this->background_color.name());
        emit colorChanged(this->background_color);
    }
}

void BackgroundColorPicker::updateLabelColor(const QString color)
{
    if(color == "DEFAULT")
        this->setStyleSheet("QFrame, QLabel, QToolTip {border: 1px solid gray;border-radius: 4px;padding: 2px;background: #ffffff }");
    else
        this->setStyleSheet("QFrame, QLabel, QToolTip {border: 1px solid gray;border-radius: 4px;padding: 2px;background: "+color+QString("}"));
}




BackgroundColorPicker::~BackgroundColorPicker()
{

}
