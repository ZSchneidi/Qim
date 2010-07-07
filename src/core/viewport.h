#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QGraphicsPixmapItem>

class ViewPort : public QGraphicsView
{
    bool is_set_pixmap;
    QRectF default_rect;
    QGraphicsPixmapItem *pixmap_item;

public:
    ViewPort(QWidget *parent = 0);

    void zoomIn(qreal x, qreal y);
    void zoomOut(qreal x, qreal y);

    void showPixmap(const QPixmap &pixmap);

    QGraphicsScene *image_scene;

protected:
        void dragEnterEvent(QDragEnterEvent *event);
        void dropEvent(QDropEvent *event);
        //void dragMoveEvent(QDragMoveEvent *event);



};

#endif // VIEWPORT_H
