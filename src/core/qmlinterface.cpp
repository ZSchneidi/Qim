#include "qmlinterface.h"

QmlInterface::QmlInterface(CoreEngine *parent_core) :
    QObject()
{
    core = parent_core;
    this->curr_index = 0;
    this->main_height = 0;
    this->main_width = 0;
}

/*this method is called when changing the image index in the qml environment*/
void QmlInterface::setCurrIndex(const int &index)
{
    if(index != this->core->currQmlIndex())
        {
        this->core->setQmlIndex(index);
        this->updateQmlIndex(index);
qDebug() << "index changed in qml to " << this->core->currQmlIndex();
        }
    else
qDebug() << "same index";
}

/*called when the mainWindow is changing its size to forward the size to the
 *qml visual layer
 */
void QmlInterface::setNewSize(const QSize size)
{
    this->main_height = size.height();
    this->main_width = size.width();
    qDebug() << "new Size " << size;
}
/*used to synchronize the index of the currently selected file with the qml environment*/
void QmlInterface::updateQmlIndex(int index)
{
    this->curr_index = index;
qDebug() << "curIndex " << this->curr_index;
    emit indexChanged();
}

void QmlInterface::emitZoom(zoomMode mode)
{
    switch(mode)
    {
    case 0: emit this->zoomIn();
            break;
    case 1: emit this->zoomOut();
            break;
    }
}






