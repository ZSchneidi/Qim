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


public:
    explicit QmlInterface(CoreEngine *core);

    //inline int currIndex() const { return core->currQmlIndex(); }

    //inline void setCurrIndex( const int &index ) { if(index != core->currQmlIndex()) core->setIndex(index);  }
    void setCurrIndex( const int &index );
    void setIndexTo(int index);
    void updateQmlIndex(int index);

    inline const int currIndex() const { return this->curr_index; }

signals:

    void indexChanged();



};

#endif // QMLINTERFACE_H
