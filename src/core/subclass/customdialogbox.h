#ifndef CUSTOMDIALOGBOX_H
#define CUSTOMDIALOGBOX_H

#include <QDialog>
#include <QString>
#include <QDeclarativeView>
#include <QDeclarativeContext>
#include <QObject>
#include <QPoint>
#include <QCursor>

class CustomDialogBoxInterface;

class CustomDialogBox : public QDialog
{
    Q_OBJECT

    QDeclarativeView *view;
    QDeclarativeContext *context;
    CustomDialogBoxInterface *dialog_interface;

public:
    explicit CustomDialogBox(QWidget *parent = 0);

    void showDialogBox(const QString title, const QString message,QWidget *parent = 0);

    inline QDeclarativeView* getView() { return this->view; };

signals:

public slots:


};

class CustomDialogBoxInterface : public QObject
{
    Q_OBJECT

    CustomDialogBox *parent;
    QString *title;
    QString *message;
    QPoint *main_pos;

    Q_PROPERTY(QString title READ getTitle NOTIFY titleChanged )
    Q_PROPERTY(QString message READ getMessage NOTIFY messageChanged )

    inline const QString getTitle() const { return *this->title; }
    inline const QString getMessage() { return *this->message; }


public:
    explicit CustomDialogBoxInterface(CustomDialogBox * parent);

    inline void setTitle(QString title) { *this->title = title; }
    inline void setMessage(QString message) { *this->message = message; }

public slots:

    /*called when ok button where pressed*/
    void ok();
    void setDialogPos();

signals:

    void titleChanged();
    void messageChanged();
    void okButtonPressed();

};


#endif // CUSTOMDIALOGBOX_H
