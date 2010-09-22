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

    Q_PROPERTY(int index READ currIndex WRITE setCurrIndex NOTIFY indexChanged )
    Q_PROPERTY(int main_width READ mainWidth CONSTANT )
    Q_PROPERTY(int main_height READ mainHeight CONSTANT )

    CoreEngine *core;
    int curr_index;
    int main_width;
    int main_height;
    /*set the index from qml*/
    void setCurrIndex( const int &index );

public:

    enum zoomMode {IN,OUT};

    explicit QmlInterface(CoreEngine *core);

    inline const int currIndex() const { return this->curr_index; }
    inline const int mainWidth() const { return this->main_width; }
    inline const int mainHeight() const { return this->main_height; }

    void setNewSize(const QSize size);
    /**/
    void updateQmlIndex(int index);
    void emitZoom(zoomMode);

signals:

    void sizeChanged(const QSize &size);
    void indexChanged();
    void zoomIn();
    void zoomOut();



};

#endif // QMLINTERFACE_H








/*

class QmlInterface : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int index READ currIndex WRITE setCurrIndex NOTIFY indexChanged )

    CoreEngine *core;
    int curr_index;


    void setCurrIndex( const int &index );

public:
    explicit QmlInterface(CoreEngine *core);

    inline const int currIndex() const { return this->curr_index; }

    void updateQmlIndex(int index);

signals:

    void indexChanged();



};



*/
