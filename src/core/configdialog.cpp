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

    this->init_config_done = false;

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

    /*temporary disable all config elements with no semantic relevance*/
    this->ui->check_raw_format->setDisabled(true);
    this->ui->check_image_preload->setDisabled(true);
    this->ui->check_secure_nav->setDisabled(true);
    this->ui->check_activate_plugin->setDisabled(true);
    this->ui->check_image_list->setDisabled(true);
    this->ui->check_image_scaling->setDisabled(true);
    this->ui->check_image_smooth->setDisabled(true);
    this->ui->check_image_streching->setDisabled(true);
    this->ui->check_invert_nav->setDisabled(true);
    this->ui->check_invert_zooming->setDisabled(true);
    this->ui->check_load_fileinfo->setDisabled(true);
    this->ui->check_load_subdir->setDisabled(true);
    this->ui->check_load_subdir_files->setDisabled(true);
    this->ui->check_nav_loop->setDisabled(true);
    this->ui->check_shadow_box->setDisabled(true);
    this->ui->check_advanced_ui->setDisabled(true);
    this->ui->theme_combo_box->setDisabled(true);
    this->ui->lang_combo_box->setDisabled(true);

}

void ConfigDialog::showEvent(QShowEvent *)
{
    this->initConfig();
}

void ConfigDialog::initConfig()
{
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
    this->ui->file_blacklist_edit->setText(this->config_handler->FileFormatBlacklistStr());
    /*set the background opacity slider to the config value*/
    this->ui->background_opacity->setValue(this->config_handler->mainBackgroundOpacity());
    this->ui->opacity_value->setText(QString::number(this->config_handler->mainBackgroundOpacity()));
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
    this->ui->check_raw_format->setChecked(this->config_handler->isActiveRawSupport());
    this->ui->check_activate_plugin->setChecked(this->config_handler->isActivePlugIn());

    this->init_config_done = true;
}

void ConfigDialog::on_save_config_button_clicked()
{
    this->config_handler->transactNewConfig(this->temp_config_map);
    this->temp_config_map->clear();
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
    if(this->init_config_done)
    {
        this->temp_config_map->insert(MAIN_LANG_SWITCH,this->ui->lang_combo_box->itemText(index).toUpper());
    }
}
void ConfigDialog::on_theme_combo_box_currentIndexChanged(int index)
{
    if(this->init_config_done)
    {
        this->temp_config_map->insert(SHADOWBOX_SWITCH,this->ui->theme_combo_box->itemText(index).toUpper());
    }
}

/*update the supported file string whenever the lineedit changes its text*/
void ConfigDialog::on_file_blacklist_edit_textEdited(QString txt)
{
    if(this->init_config_done)
    {
        this->temp_config_map->insert(FILE_FORMAT_BLACKLIST_SWITCH,txt);
    }
}

void ConfigDialog::on_check_advanced_ui_stateChanged(int state)
{
    if(this->init_config_done)
    {
        this->temp_config_map->insert(ADVANCED_UI_SWITCH,this->convStateToBoolStr(state));
    }
}

void ConfigDialog::on_check_image_list_stateChanged(int state)
{
    if(this->init_config_done)
    {
        this->temp_config_map->insert(QML_LIST_SWITCH,this->convStateToBoolStr(state));
    }
}

void ConfigDialog::on_check_image_preload_stateChanged(int state)
{
    if(this->init_config_done)
    {
        this->temp_config_map->insert(IMAGE_PRELOAD_SWITCH,this->convStateToBoolStr(state));
    }
}

void ConfigDialog::on_check_image_scaling_stateChanged(int state)
{
    if(this->init_config_done)
    {
        this->temp_config_map->insert(IMAGE_SCALE_SWITCH,this->convStateToBoolStr(state));
    }
}

void ConfigDialog::on_check_image_smooth_stateChanged(int state)
{
    if(this->init_config_done)
    {
        this->temp_config_map->insert(IMAGE_SMOOTH_SWITCH,this->convStateToBoolStr(state));
    }
}

void ConfigDialog::on_check_image_streching_stateChanged(int state)
{
    if(this->init_config_done)
    {
        this->temp_config_map->insert(IMAGE_STRECH_SWITCH,this->convStateToBoolStr(state));
    }
}

void ConfigDialog::on_check_invert_nav_stateChanged(int state)
{
    if(this->init_config_done)
    {
        this->temp_config_map->insert(INVERT_NAV_SWITCH,this->convStateToBoolStr(state));
    }
}

void ConfigDialog::on_check_invert_zooming_stateChanged(int state)
{
    if(this->init_config_done)
    {
        this->temp_config_map->insert(INVERT_ZOOM_SWITCH,this->convStateToBoolStr(state));
    }
}

void ConfigDialog::on_check_load_fileinfo_stateChanged(int state)
{
    if(this->init_config_done)
    {
        this->temp_config_map->insert(FILE_INFO_SWITCH,this->convStateToBoolStr(state));
    }
}

void ConfigDialog::on_check_load_subdir_files_stateChanged(int state)
{
    if(this->init_config_done)
    {
        this->temp_config_map->insert(SUBDIR_FILES_SWITCH,this->convStateToBoolStr(state));
    }
}

void ConfigDialog::on_check_load_subdir_stateChanged(int state)
{
    if(this->init_config_done)
    {
        this->temp_config_map->insert(SUBDIR_SWITCH,this->convStateToBoolStr(state));
    }
}

void ConfigDialog::on_check_nav_loop_stateChanged(int state)
{
    if(this->init_config_done)
    {
        this->temp_config_map->insert(NAV_LOOP_SWITCH,this->convStateToBoolStr(state));
    }
}
void ConfigDialog::on_check_secure_nav_stateChanged(int state)
{
    if(this->init_config_done)
    {
        this->temp_config_map->insert(SECURE_NAV_SWITCH,this->convStateToBoolStr(state));
    }
}

void ConfigDialog::on_check_shadow_box_stateChanged(int state)
{
    if(this->init_config_done)
    {
        this->temp_config_map->insert(SHADOWBOX_SWITCH,this->convStateToBoolStr(state));
    }
}

void ConfigDialog::on_check_start_fullscreen_stateChanged(int state)
{
    if(this->init_config_done)
    {
        this->temp_config_map->insert(FULLSCREEN_SWITCH,this->convStateToBoolStr(state));
    }
}

void ConfigDialog::on_check_raw_format_stateChanged(int state)
{
    if(this->init_config_done)
    {
        this->temp_config_map->insert(RAW_SUPPORT_SWITCH,this->convStateToBoolStr(state));
    }
}

void ConfigDialog::on_check_activate_plugin_stateChanged(int state)
{
    if(this->init_config_done)
    {
        this->temp_config_map->insert(PLUGIN_SWITCH,this->convStateToBoolStr(state));
    }
}


/*update the opacity value whenever the opacity slider changes its value*/
void ConfigDialog::on_background_opacity_valueChanged(int value)
{
    if(this->init_config_done)
    {
    this->ui->opacity_value->setText(QString::number(value));
    this->temp_config_map->insert(BACKGROUND_OPACITY_SWITCH,QString::number(value));
    }
}

/*custom signal emited by the backgroundcolorpicker subclass
 *will be emitted whenever a new background color was selected
 */
void ConfigDialog::changeBackColor(const QColor color)
{
    if(this->init_config_done)
    {
    this->temp_config_map->insert(BACKGROUND_COLOR_SWITCH,color.name().toUpper());
    }
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










