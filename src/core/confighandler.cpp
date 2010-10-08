#include "confighandler.h"
#include "globaldefinitions.h"
#include <QDebug>


#define QT_USE_FAST_CONCATENATION
#define QT_USE_FAST_OPERATOR_PLUS

ConfigHandler::ConfigHandler()
{
    /*the config_head_line is just a short comment in the config file*/
    this->config_head_line = QString("#") + QString(APP_NAME) + QString("-Config\n");
    this->config_head_line.append("#this config file is automatically generated\n#please don't edit this lines unless you know what you're doing\n");

    this->config_map = new  QMap<QString, QString>;
    this->config_map_iterator = new QMap<QString, QString>::iterator;


    /*on constructing the config_handler the config file has to be loaded
     *and parsed to set all config variables
     */
    this->config_file = new QFile(CONFIG_FILE);
    if(this->config_file->open(QIODevice::ReadWrite))
    {
        while (!this->config_file->atEnd())
        {
            QByteArray line = this->config_file->readLine();
            QString temp_line(line);
            if(!isConfigComment(temp_line) && temp_line.count() > 2)
            {
                *this->config_map_iterator = this->extendConfigMap(temp_line);
                qDebug() << this->config_map_iterator->key() << "is " << this->config_map_iterator->value();
            }
        }
    }
    this->config_file->close();
}

QMap<QString, QString>::iterator ConfigHandler::extendConfigMap(const QString line)
{
    /*the delimiter index is the position of the : symbol which seperates the key from its value*/
    int delimiter_index = line.indexOf(":");
    /*create key and value string from the line as trimmed QString*/
    QString key = QString(line).remove(delimiter_index,line.length()).trimmed();
    QString value = QString(line).remove(0,delimiter_index+1).trimmed();
    return this->config_map->insert(key,value);

}

/*befor closing write the config back to config file*/
bool ConfigHandler::writeNewConfig()
{
    qint64 written_bytes = 0;
    this->config_file = new QFile(CONFIG_FILE);
    this->config_file->open(QIODevice::ReadWrite);
    this->config_file->write(this->config_head_line.toAscii());
    QMap<QString, QString>::const_iterator i = this->config_map->constBegin();
    while (i != this->config_map->constEnd()) {
        QString line = QString(i.key()).append(":").append(i.value()).append("\n");
        written_bytes += this->config_file->write(line.toAscii());
        ++i;
    }
    this->config_file->close();
    if(written_bytes <= 0)
        return false;
    else
        return true;
}

/*return the bool equivalent to the bool value of key*/
bool ConfigHandler::getBoolFromValue(const QString key)
{
    QMap<QString, QString>::const_iterator i = this->config_map->find(key);
    if(i.value().toUpper() == "TRUE" )
        return true;
    else
        return false;
}

/*return the value from key as QString*/
QString ConfigHandler::getStringValue(const QString key)
{
    QMap<QString, QString>::const_iterator i = this->config_map->find(key);
    return i.value();
}

/*return a bool String equivalent of value*/
QString ConfigHandler::getStrFromBool(const bool value)
{
    if(value == true)
        return "TRUE";
    else
        return "FALSE";
}

/*return the value of DEF_WINDIOW_SIZE*/
QSize ConfigHandler::defWindowSize()
{
    /*search for defaul size flag and make QSize out of it*/
    QString value = this->getStringValue("DEF_WINDIOW_SIZE").toUpper();
    int width = QString(value).remove(value.indexOf("X"),value.length()).toInt();
    int height = QString(value).remove(0,value.indexOf("X")+1).toInt();
    return QSize(width,height);
}

void ConfigHandler::setDefWindowSize(const QSize size)
{
    QString new_size;
    new_size.append(QString::number(size.width())).append("x").append(QString::number(size.height()));
    this->config_map->insert("DEF_WINDIOW_SIZE",new_size);
}

/*start maximizing getter and setter*/
bool ConfigHandler::startMaximized()
{
    return this->getBoolFromValue("START_MAXIMIZED");
}

void ConfigHandler::setStartMaximized(const bool is_max)
{
    this->config_map->insert("START_MAXIMIZED",this->getStrFromBool(is_max));
}

/*start fullscreen getter and setter*/
bool ConfigHandler::startFullScreen()
{
    return this->getBoolFromValue("START_FULLSCREEN");
}

void ConfigHandler::setStartFullScreen(const bool is_full)
{

    this->config_map->insert("START_FULLSCREEN",this->getStrFromBool(is_full));
}

/*file info getter and setter*/
bool ConfigHandler::isActiveFileInfo()
{
    return this->getBoolFromValue("ACTIVATE_FILE_INFO");
}

void ConfigHandler::setActiveFileInfo(const bool file_info)
{
    this->config_map->insert("ACTIVATE_FILE_INFO",this->getStrFromBool(file_info));
}

/*image preload getter and setter*/
bool ConfigHandler::isActiveImagePreload()
{
    return this->getBoolFromValue("ACTIVATE_IMAGE_PRELOAD");
}

void ConfigHandler::setActiveImagePreload(const bool image_pre)
{
    this->config_map->insert("ACTIVATE_IMAGE_PRELOAD",this->getStrFromBool(image_pre));
}

/*image scaling getter and setter*/
bool ConfigHandler::isActiveImageScale()
{
    return this->getBoolFromValue("ACTIVATE_IMAGE_SCALE");
}

void ConfigHandler::setActiveImageScale(const bool image_scale)
{
    this->config_map->insert("ACTIVATE_IMAGE_SCALE", this->getStrFromBool(image_scale));
}

/*image smooth */
bool ConfigHandler::isActiveImageSmooth()
{
    return this->getBoolFromValue("ACTIVATE_IMAGE_SMOOTH");
}

void ConfigHandler::setActiveImageSmooth(const bool image_smooth)
{
    this->config_map->insert("ACTIVATE_IMAGE_SMOOTH", this->getStrFromBool(image_smooth));
}

/*image streching getter and setter*/
bool ConfigHandler::isActiveImageStrech()
{
    return this->getBoolFromValue("ACTIVATE_IMAGE_STRECH");
}

void ConfigHandler::setActiveImageStrech(const bool image_strech)
{
    this->config_map->insert("ACTIVATE_IMAGE_STRECH", this->getStrFromBool(image_strech));
}

/*navigation loop getter and setter*/
bool ConfigHandler::isActiveNavLoop()
{
    return this->getBoolFromValue("ACTIVATE_NAV_LOOP");
}

void ConfigHandler::setActiveNavigationLoop(const bool nav_loop)
{
    this->config_map->insert("ACTIVATE_NAV_LOOP", this->getStrFromBool(nav_loop));
}

/*plugins getter and setter*/
bool ConfigHandler::isActivePlugIn()
{
    return this->getBoolFromValue("ACTIVATE_PLUGIN");
}

void ConfigHandler::setActivePlugin(const bool plugin)
{
    this->config_map->insert("ACTIVATE_PLUGIN", this->getStrFromBool(plugin));
}

/*qml list getter and setter*/
bool ConfigHandler::isActiveQmlList()
{
    return this->getBoolFromValue("ACTIVATE_QML_LIST");
}

void ConfigHandler::setActiveQmlList(const bool qml_list)
{
    this->config_map->insert("ACTIVATE_QML_LIST", this->getStrFromBool(qml_list));
}

/*raw support getter and setter*/
bool ConfigHandler::isActiveRawSupport()
{
    return this->getBoolFromValue("ACTIVATE_RAW_SUPPORT");
}

void ConfigHandler::setActiveRawSupport(const bool raw_support)
{
    this->config_map->insert("ACTIVATE_RAW_SUPPORT",this->getStrFromBool(raw_support));
}

/*secure navigation*/
bool ConfigHandler::isActiveSecureNav()
{
    return this->getBoolFromValue("ACTIVATE_SECURE_NAV");
}

void ConfigHandler::setActiveSecureNav(const bool sec_nav)
{
    this->config_map->insert("ACTIVATE_SECURE_NAV", this->getStrFromBool(sec_nav));
}


/*shadowbox getter and setter*/
bool ConfigHandler::isActiveShadowBox()
{
    return this->getBoolFromValue("ACTIVATE_SHADOWBOX");
}

void ConfigHandler::setActiveShadowBox(const bool shad_box)
{
    this->config_map->insert("ACTIVATE_SHADOWBOX", this->getStrFromBool(shad_box));
}

/*include subdir getter and setter*/
bool ConfigHandler::includeSubdir()
{
    return this->getBoolFromValue("INCLUDE_SUBDIR");
}

void ConfigHandler::setIncludeSubDir(const bool sub_dir)
{
    this->config_map->insert("INCLUDE_SUBDIR", this->getStrFromBool(sub_dir));
}

/*include subdir files getter and setter*/
bool ConfigHandler::includeSubdirFiles()
{
    return this->getBoolFromValue("INCLUDE_SUBDIR_FILES");
}

void ConfigHandler::setIncludeSubDirFiles(const bool sub_dir_files)
{
    this->config_map->insert("INCLUDE_SUBDIR_FILES", this->getStrFromBool(sub_dir_files));
}

/*invert navigation direction getter and setter*/
bool ConfigHandler::invertNavDirection()
{
    return this->getBoolFromValue("INVERT_NAV_DIRECTION");
}

void ConfigHandler::setInvertNavigation(const bool inv_nav)
{
    this->config_map->insert("INVERT_NAV_DIRECTION", this->getStrFromBool(inv_nav));
}

/*invert zoom direction getter and setter*/
bool ConfigHandler::invertZoomDirection()
{
    return this->getBoolFromValue("INVERT_ZOOM_DIRECTION");
}

void ConfigHandler::setInvertZoom(const bool inv_zoom)
{
    this->config_map->insert("INVERT_ZOOM_DIRECTION", this->getStrFromBool(inv_zoom));
}

/*main background color getter and setter*/
QString ConfigHandler::mainBackgroundColor()
{
    return this->getStringValue("MAIN_BACKGROUND_COLOR");
}

void ConfigHandler::setMainBackgroundColor(const QString back_color)
{
    this->config_map->insert("MAIN_BACKGROUND_COLOR", back_color);
}

/*main theme getter and setter*/
QString ConfigHandler::mainTheme()
{
    return this->getStringValue("MAIN_THEME");
}

void ConfigHandler::setMainTheme(const QString main_theme)
{
    this->config_map->insert("MAIN_THEME",main_theme);
}

/*main language getter and setter*/
QString ConfigHandler::mainLanguage()
{
    return this->getStringValue("MAIN_LANG");
}

void ConfigHandler::setMainLanguage(const QString main_lang)
{
    this->config_map->insert("MAIN_LANG",main_lang);
}

/*supported files*/
QString ConfigHandler::supFileFormatStr()
{
    return this->getStringValue("SUP_FILE_FORMAT");
}

void ConfigHandler::setSupportedFormats(const Qstring supp_format)
{
    this->config_map->insert("SUP_FILE_FORMAT",supp_format);
}

bool ConfigHandler::isConfigComment(const QString line)
{
    if(line.startsWith("//") || line.startsWith("#"))
        return true;
    else return false;
}

