#ifndef QMLINTERFACE_H
#define QMLINTERFACE_H

#include <QObject>
#include "core/coreengine.h"

class CoreEngine;

/*
 *The QmlInterface is the main interface for sharing informations between
 *the C++ logic and the Qml visual layer and the opposite way
 */
class QmlInterface : public QObject
{
    Q_OBJECT

    /*the active_layer property holds the path string of the qml source which has to be loaded in the QimMainUILayer*/
    Q_PROPERTY(QString active_layer READ getActiveLayer WRITE setActiveLayer NOTIFY activeLayerChanged)

    Q_PROPERTY(int index READ currIndex WRITE setCurrIndex NOTIFY indexChanged )
    Q_PROPERTY(QSize main_size READ mainSize NOTIFY mainSizeChanged )
    Q_PROPERTY(QPoint main_pos READ mainPos NOTIFY mainPosChanged )
    Q_PROPERTY(QPoint main_size_cursor READ mainSizeCursor NOTIFY mainSizeCursorChanged )
    Q_PROPERTY(QString main_title READ mainTitle NOTIFY mainTitleChanged )


    /*member variables*/
    CoreEngine *core;
    int curr_index;
    QString *active_layer;
    QString *main_title;
    QSize *main_size;
    QPoint *main_pos;
    QPoint *main_size_cursor;

    /*property setter*/
    /*set the index from qml*/
    void setCurrIndex( const int &index );
    /*set the active layer from qml*/
    void setActiveLayer(const QString layer_path);

public:


    enum zoomMode {IN,OUT};
    enum CoreAction {MAX,MIN,CLOSE};
    /*this enum represents all valid QimVisualLayer that can be defined as the main content layer in
     *the QimMainUILayer.qml
     */
    enum QmlLayer{Default_Layer,Visual_layer};

    explicit QmlInterface(CoreEngine *core);

    /*property getter*/
    inline const QString getActiveLayer() const { return *this->active_layer;}
    inline const int currIndex() const { return this->curr_index; }
    inline const QSize mainSize() const { return *this->main_size; }
    inline const QPoint mainPos() const { return *this->main_pos; }
    inline const QPoint mainSizeCursor() const { return *this->main_size_cursor; }
    inline const QString mainTitle() const { return *this->main_title; }
    CoreAction getCoreAction() const;

    /*switches the currently loaded component for content presentation
     *for more information take a look at the definiton of this method
     */
    void changeActiveLayer(QmlLayer path);
    void setNewSize(const QSize size);
    void setNewTitle(const QString title);
    void updateQmlIndex(const int index);
    void sendImageScaleSignal();
    void emitZoom(const zoomMode);



public slots:

    /*connection from qml*/
    void sendCoreAction( int action);
    //void sendCoreAction( CoreAction action);
    void setMainSize();
    void setMainPos();
    void resetPositionCursor();
    void resetSizeCursor();

signals:

    /*connection to qml*/
    void activeLayerChanged(const QString new_layer);
    void indexChanged();
    void mainSizeChanged();
    void mainTitleChanged(const QString new_title);
    void updateImageScale();
    void sizeChanged(const QSize &size);
    void zoomIn();
    void zoomOut();



};

#endif // QMLINTERFACE_H
