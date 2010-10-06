#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>
#include <QColorDialog>

namespace Ui {
    class ConfigDialog;
}

class ConfigDialog : public QDialog
{
    Q_OBJECT

    QColor main_background_color;



public:
    explicit ConfigDialog(QWidget *parent = 0);
    ~ConfigDialog();

private:
    Ui::ConfigDialog *ui;
};

#endif // CONFIGDIALOG_H
