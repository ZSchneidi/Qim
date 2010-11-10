#include "confighandler.h"
#include "globaldefinitions.h"
#include <QDebug>


#define QT_USE_FAST_CONCATENATION
#define QT_USE_FAST_OPERATOR_PLUS



/**
 *The ConfigHandler operates with a config file which name is defined
 *in the globaldefinition.h to swith features on or off the handler
 *is parsing the config file and provides information about the config
 *swithes to the config dialog and the hole application
 *these switch identifiers are also defined in the globaldefinition.h
 *
 *if additional features have to be implemented remeber following:
 *implement the getter and setter in the config handler
 *provide editable widgets in the config dialog
 *and the signals which are emitted when there value was changed
 */
ConfigHandler::ConfigHandler(CoreEngine *core) : QObject()
{
    this->core = core;
    /*the config_head_line is just a comment in the config file*/
    this->config_head_line = QString("#") + QString(APP_NAME) + QString("-Config\n");
    this->config_head_line.append("#this config file is automatically generated\n#please don't edit these lines unless you know what you're doing\n");
    this->config_head_line.append("#the config allow only single line comments with # or // - do not append comments after a config switch\n");
    this->config_head_line.append(QString("#deleted options will be restored automatically by ")+QString(APP_NAME)+QString("\n"));

    this->config_map = new  QMap<QString, QString>;
    this->config_map_iterator = new QMap<QString, QString>::iterator;
    this->config_file_rw_access = false;

    /*on constructing the config_handler the config file has to be loaded
     *and parsed to set all config variables
     */
    this->config_file = new QFile(CONFIG_FILE);
    if(!this->config_file->exists())
    {
        this->restoreConfig();
    }
    else
    {
        if(this->config_file->open(QIODevice::ReadWrite))
        {
            this->config_file_rw_access = true;
            while (!this->config_file->atEnd())
            {
                QByteArray line = this->config_file->readLine();
                QString temp_line(line);
                if(!isConfigComment(temp_line) && temp_line.count() > 2)
                {
                    *this->config_map_iterator = this->extendConfigMap(temp_line);
                    //qDebug() << this->config_map_iterator->key() << "is " << this->config_map_iterator->value();
                }
            }
            /*if the config is incomplete restore all missing config switches*/
            this->restoreConfig();
            this->config_file->close();
        }
        /**if the config file can't be opened just to restore default config for runtime
         */
        else
        {
            this->restoreConfig();
        }
    }
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

/*before closing write the config back to config file*/
bool ConfigHandler::writeNewConfig()
{
    if(!this->config_file_rw_access)
    {
        /*if the config_file_rw_access is false the config wasn't read from the
         *config file if the user would write the config it would be written with default values
         */
        QString config_warning = QObject::tr("Could not open Config file! Do you want to reset Config file ?");
        this->core->showErrorDialog(config_warning);
    }
    qint64 written_bytes = 0;
    this->config_file = new QFile(CONFIG_FILE);
    this->config_file->remove();
    if(this->config_file->open(QIODevice::ReadWrite))
    {
        this->config_file->write(this->config_head_line.toAscii());
        QMap<QString, QString>::const_iterator i = this->config_map->constBegin();
        while (i != this->config_map->constEnd())
        {
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
    /*if config couldn't be written a warning should be shown*/
    else
        return false;
}

/*if the config file does not exist the config handler restore the config map with default values
 *in the case that the config file was opened but incomplete the restoreconfig() will check
 *if a switch is missing and restore it
 *the config will be written to file on close via writeNewConfig()
 */
void ConfigHandler::restoreConfig()
{
    if(this->config_map->find(FILE_INFO_SWITCH) == this->config_map->end())
        this->config_map->insert(FILE_INFO_SWITCH,this->getStrFromBool(DEFAULT_FILE_INFO));
    if(this->config_map->find(IMAGE_PRELOAD_SWITCH) == this->config_map->end())
        this->config_map->insert(IMAGE_PRELOAD_SWITCH,this->getStrFromBool(DEFAULT_IMAGE_PRE));
    if(this->config_map->find(IMAGE_SCALE_SWITCH) == this->config_map->end())
        this->config_map->insert(IMAGE_SCALE_SWITCH,this->getStrFromBool(DEFAULT_IMAGE_SCALE));
    if(this->config_map->find(IMAGE_SMOOTH_SWITCH) == this->config_map->end())
        this->config_map->insert(IMAGE_SMOOTH_SWITCH,this->getStrFromBool(DEFAULT_IMAGE_SMOOTH));
    if(this->config_map->find(IMAGE_STRECH_SWITCH) == this->config_map->end())
        this->config_map->insert(IMAGE_STRECH_SWITCH,this->getStrFromBool(DEFAULT_IMAGE_STRECH));
    if(this->config_map->find(NAV_LOOP_SWITCH) == this->config_map->end())
        this->config_map->insert(NAV_LOOP_SWITCH,this->getStrFromBool(DEFAULT_NAV_LOOP));
    if(this->config_map->find(PLUGIN_SWITCH) == this->config_map->end())
        this->config_map->insert(PLUGIN_SWITCH,this->getStrFromBool(DEFAULT_PLUGIN));
    if(this->config_map->find(QML_LIST_SWITCH) == this->config_map->end())
        this->config_map->insert(QML_LIST_SWITCH,this->getStrFromBool(DEFAULT_QML_LIST));
    if(this->config_map->find(RAW_SUPPORT_SWITCH) == this->config_map->end())
        this->config_map->insert(RAW_SUPPORT_SWITCH,this->getStrFromBool(DEFAULT_RAW_SUPP));
    if(this->config_map->find(SECURE_NAV_SWITCH) == this->config_map->end())
        this->config_map->insert(SECURE_NAV_SWITCH,this->getStrFromBool(DEFAULT_SEC_NAV));
    if(this->config_map->find(SHADOWBOX_SWITCH) == this->config_map->end())
        this->config_map->insert(SHADOWBOX_SWITCH,this->getStrFromBool(DEFAULT_SHAD_BOX));
    if(this->config_map->find(WINDOW_SIZE_SWITCH) == this->config_map->end())
        this->config_map->insert(WINDOW_SIZE_SWITCH,DEFAULT_WINDOW_SIZE);
    if(this->config_map->find(SUBDIR_SWITCH) == this->config_map->end())
        this->config_map->insert(SUBDIR_SWITCH,this->getStrFromBool(DEFAULT_SUBDIR));
    if(this->config_map->find(SUBDIR_FILES_SWITCH) == this->config_map->end())
        this->config_map->insert(SUBDIR_FILES_SWITCH,this->getStrFromBool(DEFAULT_SUBDIR_FILE));
    if(this->config_map->find(INVERT_NAV_SWITCH) == this->config_map->end())
        this->config_map->insert(INVERT_NAV_SWITCH,this->getStrFromBool(DEFAULT_INV_NAV));
    if(this->config_map->find(INVERT_ZOOM_SWITCH) == this->config_map->end())
        this->config_map->insert(INVERT_ZOOM_SWITCH,this->getStrFromBool(DEFUALT_INV_ZOOM));
    if(this->config_map->find(BACKGROUND_COLOR_SWITCH) == this->config_map->end())
        this->config_map->insert(BACKGROUND_COLOR_SWITCH,DFEAULT_BACK_COLOR);
    if(this->config_map->find(BACKGROUND_OPACITY_SWITCH) == this->config_map->end())
        this->config_map->insert(BACKGROUND_OPACITY_SWITCH,DFEAULT_BACK_OPACITY);
    if(this->config_map->find(MAIN_LANG_SWITCH) == this->config_map->end())
        this->config_map->insert(MAIN_LANG_SWITCH,DEFAULT_MAIN_LANG);
    if(this->config_map->find(MAIN_THEME_SWITCH) == this->config_map->end())
        this->config_map->insert(MAIN_THEME_SWITCH,DEFAULT_MAIN_THEME);
    if(this->config_map->find(FULLSCREEN_SWITCH) == this->config_map->end())
        this->config_map->insert(FULLSCREEN_SWITCH,this->getStrFromBool(DEFAULT_START_FULL));
    if(this->config_map->find(MAXIMIZED_SWITCH) == this->config_map->end())
        this->config_map->insert(MAXIMIZED_SWITCH,this->getStrFromBool(DEFAULT_START_MAX));
    if(this->config_map->find(FILE_FORMAT_BLACKLIST_SWITCH) == this->config_map->end())
        this->config_map->insert(FILE_FORMAT_BLACKLIST_SWITCH,DEFAULT_BLACKLIST_FORMAT);
    if(this->config_map->find(ADVANCED_UI_SWITCH) == this->config_map->end())
        this->config_map->insert(ADVANCED_UI_SWITCH,this->getStrFromBool(DEFAULT_ADVANCED_UI));
}

/*this method is called when saving the config dialog
 *it is used to parse all changed values and emit the signals to activate the changed features
 */
void ConfigHandler::transactNewConfig(QMap<QString, QString> *temp_config_map)
{
    QMap<QString, QString>::const_iterator i = temp_config_map->constBegin();
    while (i != temp_config_map->constEnd())
    {
        QString key = QString(i.key());
        QString value = QString(i.value());
        if(value != "")
        {
            this->config_map->insert(key,value);
            if(key == BACKGROUND_OPACITY_SWITCH)
                emit this->backgroundOpacityChanged(value.toFloat());  //update the opacity in the QmlInterface
            if(key == BACKGROUND_COLOR_SWITCH)
                emit this->backgroundColorChanged(value);               //update the color in the QmlInterface
            if(key == FILE_FORMAT_BLACKLIST_SWITCH)
                emit this->blacklistedFormatsChanged(value);            //update the blacklist string in FileSupport

            //qDebug() << "write to config " << key << ":" << value;
        }
        ++i;
    }
}


/*return the bool equivalent to the bool value of key
 *if the key wasn't found in the config file it returns false
 */
bool ConfigHandler::getBoolFromValue(const QString key)
{
    if(this->config_map->find(key).value().toUpper() == "TRUE" )
        return true;
    else
        return false;
}

/*return the value from key as QString*/
QString ConfigHandler::getStringFromValue(const QString key)
{
    return this->config_map->find(key).value();
}

/*return a bool String equivalent of value*/
QString ConfigHandler::getStrFromBool(const bool value)
{
    if(value == true)
        return "TRUE";
    else
        return "FALSE";
}

/*return true is the key is stored in the config_map otherwise return false*/
bool ConfigHandler::switchExists(const QString key)
{
    if(this->config_map->find(key) != this->config_map->end())
        return true;
    else
        return false;
}

/*defaul window size getter and setter*/
QSize ConfigHandler::defWindowSize()
{
    /*search for defaul size flag and make QSize out of it*/
    QString value;

    if(this->switchExists(WINDOW_SIZE_SWITCH))
    {
        value = this->getStringFromValue(WINDOW_SIZE_SWITCH);
    }
    /*if the value of the window size switch wasn't found set size to default value definition*/
    else
    {
        value = DEFAULT_WINDOW_SIZE;
    }
    int width = QString(value).remove(value.indexOf(CONFIG_SIZE_SEPERATOR),value.length()).toInt();
    int height = QString(value).remove(0,value.indexOf(CONFIG_SIZE_SEPERATOR)+1).toInt();
    return QSize(width,height);
}

void ConfigHandler::setDefWindowSize(const QSize size)
{
    QString new_size;
    new_size.append(QString::number(size.width())).append(CONFIG_SIZE_SEPERATOR).append(QString::number(size.height()));
    this->config_map->insert(WINDOW_SIZE_SWITCH,new_size);
}

/*start maximizing getter and setter*/
bool ConfigHandler::startMaximized()
{
    if(this->switchExists(MAXIMIZED_SWITCH))
        return this->getBoolFromValue(MAXIMIZED_SWITCH);
    else
        return DEFAULT_START_MAX;
}

void ConfigHandler::setStartMaximized(const bool is_max)
{
    this->config_map->insert(MAXIMIZED_SWITCH,this->getStrFromBool(is_max));
}

/*start fullscreen getter and setter*/
bool ConfigHandler::startFullScreen()
{
    if(this->switchExists(FULLSCREEN_SWITCH))
        return this->getBoolFromValue(FULLSCREEN_SWITCH);
    else
        return DEFAULT_START_FULL;
}

void ConfigHandler::setStartFullScreen(const bool is_full)
{
    this->config_map->insert(FULLSCREEN_SWITCH,this->getStrFromBool(is_full));
}

/*file info getter and setter*/
bool ConfigHandler::isActiveFileInfo()
{
    if(this->switchExists(FILE_INFO_SWITCH))
        return this->getBoolFromValue(FILE_INFO_SWITCH);
    else
        return DEFAULT_FILE_INFO;
}

void ConfigHandler::setActiveFileInfo(const bool file_info)
{
    this->config_map->insert(FILE_INFO_SWITCH,this->getStrFromBool(file_info));
}

/*image preload getter and setter*/
bool ConfigHandler::isActiveImagePreload()
{
    if(this->switchExists(IMAGE_PRELOAD_SWITCH))
        return this->getBoolFromValue(IMAGE_PRELOAD_SWITCH);
    else
        return DEFAULT_IMAGE_PRE;
}

void ConfigHandler::setActiveImagePreload(const bool image_pre)
{
    this->config_map->insert(IMAGE_PRELOAD_SWITCH,this->getStrFromBool(image_pre));
}

/*image scaling getter and setter*/
bool ConfigHandler::isActiveImageScale()
{
    if(this->switchExists(IMAGE_SCALE_SWITCH))
        return this->getBoolFromValue(IMAGE_SCALE_SWITCH);
    else
        return DEFAULT_IMAGE_SCALE;
}

void ConfigHandler::setActiveImageScale(const bool image_scale)
{
    this->config_map->insert(IMAGE_SCALE_SWITCH, this->getStrFromBool(image_scale));
}

/*image smooth */
bool ConfigHandler::isActiveImageSmooth()
{
    if(this->switchExists(IMAGE_SMOOTH_SWITCH))
        return this->getBoolFromValue(IMAGE_SMOOTH_SWITCH);
    else
        return DEFAULT_IMAGE_SMOOTH;
}

void ConfigHandler::setActiveImageSmooth(const bool image_smooth)
{
    this->config_map->insert(IMAGE_SMOOTH_SWITCH, this->getStrFromBool(image_smooth));
}

/*image streching getter and setter*/
bool ConfigHandler::isActiveImageStrech()
{
    if(this->switchExists(IMAGE_STRECH_SWITCH))
        return this->getBoolFromValue(IMAGE_STRECH_SWITCH);
    else
        return DEFAULT_IMAGE_STRECH;
}

void ConfigHandler::setActiveImageStrech(const bool image_strech)
{
    this->config_map->insert(IMAGE_STRECH_SWITCH, this->getStrFromBool(image_strech));
}

/*navigation loop getter and setter*/
bool ConfigHandler::isActiveNavLoop()
{
    if(this->switchExists(NAV_LOOP_SWITCH))
        return this->getBoolFromValue(NAV_LOOP_SWITCH);
    else
        return DEFAULT_NAV_LOOP;
}

void ConfigHandler::setActiveNavigationLoop(const bool nav_loop)
{
    this->config_map->insert(NAV_LOOP_SWITCH, this->getStrFromBool(nav_loop));
}

/*plugins getter and setter*/
bool ConfigHandler::isActivePlugIn()
{
    if(this->switchExists(PLUGIN_SWITCH))
        return this->getBoolFromValue(PLUGIN_SWITCH);
    else
        return DEFAULT_PLUGIN;
}

void ConfigHandler::setActivePlugin(const bool plugin)
{
    this->config_map->insert(PLUGIN_SWITCH, this->getStrFromBool(plugin));
}

/*qml list getter and setter*/
bool ConfigHandler::isActiveQmlList()
{
    if(this->switchExists(QML_LIST_SWITCH))
        return this->getBoolFromValue(QML_LIST_SWITCH);
    else
        return DEFAULT_QML_LIST;
}

void ConfigHandler::setActiveQmlList(const bool qml_list)
{
    this->config_map->insert(QML_LIST_SWITCH, this->getStrFromBool(qml_list));
}

/*raw support getter and setter*/
bool ConfigHandler::isActiveRawSupport()
{
    if(this->switchExists(RAW_SUPPORT_SWITCH))
        return this->getBoolFromValue(RAW_SUPPORT_SWITCH);
    else
        return DEFAULT_RAW_SUPP;
}

void ConfigHandler::setActiveRawSupport(const bool raw_support)
{
    this->config_map->insert(RAW_SUPPORT_SWITCH,this->getStrFromBool(raw_support));
}

/*secure navigation getter and setter*/
bool ConfigHandler::isActiveSecureNav()
{
    if(this->switchExists(SECURE_NAV_SWITCH))
        return this->getBoolFromValue(SECURE_NAV_SWITCH);
    else
        return DEFAULT_SEC_NAV;
}

void ConfigHandler::setActiveSecureNav(const bool sec_nav)
{
    this->config_map->insert(SECURE_NAV_SWITCH, this->getStrFromBool(sec_nav));
}


/*shadowbox getter and setter*/
bool ConfigHandler::isActiveShadowBox()
{
    if(this->switchExists(SHADOWBOX_SWITCH))
        return this->getBoolFromValue(SHADOWBOX_SWITCH);
    else
        return DEFAULT_SHAD_BOX;
}

void ConfigHandler::setActiveShadowBox(const bool shad_box)
{
    this->config_map->insert(SHADOWBOX_SWITCH, this->getStrFromBool(shad_box));
}

/*include subdir getter and setter*/
bool ConfigHandler::includeSubdir()
{
    if(this->switchExists(SUBDIR_SWITCH))
        return this->getBoolFromValue(SUBDIR_SWITCH);
    else
        return DEFAULT_SUBDIR;
}

void ConfigHandler::setIncludeSubDir(const bool sub_dir)
{
    this->config_map->insert(SUBDIR_SWITCH, this->getStrFromBool(sub_dir));
}

/*include subdir files getter and setter*/
bool ConfigHandler::includeSubdirFiles()
{
    if(this->switchExists(SUBDIR_FILES_SWITCH))
        return this->getBoolFromValue(SUBDIR_FILES_SWITCH);
    else
        return DEFAULT_SUBDIR_FILE;
}

void ConfigHandler::setIncludeSubDirFiles(const bool sub_dir_files)
{
    this->config_map->insert(SUBDIR_FILES_SWITCH, this->getStrFromBool(sub_dir_files));
}

/*invert navigation direction getter and setter*/
bool ConfigHandler::invertNavDirection()
{
    if(this->switchExists(INVERT_NAV_SWITCH))
        return this->getBoolFromValue(INVERT_NAV_SWITCH);
    else
        return DEFAULT_INV_NAV;
}

void ConfigHandler::setInvertNavigation(const bool inv_nav)
{
    this->config_map->insert(INVERT_NAV_SWITCH, this->getStrFromBool(inv_nav));
}

/*invert zoom direction getter and setter*/
bool ConfigHandler::invertZoomDirection()
{
    if(this->switchExists(INVERT_ZOOM_SWITCH))
        return this->getBoolFromValue(INVERT_ZOOM_SWITCH);
    else
        return DEFUALT_INV_ZOOM;
}

void ConfigHandler::setInvertZoom(const bool inv_zoom)
{
    this->config_map->insert(INVERT_ZOOM_SWITCH, this->getStrFromBool(inv_zoom));
}

/*main background color getter and setter*/
QString ConfigHandler::mainBackgroundColor()
{
    if(this->switchExists(BACKGROUND_COLOR_SWITCH))
        return this->getStringFromValue(BACKGROUND_COLOR_SWITCH);
    else
        return DFEAULT_BACK_COLOR;
}

void ConfigHandler::setMainBackgroundColor(const QString back_color)
{
    this->config_map->insert(BACKGROUND_COLOR_SWITCH, back_color);
}

/*main background opacity getter and setter*/
int ConfigHandler::mainBackgroundOpacity()
{
    bool ok;
    if(this->switchExists(BACKGROUND_OPACITY_SWITCH))
        return this->getStringFromValue(BACKGROUND_OPACITY_SWITCH).toInt(&ok,10);
    else
        return QString(DFEAULT_BACK_OPACITY).toInt(&ok,10);
}

void ConfigHandler::setMainBackgroundOpacity(const int opacity)
{
    this->config_map->insert(BACKGROUND_OPACITY_SWITCH,QString::number(opacity));
}

/*main theme getter and setter*/
QString ConfigHandler::mainTheme()
{
    if(this->switchExists(MAIN_THEME_SWITCH))
        return this->getStringFromValue(MAIN_THEME_SWITCH);
    else
        return DEFAULT_MAIN_THEME;
}

void ConfigHandler::setMainTheme(const QString main_theme)
{
    this->config_map->insert(MAIN_THEME_SWITCH,main_theme);
}

/*main language getter and setter*/
QString ConfigHandler::mainLanguage()
{
    if(this->switchExists(MAIN_LANG_SWITCH))
        return this->getStringFromValue(MAIN_LANG_SWITCH);
    else
        return DEFAULT_MAIN_LANG;
}

void ConfigHandler::setMainLanguage(const QString main_lang)
{
    this->config_map->insert(MAIN_LANG_SWITCH,main_lang);
}

/*supported files getter and setter*/
QString ConfigHandler::FileFormatBlacklistStr()
{
    if(this->switchExists(FILE_FORMAT_BLACKLIST_SWITCH))
        return this->getStringFromValue(FILE_FORMAT_BLACKLIST_SWITCH);
    else
        return DEFAULT_BLACKLIST_FORMAT;
}

void ConfigHandler::setSupportedFormats(const QString supp_format)
{
    this->config_map->insert(FILE_FORMAT_BLACKLIST_SWITCH,supp_format);
}

/*advanced ui getter and setter*/
bool ConfigHandler::isActiveAdvancedUI()
{
    if(this->switchExists(ADVANCED_UI_SWITCH))
        return this->getBoolFromValue(ADVANCED_UI_SWITCH);
    else
        return DEFAULT_ADVANCED_UI;
}

void ConfigHandler::setActiveAdvancedUI(const bool adv_ui)
{
    this->config_map->insert(ADVANCED_UI_SWITCH, this->getStrFromBool(adv_ui));
}
bool ConfigHandler::isConfigComment(const QString line)
{
    if(line.startsWith("//") || line.startsWith("#"))
        return true;
    else return false;
}

