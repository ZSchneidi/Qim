#include "customdialogbox.h"
#include <QDebug>

CustomDialogBox::CustomDialogBox(QWidget *parent) :
    QDialog(parent)
{
    this->view = new QDeclarativeView();
    this->dialog_interface = new CustomDialogBoxInterface(this);
    this->context = view->rootContext();
}

void CustomDialogBox::showDialogBox(const QString title, const QString message,QWidget * parent)
{
    qDebug() << "static dialog box: " << message;
    this->dialog_interface->setTitle(title);
    this->dialog_interface->setMessage(message);

    this->context->setContextProperty("dialogInterface", dialog_interface );

    this->view->setSource(QUrl::fromLocalFile("visuallayer/elements/DialogBox.qml"));
    this->view->setStyleSheet("background:transparent");
    this->view->setAttribute(Qt::WA_TranslucentBackground);
    this->view->setWindowFlags(Qt::FramelessWindowHint);
    this->view->show();

    connect(this->dialog_interface,SIGNAL(okButtonPressed()),this->view, SLOT(close()) );

}


CustomDialogBoxInterface::CustomDialogBoxInterface(CustomDialogBox *parent) :
    QObject()
{
    this->parent = parent;
    this->title = new QString;
    this->message = new QString;
    this->main_pos = new QPoint;

}

void CustomDialogBoxInterface::setDialogPos()
{
    if(this->main_pos->x()> 0 && this->main_pos->y() > 0)
    {
        int x_diff = QCursor::pos().x() - this->main_pos->x();
        int y_diff = QCursor::pos().y() - this->main_pos->y();
        //this->core->move(this->core->x()+x_diff,this->core->y()+y_diff);
        this->parent->getView()->move(this->parent->getView()->x()+x_diff,this->parent->getView()->y()+y_diff);

    }
    this->main_pos->setX( QCursor::pos().x());
    this->main_pos->setY( QCursor::pos().y());
}

void CustomDialogBoxInterface::ok() {
    emit this->okButtonPressed();
    qDebug() << "ok button pressed";
}


