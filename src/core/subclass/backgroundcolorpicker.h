#ifndef BACKGROUNDCOLORPICKER_H
#define BACKGROUNDCOLORPICKER_H

#include <QLabel>
#include <QColorDialog>

class BackgroundColorPicker : public QLabel
{

    Q_OBJECT
    QColor background_color;


    void mousePressEvent(QMouseEvent *ev);


public:
    BackgroundColorPicker(QWidget *parent = 0);



    void updateLabelColor(const QString color);

    ~BackgroundColorPicker();

signals:

    void colorChanged(const QColor color);

};

#endif // BACKGROUNDCOLORPICKER_H
