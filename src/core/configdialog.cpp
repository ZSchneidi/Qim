#include "configdialog.h"
#include "ui_configdialog.h"

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

    /*the language combo box items text must suit with the language strings from config resp. QLocal language
     *if you're going to change these items make sure they work together with the config or QLocal::language
     */
    this->ui->lang_combo_box->addItem("Default");
    this->ui->lang_combo_box->addItem("English");
    this->ui->lang_combo_box->addItem("German");

    /*the theme combo box should be loaded by an theme handler which isn't implemented yet*/
    this->ui->theme_combo_box->addItem("Default");
    this->ui->theme_combo_box->addItem("White");
    this->ui->theme_combo_box->addItem("Dark");


    this->back_picker = new BackgroundColorPicker(this);

    QRect rect = QRect(70,70,200,200);
    this->back_picker->setGeometry(rect);
    connect(this->back_picker,SIGNAL(colorChanged(QColor)),this,SLOT(changeBackColor(QColor)));

    this->ui->background_layout->addWidget(this->back_picker);


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
    /*set the theme combo box to the theme defined in the config*/
    this->ui->theme_combo_box->setCurrentIndex(this->ui->theme_combo_box->findText(this->config_handler->mainTheme(),Qt::MatchFixedString));

    /*set the supported file string into the line edit widget*/
    this->ui->supp_file_edit->setText(this->config_handler->supFileFormatStr());
    /*set the background opacity slider to the config value*/
    this->ui->background_opacity->setValue(this->config_handler->mainBackgroundOpacity());
    this->back_picker->updateLabelColor(this->config_handler->mainBackgroundColor());
    this->ui->check_advanced_ui->setChecked(this->config_handler->isActiveAdvancedUI());
    this->ui->check_image_list->setChecked(this->config_handler->isActiveQmlList());
    this->ui->check_image_preload->setChecked(this->config_handler->isActiveImagePreload());
    this->ui->check_image_scaling->setChecked(this->config_handler->isActiveImageScale());
    this->ui->check_image_smooth->setChecked(this->config_handler->isActiveImageSmooth());
    this->ui->check_image_streching->setChecked(this->config_handler->isActiveImageStrech());
    this->ui->check_invert_nav->setChecked(this->config_handler->invertNavDirection());
    this->ui->check_invert_zooming->setChecked(this->config_handler->invertZoomDirection());
    this->ui->check_load_fileinfo->setChecked(this->config_handler->isActiveFileInfo());
    this->ui->check_load_subdir_files->setChecked(this->config_handler->includeSubdirFiles());
    this->ui->check_load_subdir->setChecked(this->config_handler->includeSubdir());
    this->ui->check_nav_loop->setChecked(this->config_handler->isActiveNavLoop());
    this->ui->check_secure_nav->setChecked(this->config_handler->isActiveSecureNav());
    this->ui->check_shadow_box->setChecked(this->config_handler->isActiveShadowBox());
    this->ui->check_start_fullscreen->setChecked(this->config_handler->startFullScreen());
    this->ui->check_activate_plugin->setChecked(this->config_handler->isActivePlugIn());


}

void ConfigDialog::on_save_config_button_clicked()
{
    QMap<QString, QString>::const_iterator i = this->temp_config_map->constBegin();
    while (i != this->temp_config_map->constEnd()) {
        QString key = QString(i.key());
        QString value = QString(i.value());
        if(value != "")
        {
            //qDebug() << "send new config : " << key << ":" << value;
            this->config_handler->getConfigMap()->insert(key,value);
        }
        ++i;
    }
    this->close();
}

void ConfigDialog::on_cancel_config_buttion_clicked()
{
    this->temp_config_map->clear();
    this->close();
}

/*update the selected language whenever the combobox changes its index*/
void ConfigDialog::on_lang_combo_box_currentIndexChanged(int index)
{
    if(this->init_config_started)
    {
    this->temp_config_map->insert(MAIN_LANG_SWITCH,this->ui->lang_combo_box->itemText(index).toUpper());
    }
}

/*update the supported file string whenever the lineedit changes its text*/
void ConfigDialog::on_supp_file_edit_textEdited(QString txt)
{
    if(this->init_config_started)
    {
        this->temp_config_map->insert(SUPP_FILE_FORMAT_SWITCH,txt);
    }
}

void ConfigDialog::on_check_advanced_ui_stateChanged(int state)
{
    if(this->init_config_started)
    {
        this->temp_config_map->insert(ADVANCED_UI_SWITCH,this->convStateToBoolStr(state));
    }
}

void ConfigDialog::on_check_image_list_stateChanged(int state)
{

}

void ConfigDialog::on_check_image_preload_stateChanged(int state)
{
    if(this->init_config_started)
    {
        this->temp_config_map->insert(IMAGE_PRELOAD_SWITCH,this->convStateToBoolStr(state));
    }
}

void ConfigDialog::on_check_image_scaling_stateChanged(int state)
{

}

void ConfigDialog::on_check_image_smooth_stateChanged(int state)
{

}

void ConfigDialog::on_check_image_streching_stateChanged(int state)
{

}

void ConfigDialog::on_check_invert_nav_stateChanged(int state)
{

}

void ConfigDialog::on_check_invert_zooming_stateChanged(int state)
{

}

void ConfigDialog::on_check_load_fileinfo_stateChanged(int state)
{

}

void ConfigDialog::on_check_load_subdir_files_stateChanged(int state)
{

}

void ConfigDialog::on_check_load_subdir_stateChanged(int state)
{

}

void ConfigDialog::on_check_nav_loop_stateChanged(int state)
{

}
void ConfigDialog::on_check_secure_nav_stateChanged(int state)
{

}

void ConfigDialog::on_check_shadow_box_stateChanged(int state)
{

}

void ConfigDialog::on_check_start_fullscreen_stateChanged(int state)
{

}

void ConfigDialog::on_theme_combo_box_currentIndexChanged(int index)
{

}

void ConfigDialog::on_check_activate_plugin_stateChanged(int state)
{

}


/*update the opacity value whenever the opacity slider changes its value*/
void ConfigDialog::on_background_opacity_valueChanged(int value)
{
    this->ui->opacity_value->setText(QString::number(value));
    this->temp_config_map->insert(BACKGROUND_OPACITY_SWITCH,QString::number(value));
}

/*custom signal emited by the backgroundcolorpicker subclass
 *will be emitted whenever a new background color was selected
 */
void ConfigDialog::changeBackColor(const QColor color)
{
    this->temp_config_map->insert(BACKGROUND_COLOR_SWITCH,color.name().toUpper());
}



QString ConfigDialog::convStateToBoolStr(int state)
{
    if(state == 0)
        return "FALSE";
    else if (state == 2)
        return "TRUE";
    else
        return "";
}

ConfigDialog::~ConfigDialog()
{
    delete ui;
}










