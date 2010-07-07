#ifndef COREENGINE_H
#define COREENGINE_H

#include <QMainWindow>
#include <QLabel>
#include <QScrollArea>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QEvent>
#include <QImage>
#include <QString>
#include <QFileInfo>

/*
The CoreEngine namespace contais all major functionality.
For interfaces use specialized namespaces
*/

class ThemeManager;
class ImageHandler;
class FileInfoHandler;

class CoreEngine : public QMainWindow
{
    Q_OBJECT

    ImageHandler *image_handler;
    ThemeManager *theme_manager;
    FileInfoHandler *file_info_handler;

    qreal scale_factor_x;
    qreal scale_factor_y;

    /*the default_title string is the default application window title*/
    QString default_title;

    QAction *open_action;
    QAction *exit_action;
    QAction *about_qt_qction;
    QAction *show_file_info;
    QAction *close_file_info;

    QMenu *fileMenu;
    QMenu *helpMenu;
    QMenu *contextMenu;

    void buildActions();
    void buildMenu();
    void scaleImage();
    void open(QString filepath);
    void updateMainTitle(QString titlestr);

    /*the dragEnterEvent will be emit whenever the mouse cursor enters the application window*/
    void dragEnterEvent(QDragEnterEvent *event);
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

    QLabel *image_label;
    QScrollArea *image_area;

    /*testing graphicsview*/
    QGraphicsScene *image_scene;
    QGraphicsView *image_view;

    CoreEngine(QWidget *parent = 0);
    ~CoreEngine();

    void openFromArgument(char *file);

};

#endif // COREENGINE_H
