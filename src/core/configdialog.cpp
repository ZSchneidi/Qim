#include "configdialog.h"
#include "ui_configdialog.h"

ConfigDialog::ConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigDialog)
{
    ui->setupUi(this);

    //this->main_background_color = QColor;
}

ConfigDialog::~ConfigDialog()
{
    delete ui;
}
