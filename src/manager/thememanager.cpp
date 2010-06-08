#include "thememanager.h"
#include "core/coreengine.h"


ThemeManager::ThemeManager(CoreEngine *parent)
{

    core = parent;

    core->image_label->setStyleSheet("background: transparent; color: white;");
    core->image_area->setStyleSheet("background: rgb(103, 103, 103);");
}

void ThemeManager::setLableStyle()
{


}

void ThemeManager::setAreaStyle()
{

}
