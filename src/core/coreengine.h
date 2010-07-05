#ifndef COREENGINE_H
#define COREENGINE_H

#include <QMainWindow>
#include <QLabel>
#include <QScrollArea>
#include <QEvent>
#include <QImage>
#include <QString>

/*
The CoreEngine namespace contais all major functionality.
For interfaces use specialized namespaces
*/

class ThemeManager;
class ImageHandler;

class CoreEngine : public QMainWindow
{
    Q_OBJECT

    ImageHandler *image_handler;
    ThemeManager *theme_manager;

    void buildActions();
    void buildMenu();
    void scaleImage();
    void open(QString filepath);

    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void wheelEvent(QWheelEvent *event);

private slots:

    void open();
    void zoomIn();
    void zoomOut();
    void navigateForward();
    void navigateBackward();

public:

    QLabel *image_label;
    QScrollArea *image_area;

    QAction *open_action;
    QAction *exit_action;
    QAction *about_qt_qction;

    QMenu *fileMenu;
    QMenu *helpMenu;

    CoreEngine(QWidget *parent = 0);
    ~CoreEngine();

    void openFromArgument(char *file);

};

#endif // COREENGINE_H
