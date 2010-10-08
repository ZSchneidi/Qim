#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H
#include "confighandler.h"

#include <QDialog>
#include <QColorDialog>

namespace Ui {
    class ConfigDialog;
}

class ConfigHandler;

class ConfigDialog : public QDialog
{
    Q_OBJECT

    QColor main_background_color;
    ConfigHandler *config_handler;



public:
    explicit ConfigDialog(QWidget *parent,ConfigHandler *config_handler );
    //explicit ConfigDialog(ConfigHandler *config_handler);

    ~ConfigDialog();

private:
    Ui::ConfigDialog *ui;
};

#endif // CONFIGDIALOG_H
