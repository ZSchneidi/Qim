#ifndef CONFIGHANDLER_H
#define CONFIGHANDLER_H
#include "core/coreengine.h"

#include <QFile>
#include <QMap>
#include <QSize>

class CoreEngine;


/*the ConfigHandler is designed to manage the global configuration
 *it reads several config switches from the config file and provides them to the coreengine
 *the confighandler also have the ability to restore lost config files or missing switches in the config file
 *the configuraton interface is implemented in the configdialog which gets a pointer to the confighandler to
 *set the switches.
 */
class ConfigHandler : public QObject
{

    Q_OBJECT
    /*member*/
    QFile *config_file;
    QMap<QString, QString> *config_map;
    QMap<QString, QString>::Iterator *config_map_iterator;
    QMap<QString, QString>::Iterator extendConfigMap(const QString line);
    QString config_head_line;
    bool config_file_rw_access;

    /*pointer to coreengine as parent object*/
    CoreEngine *core;

    /*methods*/
    bool getBoolFromValue(const QString key);
    bool switchExists(const QString key);
    QString getStringFromValue(const QString key);
    QString getStrFromBool(const bool value);

    void restoreConfig();


public:

    ConfigHandler(CoreEngine *core);

    QMap<QString, QString> *getConfigMap() { return this->config_map; }
    bool writeNewConfig();

    /**/
    void transactNewConfig(QMap<QString, QString> *temp_config);

    /*config switch getter*/
    bool isConfigComment(const QString line);
    QString mainLanguage();
    QString mainTheme();
    QString mainBackgroundColor();
    QString supFileFormatStr();
    QSize defWindowSize();
    int mainBackgroundOpacity();
    bool startMaximized();
    bool startFullScreen();
    bool includeSubdir();
    bool includeSubdirFiles();
    bool invertNavDirection();
    bool invertZoomDirection();
    bool isActiveImagePreload();
    bool isActiveSecureNav();
    bool isActiveQmlList();
    bool isActiveShadowBox();
    bool isActiveImageSmooth();
    bool isActiveImageScale();
    bool isActiveImageStrech();
    bool isActiveFileInfo();
    bool isActiveNavLoop();
    bool isActivePlugIn();
    bool isActiveRawSupport();
    bool isActiveAdvancedUI();

    /*config switch setter*/
    void setDefWindowSize(const QSize size);
    void setStartMaximized(const bool is_max);
    void setStartFullScreen(const bool is_fullscreen);
    void setMainTheme(const QString main_theme);
    void setMainLanguage(const QString main_lang);
    void setMainBackgroundColor(const QString back_color);
    void setMainBackgroundOpacity(const int opacity);
    void setIncludeSubDir(const bool sub_dir);
    void setIncludeSubDirFiles(const bool sub_dir_files);
    void setInvertNavigation(const bool inv_nav);
    void setInvertZoom(const bool inv_zoom);
    void setSupportedFormats(const QString supp_format);
    void setActiveRawSupport(const bool raw_support);
    void setActiveFileInfo(const bool file_info);
    void setActiveImagePreload(const bool image_pre);
    void setActiveImageScale(const bool image_scale);
    void setActiveImageStrech(const bool image_strech);
    void setActiveImageSmooth(const bool image_smooth);
    void setActiveNavigationLoop(const bool nav_loop);
    void setActivePlugin(const bool plugin);
    void setActiveQmlList(const bool qml_list);
    void setActiveSecureNav(const bool sec_nav);
    void setActiveShadowBox(const bool shad_box);
    void setActiveAdvancedUI(const bool adv_ui);

signals:

    void backgroundColorChanged(QString color);
    void backgroundOpacityChanged(double opacity);


};

#endif // CONFIGHANDLER_H
