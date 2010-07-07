#include "viewport.h"

#include <QDebug>

ViewPort::ViewPort(QWidget *parent) :
        QGraphicsView(parent)
{
    is_set_pixmap = false;
    setAcceptDrops(true);

    /*implementation of the QGraphicsScene*/
    /*the image_scene contains all image data*/
    image_scene = new QGraphicsScene;
    image_scene->addText(tr("no picture loaded"));

    /*the image_view needs the image_scene*/
    setScene(image_scene);
    default_rect = image_scene->sceneRect();
    setOptimizationFlag(QGraphicsView::DontAdjustForAntialiasing);

    setTransformationAnchor(QGraphicsView::AnchorViewCenter);

    //setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setDragMode(QGraphicsView::ScrollHandDrag);
}

void ViewPort::showPixmap(const QPixmap &pixmap)
{
    if(is_set_pixmap)
        image_scene->removeItem(pixmap_item);
    image_scene->clear();
    resetTransform();
    pixmap_item = image_scene->addPixmap(pixmap);
    is_set_pixmap = true;
    show();
}

void ViewPort::zoomIn(qreal x, qreal y)
{
    scale((1.0+x),(1.0+y));
}

void ViewPort::zoomOut(qreal x, qreal y)
{
    scale((1.0-x),(1.0-y));
}

void ViewPort::dragEnterEvent(QDragEnterEvent *event)
{
        qDebug() << "Enter";
}

void ViewPort::dropEvent(QDropEvent *event)
{
        qDebug() << "file droped";
}
/*
void ViewPort::dragMoveEvent(QDragMoveEvent *event)
{
    qDebug() << "drag moved";
}
*/
