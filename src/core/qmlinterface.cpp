#include "qmlinterface.h"

QmlInterface::QmlInterface(CoreEngine *parent_core) :
    QObject()
{
    //core = parent_core;
    this->curr_index = 0;
    core = CoreEngine::getInstance();
    //index = 0;
}

void QmlInterface::setIndexTo(int index)
{
    core->setIndex(index);
}

void QmlInterface::setCurrIndex(const int &index)
{
    if(index != core->currQmlIndex())
        core->setIndex(index);
}

void QmlInterface::updateQmlIndex(int index)
{
    this->curr_index = index;
    qDebug() << "curIndex " << this->curr_index;
    emit indexChanged();
}




