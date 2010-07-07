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
#include "fileinfohandler.h"
#include "manager/thememanager.h"
#include "manager/pluginmmanager.h"

/*The Core Engine is declared in namespace Core*/

CoreEngine::CoreEngine(QWidget *parent) : 
    QMainWindow(parent)
{
    default_title = "Qim";


    image_label = new QLabel;
    image_label->setAlignment(Qt::AlignCenter);
    image_label->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
    image_label->setText(tr("no picture loaded"));

    image_area = new QScrollArea;
    image_area->setWidget(image_label);
    image_area->setAlignment(Qt::AlignCenter);


    scale_factor_x = 0.1;
    scale_factor_y = 0.1;

    image_scene = new QGraphicsScene;
    image_scene->addText(tr("no picture loaded"));
    image_view = new QGraphicsView;
    image_view->setScene(image_scene);
    image_view->setDragMode(QGraphicsView::ScrollHandDrag);
    image_view->show();

    setCentralWidget(image_view);

    setAcceptDrops(true);
    //setCentralWidget(image_area);

    showMaximized();

    buildActions();
    buildMenu();

    image_handler = new ImageHandler;
    theme_manager = new ThemeManager(this);
    file_info_handler = new FileInfoHandler(this);
    /*to define how the file info dialog behaves you can use the WindowFlags*/
    file_info_handler->setWindowFlags(Qt::Dialog);

}

void CoreEngine::open()
{
    QString file = QFileDialog::getOpenFileName(this,tr("open file"),QDir::currentPath());
    if(!file.isEmpty())
        {
        image_handler->loadImage(file);
        /*the file information has to be updated before scaling or manipulate the image otherwise */
        file_info_handler->updateFileInfo(image_handler->getCurImageFileInfo(),image_handler->getCurImage());
        if (image_handler->getCurImage().isNull())
            {
            QMessageBox::information(this, tr("Qim - error report"),
                                     tr("Can't convert to QImage."));
            return;
            }
        image_handler->scaleImage((width()),(height()-40));
        //image_label->setPixmap(QPixmap::fromImage(image_handler->getCurImage()));
        //image_label->adjustSize();
        image_scene->clear();
        image_scene->addPixmap(QPixmap::fromImage(image_handler->getCurImage()));
        updateMainTitle(image_handler->getTitleStr());

        return;
        }
    QMessageBox::information(this, tr("Qim - error report"),
                             tr("Can't load file!"));
}

void CoreEngine::open(QString filepath)
{
    if(!filepath.isEmpty())
        {
        image_handler->loadImage(filepath);
        /*the file information has to be updated before scaling or manipulate the image otherwise */
        file_info_handler->updateFileInfo(image_handler->getCurImageFileInfo(),image_handler->getCurImage());
        if (image_handler->getCurImage().isNull())
            {
            QMessageBox::information(this, tr("Qim - error report"),
                                     tr("Can't convert to QImage."));
            return;
            }
        image_handler->scaleImage((width()),(height()-40));
        //image_label->setPixmap(QPixmap::fromImage(image_handler->getCurImage()));
        //image_label->adjustSize();
        image_scene->clear();
        image_scene->addPixmap(QPixmap::fromImage(image_handler->getCurImage()));
        updateMainTitle(image_handler->getTitleStr());
        return;
        }
    QMessageBox::information(this, tr("Qim - error report"),
                             tr("Can't load file!"));
}

void CoreEngine::updateMainTitle(QString titlestr)
{
    QString newtitle = default_title;
    newtitle.append(" - ");
    setWindowTitle(newtitle.append(titlestr));

}

void CoreEngine::zoomIn()
{
    image_view->scale((1.0+scale_factor_x),(1.0+scale_factor_y));
}

void CoreEngine::zoomOut()
{
    image_view->scale((1.0-scale_factor_x),(1.0-scale_factor_y));
}

void CoreEngine::showInfo()
{
    if(!file_info_handler->isVisible())
    {
        file_info_handler->show();
    }
}

void CoreEngine::closeInfo()
{
    if(file_info_handler->isVisible())
    {
        file_info_handler->close();
    }
}

void CoreEngine::navigateForward()
{
    if(image_handler->isSetDir)
    {
        if(image_handler->loadNextImage())
        {
            /*the file information has to be updated before scaling or manipulate the image otherwise */
            file_info_handler->updateFileInfo(image_handler->getCurImageFileInfo(),image_handler->getCurImage());
            image_handler->scaleImage((width()),(height()-40));
            //image_label->setPixmap(QPixmap::fromImage(image_handler->getCurImage()));
            //image_label->adjustSize();
            image_scene->clear();
            image_scene->addPixmap(QPixmap::fromImage(image_handler->getCurImage()));
            updateMainTitle(image_handler->getTitleStr());
        }
    }
}

void CoreEngine::navigateBackward()
{
    if(image_handler->isSetDir)
    {
        if(image_handler->loadPrevImage())
        {
            /*the file information has to be updated before scaling or manipulate the image otherwise */
            file_info_handler->updateFileInfo(image_handler->getCurImageFileInfo(),image_handler->getCurImage());
            image_handler->scaleImage((width()),(height()-40));
            //image_label->setPixmap(QPixmap::fromImage(image_handler->getCurImage()));
            //image_label->adjustSize();
            image_scene->clear();
            image_scene->addPixmap(QPixmap::fromImage(image_handler->getCurImage()));
            updateMainTitle(image_handler->getTitleStr());
        }
    }
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


    show_file_info = new QAction(tr("&Show Info"),this);
    connect(show_file_info, SIGNAL(triggered()), this, SLOT(showInfo()));

    close_file_info = new QAction(tr("&Close Info"),this);
    connect(close_file_info, SIGNAL(triggered()), this, SLOT(closeInfo()));

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
    helpMenu->addAction(show_file_info);
    helpMenu->addAction(about_qt_qction);

    contextMenu = new QMenu;

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(helpMenu);
}

void CoreEngine::dragEnterEvent(QDragEnterEvent *event)
{
    /*the dragEnterEvent is also needed to implement the Drag&Drop feature*/
    const QMimeData* md = event->mimeData();
    if( event && (md->hasImage() ||
                  md->hasUrls() || md->hasText()))
        event->acceptProposedAction();
}

void CoreEngine::dropEvent(QDropEvent *event)
{
    qDebug() << "drop occur";
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

void CoreEngine::wheelEvent(QWheelEvent *event)
{
    if (!event->modifiers())
    {
        if (event->delta() > 0 )
        {
            navigateForward();
        }

        else if (event->delta() < 0)
        {
            navigateBackward();
        }
    }
    else if (event->modifiers() == Qt::ControlModifier)
    {
        if (event->delta() > 0 )
        {
            zoomIn();
        }
        else if (event->delta() < 0)
        {
            zoomOut();
        }
    }
}

void CoreEngine::closeEvent(QCloseEvent *event)
{
    file_info_handler->close();
}

/*
 *the contextMenuEvent is called by systemdependent contextMenu actions
 */
void CoreEngine::contextMenuEvent(QContextMenuEvent *event)
{
    /*set the position of the context menu to the current position*/
    contextMenu->move(event->x(),event->y());
    /*for now the contextMenu will be cleared before adding all needed actions*/
    contextMenu->clear();
    if(file_info_handler->isVisible())
    {
        contextMenu->addAction(close_file_info);
    }
    else
    {
        contextMenu->addAction(show_file_info);
    }
    contextMenu->show();
}

void CoreEngine::openFromArgument(char *file)
{
    QString filepath = (QString)file;
    open(filepath);
}



CoreEngine::~CoreEngine()
{

}
