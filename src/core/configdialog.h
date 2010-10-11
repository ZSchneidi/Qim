#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H
#include "core/confighandler.h"
#include "core/coreengine.h"
#include "core/globaldefinitions.h"

#include <QDialog>
#include <QColorDialog>
#include <QShowEvent>

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

    bool init_config_started;

    void initConfig();
    void setLanguage();

    void showEvent(QShowEvent *);


public slots:

    void on_lang_combo_box_currentIndexChanged(int index);
    void on_supp_file_edit_textEdited(QString txt);
    void on_save_config_button_clicked();
    void on_cancel_config_buttion_clicked();

public:
    explicit ConfigDialog(QWidget *parent, CoreEngine *core, ConfigHandler *config_handler);
    //explicit ConfigDialog(ConfigHandler *config_handler);

    ~ConfigDialog();

private:
    Ui::ConfigDialog *ui;
};

#endif // CONFIGDIALOG_H
