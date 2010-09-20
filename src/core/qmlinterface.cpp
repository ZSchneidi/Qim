#include "qmlinterface.h"

QmlInterface::QmlInterface(CoreEngine *parent_core) :
    QObject()
{
    core = parent_core;
    this->curr_index = 0;
    //index = 0;
}

void QmlInterface::setCurrIndex(const int &index)
{
    if(index != this->core->currQmlIndex())
        {
        this->core->setQmlIndex(index);
        this->updateQmlIndex(index);
        //this->updateQmlIndex(index);
        //this->curr_index = index;
        }
}

void QmlInterface::updateQmlIndex(int index)
{
    this->curr_index = index;
    emit indexChanged();
}




