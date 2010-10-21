#ifndef CUSTOMDIALOGBOX_H
#define CUSTOMDIALOGBOX_H

#include <QDialog>
#include <QString>
#include <QDeclarativeView>
#include <QDeclarativeContext>
#include <QObject>


class CustomDialogBox : public QDialog
{
    Q_OBJECT
public:
    explicit CustomDialogBox(QWidget *parent = 0);

    static void showDialogBox(const QString title, const QString message,QWidget *parent = 0);

signals:

public slots:


};

class CustomDialogBoxInterface : public QObject
{
    Q_OBJECT

    QString *title;
    QString *message;

    Q_PROPERTY(QString title READ getTitle NOTIFY titleChanged )
    Q_PROPERTY(QString message READ getMessage NOTIFY messageChanged )

    inline const QString getTitle() const { return *this->title; }
    inline const QString getMessage() { return *this->message; }


public:
    explicit CustomDialogBoxInterface();

    inline void setTitle(QString title) { *this->title = title; }
    inline void setMessage(QString message) { *this->message = message; }

public slots:

    /*called when ok button where pressed*/
    void ok();

signals:

    void titleChanged();
    void messageChanged();
    void okButtonPressed();

};


#endif // CUSTOMDIALOGBOX_H
