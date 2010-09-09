#ifndef QMLINTERFACE_H
#define QMLINTERFACE_H

#include <QObject>
#include "core/coreengine.h"

class CoreEngine;

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
