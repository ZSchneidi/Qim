#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H
#include "core/confighandler.h"
#include "core/coreengine.h"
#include "core/globaldefinitions.h"
#include "core/subclass/backgroundcolorpicker.h"

#include <QDialog>
#include <QColorDialog>
#include <QShowEvent>
#include <QDebug>

namespace Ui {
    class ConfigDialog;
}

class ConfigHandler;
class CoreEngine;

class ConfigDialog : public QDialog
{
    Q_OBJECT

    /*temporary config map which will be insert into the config_map of the confighandler on saving*/
    QMap<QString, QString> *temp_config_map;

    QColor main_background_color;

    ConfigHandler *config_handler;
    CoreEngine *core;

    BackgroundColorPicker *back_picker;

    bool init_config_started;

    void initConfig();
    void setLanguage();

    void showEvent(QShowEvent *);


public slots:

    /*standard signals connected via QMetaObject::connectSlotsByName*/
    void on_lang_combo_box_currentIndexChanged(int index);
    void on_theme_combo_box_currentIndexChanged(int index);
    void on_supp_file_edit_textEdited(QString txt);
    void on_save_config_button_clicked();
    void on_cancel_config_buttion_clicked();
    void on_check_image_preload_stateChanged(int state);
    void on_check_secure_nav_stateChanged(int state);
    void on_check_load_subdir_stateChanged(int state);
    void on_check_load_subdir_files_stateChanged(int state);
    void on_check_invert_nav_stateChanged(int state);
    void on_check_nav_loop_stateChanged(int state);
    void on_check_invert_zooming_stateChanged(int state);
    void on_check_image_list_stateChanged(int state);
    void on_check_shadow_box_stateChanged(int state);
    void on_check_image_smooth_stateChanged(int state);
    void on_check_image_scaling_stateChanged(int state);
    void on_check_image_streching_stateChanged(int state);
    void on_check_load_fileinfo_stateChanged(int state);
    void on_check_advanced_ui_stateChanged(int state);
    void on_check_start_fullscreen_stateChanged(int state);
    void on_check_activate_plugin_stateChanged(int state);
    void on_background_opacity_valueChanged(int value);
    /*subclass signals using connect in construtor*/
    void changeBackColor(const QColor color);

public:
    explicit ConfigDialog(QWidget *parent, CoreEngine *core, ConfigHandler *config_handler);
    //explicit ConfigDialog(ConfigHandler *config_handler);

    QString convStateToBoolStr(int state);

    ~ConfigDialog();

private:
    Ui::ConfigDialog *ui;
};

#endif // CONFIGDIALOG_H
