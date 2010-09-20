#ifndef COREENGINE_H
#define COREENGINE_H

#include <QMainWindow>
#include <QEvent>
#include <QImage>
#include <QString>
#include <QFileInfo>
#include <QFileDialog>
#include <QDebug>
#include <QMimeData>
#include <QUrl>
#include <QEvent>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QWheelEvent>
#include <QMessageBox>
#include <QPixmap>
#include <QtGui>
#include <QDeclarativeView>
#include <QDeclarativeContext>
#include <QDeclarativeEngine>

#include "imagehandler.h"
#include "fileinfohandler.h"
#include "manager/thememanager.h"
#include "manager/pluginmmanager.h"
#include "imagedatamodel.h"
#include "qmlinterface.h"

class ThemeManager;
class ImageHandler;
class FileInfoHandler;
class QmlInterface;

/*CoreEngine -> ThemeManager interface see below*/

/*core engine class*/
class CoreEngine : public QMainWindow
{
    Q_OBJECT

    /*object list of image data informations to provide them via */
    QList<QObject *> imageDataModelList;
    /*qml declaritive view is used to display qml based visual layer*/
    QDeclarativeView *visual_qml_view;
    /*context for the QDeclarative environment*/
    QDeclarativeContext *context;

    /*extension objects*/

    ImageHandler *image_handler;
    ThemeManager *theme_manager;
    FileInfoHandler *file_info_handler;
    QmlInterface *qml_interface;

    /*scaling factor*/
    qreal scale_factor_x;
    qreal scale_factor_y;

    /*the default_title string is the default application window title*/
    QString default_title;

    /*index of the currently selected picture in the qml list*/
    int curr_qml_index;

    /*QActions and QMenus*/
    QAction *open_action;
    QAction *exit_action;
    QAction *about_qt_qction;
    QAction *show_file_info;
    QAction *close_file_info;
    QAction *show_fullsreen;
    QAction *close_fullsreen;

    QMenu *fileMenu;
    QMenu *helpMenu;
    QMenu *contextMenu;

    void buildActions();
    void buildMenu();
    void open(QString filepath);
    void updateMainTitle(QString titlestr);
    void setUpQml();

    /*the dragEnterEvent will be emit whenever the mouse cursor enters the application window*/
    void dragEnterEvent(QDragEnterEvent *event);
    //void dragMoveEvent(QDragMoveEvent *event);
    /*the dropEvent will be emit in the moment when the image file is droped over the application*/
    void dropEvent(QDropEvent *event);
    /*the wheelEvent will be emit whenever the mouse wheel sends a signal*/
    void wheelEvent(QWheelEvent *event);
    /*the closeEvent will be if the main window is closed*/
    void closeEvent(QCloseEvent *event);

    void contextMenuEvent(QContextMenuEvent *event);

private slots:

    void open();
    void zoomIn();
    void zoomOut();
    void showInfo();
    void closeInfo();
    void navigateForward();
    void navigateBackward();

public:

    CoreEngine(QWidget *parent = 0);
    ~CoreEngine();

    void openFromArgument(char *file);
    void setQmlIndex(int index);
    inline int currQmlIndex() { return this->curr_qml_index; }

};

#endif // COREENGINE_H
