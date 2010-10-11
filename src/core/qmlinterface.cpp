#include "qmlinterface.h"

QmlInterface::QmlInterface(CoreEngine *parent_core) :
    QObject()
{
    this->core = parent_core;
    this->curr_index = 0;
    this->main_pos = new QPoint(0,0);
    this->main_size_cursor = new QPoint(0,0);
    this->main_size = new QSize();
    this->main_title = new QString;
    this->active_layer = new QString("");

}
/*
QmlInterface::CoreAction QmlInterface::coreAction() const
{

    return this->CoreAction;
}*/

/*this method is designed to send action signals to the core engine*/
//void QmlInterface::sendCoreAction(CoreAction action)
void QmlInterface::sendCoreAction(int action)
{
    /*for definition of coreAction take a look at the enum definition in the qmlinterface header*/
    switch (action)
    {
        case 0: if(this->core->isMaximized())
                {
                    this->core->showNormal();
                }
                else
                    this->core->showMaximized();
                break;
        case 1: this->core->showMinimized();
                break;
        case 2: this->core->callCoreAction(CoreEngine::OPEN);
                break;
        case 3: this->core->callCoreAction(CoreEngine::CLOSE);
                break;
        case 4: this->core->callCoreAction(CoreEngine::ABOUT);
                break;
        case 5: this->core->callCoreAction(CoreEngine::FULLSCREEN);
                break;
        case 6: this->core->callCoreAction(CoreEngine::CONFIG);
                break;
    }
}
/*this method is a major part of the new QML based UI concept
 *by default Qim loads the QimMainUILayer.qml which is basically
 *the new version of an MainWindow implemented in QML in this file
 *is a loader which can dynamically load different Components or sources
 *the main content view is viewing only the QimDefaultLayer.qml which
 *is just a kind of placeholder.
 *when an image is loaded the QimMainUILayer has to change the main content view
 *to an qml component which is designed to display images on screen.
 *Normally this should be the QimVisualLayer.qml which was designed to do so, or implement
 *another qml source to handle image data and switch to this one.
 *
 *therefor the QmlLayer enum was implemented to control the different layer
 */
void QmlInterface::changeActiveLayer(QmlLayer path)
{
    /*temp_path must be defined with the relative path of the .qml source of the layer you want
     *to load as main content handler. to define the path mind that the QimMainUILayer.qml
     *is located in the /visuallayer directory in the main application folder so you don't have to define
     *the absolute path to this folder only subdirectories have to be written.
     *this is basically the folder for all qml files
     */
    QString temp_path;
    switch(path)
    {
    case 0: temp_path = "QimDefaultLayer.qml";
            break;
    case 1: temp_path = "QimVisualLayer.qml";
            break;

    }
    *this->active_layer = temp_path;
    emit this->activeLayerChanged(*this->active_layer);
}

/*this method is called when changing the image index in the qml environment*/
void QmlInterface::setCurrIndex(const int &index)
{
    if(index != this->core->currQmlIndex())
        {
        this->core->setQmlIndex(index);
        this->updateQmlIndex(index);
        /*the updateSignal has to be emitted to redefine the size of the image presentation*/
        emit this->updateImageScale();
        }
}

void QmlInterface::setActiveLayer(const QString layer_path)
{
    *this->active_layer = layer_path;
    emit this->activeLayerChanged(*this->active_layer);
}

void QmlInterface::setMainSize()
{
    //this->core->resize(this->core->width(),this->core->height()+height);
    if(this->main_size_cursor->x()> 0 && this->main_size_cursor->y() > 0)
    {
        int w_diff = QCursor::pos().x() - this->main_size_cursor->x();
        int h_diff = QCursor::pos().y() - this->main_size_cursor->y();
        this->core->resize(this->core->width()+w_diff,this->core->height()+h_diff);
    }
    this->main_size_cursor->setX( QCursor::pos().x());
    this->main_size_cursor->setY( QCursor::pos().y());

    /*after any resize the imageScaleSignal has to be emit to scale the image to the new window size*/
    this->sendImageScaleSignal();
}


void QmlInterface::setMainPos()
{
    if(this->main_pos->x()> 0 && this->main_pos->y() > 0)
    {
        int x_diff = QCursor::pos().x() - this->main_pos->x();
        int y_diff = QCursor::pos().y() - this->main_pos->y();
        this->core->move(this->core->x()+x_diff,this->core->y()+y_diff);
    }
    this->main_pos->setX( QCursor::pos().x());
    this->main_pos->setY( QCursor::pos().y());
}

void QmlInterface::resetPositionCursor()
{
    this->main_pos->setX(0);
    this->main_pos->setY(0);
}

void QmlInterface::resetSizeCursor()
{
    this->main_size_cursor->setX(0);
    this->main_size_cursor->setY(0);
}
/*called when the mainWindow is changing its size to forward the size to the
 *qml visual layer
 */
void QmlInterface::setNewSize(const QSize size)
{
    *this->main_size = size;
    emit this->sizeChanged(size);
}

void QmlInterface::setNewTitle(const QString title)
{
    *this->main_title = title;
    emit this->mainTitleChanged(title);
}

/*used to synchronize the index of the currently selected file with the qml environment*/
void QmlInterface::updateQmlIndex(const int index)
{
    this->curr_index = index;
    emit this->indexChanged();
}

/*after initializing the qml mainView with a new image source the size of the image has
 *to be determined
 *in the case that the actual image size is bigger that the current Window size the image
 *has to be scaled down to a smaller size, so that it fits the view
 *in the case that the images size is smaller than the current window size the image
 *will be presented in its real size
 */
void QmlInterface::sendImageScaleSignal()
{
    /*the logic is implemented directly in qml
     *take a look at the QimVisualLayer.qml -> mainPicture Connections{} element
     */
    /*update the main_size for comparison*/
    *this->main_size = this->core->size();
    /*emit the signal which is catched by the qml layer*/
    emit this->updateImageScale();
}

void QmlInterface::emitZoom(const zoomMode mode)
{
    /*enum  mode defined in the qmlinterface header*/
    switch(mode)
    {
    case 0: emit this->zoomIn();
            break;
    case 1: emit this->zoomOut();
            break;
    }
}






