#ifndef QMLINTERFACE_H
#define QMLINTERFACE_H

#include <QObject>
#include "core/coreengine.h"

class CoreEngine;

class QmlInterface : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int currIndex READ currIndex WRITE setCurrIndex NOTIFY indexChanged )

    CoreEngine *core;


public:
    explicit QmlInterface(CoreEngine *core);

    //inline int currIndex() const { return core->currQmlIndex(); }
    int currIndex();
    //inline void setCurrIndex( const int &index ) { if(index != core->currQmlIndex()) core->setIndex(index);  }
    void setCurrIndex( const int &index );
    void setIndexTo(int index);
    void incrementIndex();
    void decrementIndex();

signals:

    void indexChanged();


public:

};

#endif // QMLINTERFACE_H
