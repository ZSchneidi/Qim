#ifndef THEMEMANAGER_H
#define THEMEMANAGER_H

#include <QString>


class CoreEngine;

class ThemeManager
{

    CoreEngine *core;
    QString labe_style;
    QString area_style;

public:

    ThemeManager(CoreEngine *parent);

    void setLableStyle();
    void setAreaStyle();

};


#endif // THEMEMANAGER_H
