#include "customdialogbox.h"
#include <QDebug>

CustomDialogBox::CustomDialogBox(QWidget *parent) :
    QDialog(parent)
{
}

void CustomDialogBox::showDialogBox(const QString title, const QString message,QWidget * parent)
{
    qDebug() << "static dialog box: " << message;
    QDeclarativeView *view = new QDeclarativeView(parent);
    QDeclarativeContext *context = view->rootContext();
    CustomDialogBoxInterface *dialog_interface = new CustomDialogBoxInterface();
    dialog_interface->setTitle(title);
    dialog_interface->setMessage(message);

    context->setContextProperty("dialogInterface", dialog_interface );

    view->setSource(QUrl::fromLocalFile("visuallayer/elements/DialogBox.qml"));
    view->setStyleSheet("background:transparent");
    view->setAttribute(Qt::WA_TranslucentBackground);
    view->setWindowFlags(Qt::FramelessWindowHint);
    view->show();

    connect(dialog_interface,SIGNAL(okButtonPressed()),view, SLOT(close()) );

}



CustomDialogBoxInterface::CustomDialogBoxInterface() :
    QObject()
{
    this->title = new QString;
    this->message = new QString;

}

void CustomDialogBoxInterface::ok() {
    emit this->okButtonPressed();
}
