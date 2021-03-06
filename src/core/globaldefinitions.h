#ifndef GLOBALDEFINITIONS_H
#define GLOBALDEFINITIONS_H

/*this header contains various constant definitions*/
#define APP_NAME "Qim"
#define QIMVISLAYERFILE "qrc:///qml_source/visuallayer/QimVisualLayer.qml"
#define QIMDEFLAYERFILE "qrc:///qml_source/visuallayer/QimDefaultLayer.qml"
#define QIMMAINUILAYERFILE "qrc:///qml_source/visuallayer/QimMainUILayer.qml"
#define SCALEFACTORX 0.3
#define SCALEFACTORY 0.3

#define CONFIG_SIZE_SEPERATOR "x"
/*config file definition*/
#define CONFIG_FILE "config.cfg"
/*config switch definition*/
/*these are the main config switch which are used by the ConfigHandler*/
#define FILE_INFO_SWITCH "ACTIVATE_FILE_INFO"
#define IMAGE_PRELOAD_SWITCH "ACTIVATE_IMAGE_PRELOAD"
#define IMAGE_SCALE_SWITCH "ACTIVATE_IMAGE_SCALE"
#define IMAGE_SMOOTH_SWITCH "ACTIVATE_IMAGE_SMOOTH"
#define IMAGE_STRECH_SWITCH "ACTIVATE_IMAGE_STRECH"
#define NAV_LOOP_SWITCH "ACTIVATE_NAV_LOOP"
#define PLUGIN_SWITCH "ACTIVATE_PLUGIN"
#define QML_LIST_SWITCH "ACTIVATE_QML_LIST"
#define RAW_SUPPORT_SWITCH "ACTIVATE_RAW_SUPPORT"
#define SECURE_NAV_SWITCH "ACTIVATE_SECURE_NAV"
#define SHADOWBOX_SWITCH "ACTIVATE_SHADOWBOX"
#define WINDOW_SIZE_SWITCH "DEF_WINDIOW_SIZE"
#define SUBDIR_SWITCH "INCLUDE_SUBDIR"
#define SUBDIR_FILES_SWITCH "INCLUDE_SUBDIR_FILES"
#define INVERT_NAV_SWITCH "INVERT_NAV_DIRECTION"
#define INVERT_ZOOM_SWITCH "INVERT_ZOOM_DIRECTION"
#define BACKGROUND_COLOR_SWITCH "MAIN_BACKGROUND_COLOR"
#define BACKGROUND_OPACITY_SWITCH "MAIN_BACKGROUND_OPACITY"
#define MAIN_LANG_SWITCH "MAIN_LANG"
#define MAIN_THEME_SWITCH "MAIN_THEME"
#define FULLSCREEN_SWITCH "START_FULLSCREEN"
#define MAXIMIZED_SWITCH "START_MAXIMIZED"
#define FILE_FORMAT_BLACKLIST_SWITCH "FILE_FORMAT_BLACKLIST"
#define ADVANCED_UI_SWITCH "ACTIVATE_ADVANCED_UI"


/*these config value definitions are used to switch to an
 *default value if the expected config switch wasn't found in the config
 */
#define DEFAULT_WINDOW_SIZE_WIDTH 640
#define DEFAULT_WINDOW_SIZE_HEIGHT 480
/*if your change the default window size try to keep int and string representation synchron*/
#define DEFAULT_WINDOW_SIZE "640"CONFIG_SIZE_SEPERATOR"480"
#define DEFAULT_START_MAX false
#define DEFAULT_START_FULL false
#define DEFAULT_FILE_INFO true
#define DEFAULT_IMAGE_PRE false
#define DEFAULT_IMAGE_SCALE true
#define DEFAULT_IMAGE_SMOOTH true
#define DEFAULT_IMAGE_STRECH false
#define DEFAULT_NAV_LOOP false
#define DEFAULT_PLUGIN true
#define DEFAULT_QML_LIST true
#define DEFAULT_RAW_SUPP true
#define DEFAULT_SEC_NAV false
#define DEFAULT_SHAD_BOX true
#define DEFAULT_SUBDIR false
#define DEFAULT_SUBDIR_FILE false
#define DEFAULT_INV_NAV false
#define DEFUALT_INV_ZOOM false
#define DFEAULT_BACK_COLOR "#ACB2BF"
#define DFEAULT_BACK_OPACITY "100"
#define DEFAULT_MAIN_LANG "LOCAL"
#define DEFAULT_MAIN_THEME "DEFAULT"
#define DEFAULT_BLACKLIST_FORMAT ""
#define DEFAULT_ADVANCED_UI true

#endif // GLOBALDEFINITIONS_H





