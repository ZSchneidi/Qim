#include "configdialog.h"
#include "ui_configdialog.h"
#include <QDebug>

ConfigDialog::ConfigDialog(QWidget *parent,CoreEngine *core, ConfigHandler *config_handler) :
    QDialog(parent),
    ui(new Ui::ConfigDialog)
{
    ui->setupUi(this);
    this->config_handler = config_handler;
    this->core = core;

    this->temp_config_map = new QMap<QString, QString>;

    this->init_config_started = false;

    //this->main_background_color = QColor;

    /*the language combo box items test must suit with the language strings from config resp. QLocal language
     *if you're going to change these items make sure they work together with the config or QLocal::language
     */
    this->ui->lang_combo_box->addItem("Default");
    this->ui->lang_combo_box->addItem("English");
    this->ui->lang_combo_box->addItem("German");

}

void ConfigDialog::showEvent(QShowEvent *)
{
    this->initConfig();
    qDebug() << "initialize config dialog from config";
}

void ConfigDialog::initConfig()
{
    this->init_config_started = true;
    /*set the language combo box to the languange defined in the config*/
    QString main_lang = this->config_handler->mainLanguage();
    if(main_lang == "LOCAL")
    {
        QString local_lang = this->core->getMainLocal()->languageToString(this->core->getMainLocal()->language());
        this->ui->lang_combo_box->setCurrentIndex(this->ui->lang_combo_box->findText(local_lang));
    }
    else
    {
        this->ui->lang_combo_box->setCurrentIndex(this->ui->lang_combo_box->findText(main_lang,Qt::MatchFixedString));
    }

    /*set the supported file string into the line edit widget*/
    this->ui->supp_file_edit->setText(this->config_handler->supFileFormatStr());
}

void ConfigDialog::on_save_config_button_clicked()
{
    QMap<QString, QString>::const_iterator i = this->temp_config_map->constBegin();
    while (i != this->temp_config_map->constEnd()) {
        QString key = QString(i.key());
        QString value = QString(i.value());
        if(value != "")
            this->config_handler->getConfigMap()->insert(key,value);
        ++i;
    }
    this->close();
}

void ConfigDialog::on_cancel_config_buttion_clicked()
{
    this->temp_config_map->clear();
    this->close();
}

void ConfigDialog::on_lang_combo_box_currentIndexChanged(int index)
{
    if(this->init_config_started)
    {
    this->temp_config_map->insert(MAIN_LANG_SWITCH,this->ui->lang_combo_box->itemText(index).toUpper());
    }
}

void ConfigDialog::on_supp_file_edit_textEdited(QString txt)
{
    if(this->init_config_started)
    {
        this->temp_config_map->insert(SUPP_FILE_FORMAT_SWITCH,txt);
    }
}


ConfigDialog::~ConfigDialog()
{
    delete ui;
}
