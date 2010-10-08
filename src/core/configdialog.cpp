#include "configdialog.h"
#include "ui_configdialog.h"

ConfigDialog::ConfigDialog(QWidget *parent,ConfigHandler *config_handler) :
    QDialog(parent),
    ui(new Ui::ConfigDialog)
{
    ui->setupUi(this);
    this->config_handler = config_handler;

    //this->main_background_color = QColor;
}

ConfigDialog::~ConfigDialog()
{
    delete ui;
}
