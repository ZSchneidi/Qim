#ifndef CONFIGHANDLER_H
#define CONFIGHANDLER_H

#include <QFile>
#include <QMap>
#include <QSize>

class ConfigHandler
{

    QFile *config_file;
    QMap<QString, QString> *config_map;
    QMap<QString, QString>::Iterator *config_map_iterator;
    QMap<QString, QString>::Iterator extendConfigMap(const QString line);

    QString config_head_line;

    bool getBoolFromValue(const QString key);
    QString getStringValue(const QString key);
    QString getStrFromBool(const bool value);


public:

    ConfigHandler();

    bool writeNewConfig();

    /*config switch getter*/
    bool isConfigComment(const QString line);
    QString mainLanguage();
    QString mainTheme();
    QString mainBackgroundColor();
    QString supFileFormatStr();
    QSize defWindowSize();
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

    /*config switch setter*/
    void setDefWindowSize(const QSize size);
    void setStartMaximized(const bool is_max);
    void setStartFullScreen(const bool is_fullscreen);
    void setMainTheme(const QString main_theme);
    void setMainLanguage(const QString main_lang);
    void setMainBackgroundColor(const QString back_color);
    void setIncludeSubDir(const bool sub_dir);
    void setIncludeSubDirFiles(const bool sub_dir_files);
    void setInvertNavigation(const bool inv_nav);
    void setInvertZoom(const bool inv_zoom);
    void setSupportedFormats(const Qstring supp_format);
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

};

#endif // CONFIGHANDLER_H
