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

#include "confighandler.h"
#include "configdialog.h"
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

    ConfigDialog *config_dialog;
    ConfigHandler *config_handler;
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

    bool is_full_screen;

    /*QActions and QMenus*/
    QAction *open_action;
    QAction *exit_action;
    QAction *about_qt_qction;
    QAction *show_file_info;
    QAction *close_file_info;
    QAction *show_fullsreen;
    QAction *close_fullsreen;
    QAction *open_config;

    QMenu *fileMenu;
    QMenu *helpMenu;
    QMenu *contextMenu;

    /*build Actions and Menu is obsolete when using qml only*/
    void buildActions();
    void buildMenu();
    /*set the Window title to titlestr which is now delegated to qml Titlebar*/
    void updateMainTitle(QString titlestr);
    /*used to define the MainWindow apearance*/
    void setUpMainWindow();
    /*used to define the QML environment*/
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
    /*the resizeEvent is used to delegate the mainwindow size to the qml interface whenever the
     *main window is changing its size
     */
    //void resizeEvent(QResizeEvent *event);
    /*called on an rightclick to open the widget based context menu
     *qml context menu is implemented seperatly
     */
    //void contextMenuEvent(QContextMenuEvent *event);

private slots:

    void openConfig();
    void zoomIn();
    void zoomOut();
    void showInfo();
    void closeInfo();
    void navigateForward();
    void navigateBackward();
    void toggleFullScreen();
    void about();

    void open();
    void open(QString filepath);


public:

    /*enum declaration*/
    /*the CoreAction enum is used to call QActions from QmlInterface::sendCoreAction()
     */
    enum CoreAction {OPEN,CLOSE,ABOUT,FULLSCREEN,CONFIG};

    CoreEngine(QWidget *parent = 0);
    ~CoreEngine();

    void callCoreAction(CoreAction action);
    void openFromArgument(char *file);
    void setQmlIndex(int index);
    inline int currQmlIndex() { return this->curr_qml_index; }

};

#endif // COREENGINE_H
