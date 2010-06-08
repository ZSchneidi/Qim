#include "coreengine.h"

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

#include "imagehandler.h"
#include "manager/thememanager.h"
#include "manager/pluginmmanager.h"

/*The Core Engine is declared in namespace Core*/

CoreEngine::CoreEngine(QWidget *parent) : 
    QMainWindow(parent)
{

    image_label = new QLabel;
    image_label->setAlignment(Qt::AlignCenter);
    image_label->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
    image_label->setText(tr("no picture loaded"));
    image_area = new QScrollArea;
    image_area->setWidget(image_label);
    image_area->setAlignment(Qt::AlignCenter);

    setAcceptDrops(true);
    setCentralWidget(image_area);
    showMaximized();

    buildActions();
    buildMenu();

    image_handler = new ImageHandler;
    theme_manager = new ThemeManager(this);

}

void CoreEngine::open()
{
    QString file = QFileDialog::getOpenFileName(this,tr("open file"),QDir::currentPath());
    if(!file.isEmpty())
        {
        image_handler->setCurrImage(file);
        //QImage image(file);
        if (image_handler->CurImage().isNull())
            {
            QMessageBox::information(this, tr("Qim - error report"),
                                     tr("Can't convert to QImage."));
            return;
            }

        image_handler->scaleImage((width()),(height()-40));
        image_label->setPixmap(QPixmap::fromImage(image_handler->CurImage()));
        image_label->adjustSize();
        return;
        }
    QMessageBox::information(this, tr("Qim - error report"),
                             tr("Can't load file!"));
}

void CoreEngine::open(QString filepath)
{
    if(!filepath.isEmpty())
        {
        image_handler->setCurrImage(filepath);
        if (image_handler->CurImage().isNull())
            {
            QMessageBox::information(this, tr("Qim - error report"),
                                     tr("Can't convert to QImage."));
            return;
            }
        image_handler->scaleImage((width()),(height()-40));

        image_label->setPixmap(QPixmap::fromImage(image_handler->CurImage()));
        image_label->adjustSize();
        return;
        }
    QMessageBox::information(this, tr("Qim - error report"),
                             tr("Can't load file!"));
}

void CoreEngine::zoomIn()
{

}

void CoreEngine::zoomOut()
{

}

void CoreEngine::buildActions()
{
    /*this creates the action in the menubar
      the tr() function is used for translation in internationalized apps
    */
    open_action = new QAction(tr("&Open"),this);
    open_action->setShortcut(QKeySequence::Open);
    connect(open_action , SIGNAL(triggered()), this, SLOT(open()));

    exit_action = new QAction(tr("&Exit"),this);
    exit_action->setShortcut(QKeySequence::Quit);
    connect(exit_action, SIGNAL(triggered()), this, SLOT(close()));

    /*the aboutQT() function is a build in dialog*/
    about_qt_qction = new QAction(tr("About &Qt"), this);
    connect(about_qt_qction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void CoreEngine::buildMenu()
{
    fileMenu = new QMenu(tr("&File"),this);
    fileMenu->addAction(open_action);
    fileMenu->addSeparator();
    fileMenu->addAction(exit_action);

    helpMenu = new QMenu(tr("&Help"),this);
    helpMenu->addAction(about_qt_qction);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(helpMenu);
}

void CoreEngine::dropEvent(QDropEvent *event)
{
    /*the dropEvent is emitted whenever a file is dropped by the user over the main widget*/
    if( event && event->mimeData())
        {
        /*extract the mimeData from the drop*/
        const QMimeData *data = event->mimeData();
        /*to keep it simple I only ask for urls in the mimedata because Qt has some issues with
          image mime data. So I used only the file url to call an open with the filepath as parameter
          this should be much more plattform independent
        */
        if(data->hasUrls())
            {
            QList<QUrl> urls = data->urls();
            if(urls.isEmpty()) return;
            QString filepath = urls.first().toLocalFile();
            open(filepath);
            }
        }
}

void CoreEngine::dragEnterEvent(QDragEnterEvent *event)
{
    /*the dragEnterEvent is also needed to implement the Drag&Drop feature*/
    qDebug() << "enter draging";
    const QMimeData* md = event->mimeData();
    if( event && (md->hasImage() ||
                  md->hasUrls() || md->hasText()))
        event->acceptProposedAction();
}

void CoreEngine::openFromArgument(char *file)
{
    QString filepath = (QString)file;
    open(filepath);
}

void CoreEngine::wheelEvent(QWheelEvent *event)
{
    if (!event->modifiers())
        {
    if (event->delta() < 0 )
        qDebug() << "navigate forward";
    else if (event->delta() > 0)
        qDebug() << "navigate backward";
        }
    else if (event->modifiers() == Qt::ControlModifier)
        {
        if (event->delta() < 0 )
            {
            qDebug() << "zoom Out";
            zoomIn();
            }
        else if (event->delta() > 0)
            {
            qDebug() << "zoom In";
            zoomOut();
            }
        }
}

CoreEngine::~CoreEngine()
{

}
