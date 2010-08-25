#include "qmlinterface.h"

QmlInterface::QmlInterface(CoreEngine *parent_core) :
    QObject()
{
    core = parent_core;

    //index = 0;
}

void QmlInterface::setIndexTo(int index)
{
    core->setIndex(index);
}

int QmlInterface::currIndex()
{
    return core->currQmlIndex();
    //return this->index;
}

void QmlInterface::setCurrIndex(const int &index)
{
    if(index != core->currQmlIndex())
        core->setIndex(index);
}

void QmlInterface::incrementIndex()
{
    core->incCurrQmlIndex();
    //emit indexChanged();
}

void QmlInterface::decrementIndex()
{
    core->decCurrQmlIndex();
    //emit indexChanged();
}



