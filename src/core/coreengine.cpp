#include "coreengine.h"

#define QIMVISLAYERFILE "visuallayer/QimVisualLayer.qml"
#define QIMDEFLAYERFILE "visuallayer/QimDefaultLayer.qml"
#define SCALEFACTORX 0.1
#define SCALEFACTORY 0.1

/*
 *The core engine is the major class which operates with all handler classes.
 */
CoreEngine::CoreEngine(QWidget *parent) :
        QMainWindow(parent)
{
    //test
    this->curr_qml_index = 0;

    this->default_title = "Qim";
    //setWindowIcon(QIcon("theme/icon/qim.icon-256.png"));

    //setWindowState(Qt::WindowFullScreen);

    /*extension objects instantiation*/
    /*initialize the image handler object which provides the image and directory data*/
    this->image_handler = new ImageHandler;

    /*initialize the styling manager*/
    this->theme_manager = new ThemeManager(this);

    /*initialize the info handler object which contains all kinds of information about the shown image*/
    this->file_info_handler = new FileInfoHandler(this);

    /*this object is the interface object between c++ logic layer and the qml ui layer*/
    qml_interface = new QmlInterface(this);

    /*instatiate and load the qml declarative ui into the qml viewer*/
    this->visual_qml_view = new QDeclarativeView;
    //visual_qml_view.acceptDrops();

    /*initialize the context with the root context of the qml viewer*/
    this->context = this->visual_qml_view->rootContext();
    /*define imageDataModel as a variant of the data list in the qml context*/

    /*set the source of the default qim layer qml file */
    this->visual_qml_view->setSource(QUrl(QIMDEFLAYERFILE));
    /*this fills the parent application window with the qml view*/
    this->visual_qml_view->setResizeMode(QDeclarativeView::SizeRootObjectToView);

    /*the zooming feature scales the image by the scale factor*/
    this->scale_factor_x = SCALEFACTORX;
    this->scale_factor_y = SCALEFACTORY;

    /*set-up the main window*/
    this->setCentralWidget(visual_qml_view);
    this->setAcceptDrops(true);
    this->showMaximized();

    this->buildActions();
    this->buildMenu();

    //this->open("C:/Users/Public/Pictures/Sample Pictures/Desert.jpg");
    //this->open("N:/Projekte/Qt/Qim/src/demo-data/demo-2.jpg");

}

/*setUpQml will be called when an image was loaded and is used to define the data model for the qml view*/
void CoreEngine::setUpQml()
{
    //qmlRegisterType<QmlInterface>("QmlInterface", 1, 0, "QmlInterface");

    this->context->setContextProperty("imageDataModel", QVariant::fromValue(imageDataModelList));
//qDebug() << "interface index " << this->qml_interface->currIndex();
    this->context->setContextProperty("qmlInterface", this->qml_interface );

    //this->context->setContextProperty("qmlInterface", new QmlInterface(this) );
    this->context->setContextProperty("icolor", QColor(Qt::red) );


    /*set the source qml file */
    this->visual_qml_view->setSource(QUrl(QIMVISLAYERFILE));
    //this->visual_qml_view->setResizeMode(QDeclarativeView::SizeRootObjectToView);

}

void CoreEngine::open()
{
    QString file = QFileDialog::getOpenFileName(this,tr("open file"),QDir::currentPath());
    if(!file.isEmpty())
    {
        this->image_handler->loadImage(file);
        this->curr_qml_index = this->image_handler->getCurFileIndex();
        qDebug() << "index: " << this->curr_qml_index;
        this->qml_interface->updateQmlIndex(this->curr_qml_index);
        /*image data initialization to get all image data to qml*/
        this->image_handler->initImageDataModel(this->imageDataModelList);
        this->setUpQml();
        /*the file information has to be updated before scaling or manipulate the image otherwise */
        //this->file_info_handler->updateFileInfo(this->image_handler->getCurImageFileInfo(),this->image_handler->getCurImage());
        if (this->image_handler->getCurImage().isNull())
        {
            QMessageBox::information(this, tr("Qim - error report"),
                                     tr("Can't convert to QImage."));
            return;
        }
        this->image_handler->scaleImage((width()),(height()-40));
        this->updateMainTitle(this->image_handler->getTitleStr());

        return;
    }
    QMessageBox::information(this, tr("Qim - error report"),
                             tr("Can't load file!"));
}

void CoreEngine::open(QString filepath)
{
    if(!filepath.isEmpty())
    {
        this->image_handler->loadImage(filepath);
        this->curr_qml_index = this->image_handler->getCurFileIndex();
        this->qml_interface->updateQmlIndex(this->curr_qml_index);
        /*image data initialization to get all image data to qml*/
        this->image_handler->initImageDataModel(this->imageDataModelList);
        this->setUpQml();
        /*the file information has to be updated before scaling or manipulate the image otherwise */
        this->file_info_handler->updateFileInfo(this->image_handler->getCurImageFileInfo(),
                                                this->image_handler->getCurImage());
        if (this->image_handler->getCurImage().isNull())
        {
            QMessageBox::information(this, tr("Qim - error report"),
                                     tr("Can't convert to QImage."));
            return;
        }
        this->image_handler->scaleImage((width()),(height()-40));
        this->updateMainTitle(image_handler->getTitleStr());

        return;
    }
    QMessageBox::information(this, tr("Qim - error report"),
                             tr("Can't load file!"));
}

void CoreEngine::updateMainTitle(QString titlestr)
{
    QString newtitle = this->default_title;
    newtitle.append(" - ");
    this->setWindowTitle(newtitle.append(titlestr));
}

void CoreEngine::zoomIn()
{
    //image_viewport->zoomIn(scale_factor_x,scale_factor_y);
}

void CoreEngine::zoomOut()
{
    //image_viewport->zoomOut(scale_factor_x,scale_factor_y);
}

void CoreEngine::showInfo()
{
    if(!this->file_info_handler->isVisible())
    {
        this->file_info_handler->show();
    }
}

void CoreEngine::closeInfo()
{
    if(this->file_info_handler->isVisible())
    {
        this->file_info_handler->close();
    }
}

void CoreEngine::navigateForward()
{
    if(this->image_handler->isSetDir)
    {
        if(this->image_handler->loadNextImage())
        {
            this->curr_qml_index = this->image_handler->getCurFileIndex();
            /*the file information has to be updated before scaling or manipulate the image otherwise */
            //this->file_info_handler->updateFileInfo(this->image_handler->getCurImageFileInfo(),
            //                                        this->image_handler->getCurImage());
            //this->image_handler->scaleImage(this->width(), this->height() - 40);
            this->updateMainTitle(this->image_handler->getTitleStr());
            //context->setContextProperty("index",++index);
            //this->curr_qml_index++;
            //this->qml_interface->incrementIndex();

            //context->setContextProperty("index",qml_interface->index);

            this->qml_interface->updateQmlIndex(this->curr_qml_index);
        }
    }
}

void CoreEngine::navigateBackward()
{
    if(this->image_handler->isSetDir)
    {
        if(this->image_handler->loadPrevImage())
        {
            this->curr_qml_index = this->image_handler->getCurFileIndex();
            /*the file information has to be updated before scaling or manipulate the image otherwise */
            //this->file_info_handler->updateFileInfo(this->image_handler->getCurImageFileInfo(),
            //                                        this->image_handler->getCurImage());
            //this->image_handler->scaleImage(width(), height() - 40);
            this->updateMainTitle(this->image_handler->getTitleStr());
            //this->curr_qml_index--;
            //this->qml_interface->decrementIndex();
            //context->setContextProperty("index",qml_interface->index);
            this->qml_interface->updateQmlIndex(this->curr_qml_index);
        }
    }
}

void CoreEngine::buildActions()
{
    /*this creates the action in the menubar
      the tr() function is used for translation in internationalized apps
    */
    this->open_action = new QAction(tr("&Open"),this);
    this->open_action->setShortcut(QKeySequence::Open);
    this->connect(this->open_action , SIGNAL(triggered()), this, SLOT(open()));

    this->exit_action = new QAction(tr("&Exit"),this);
    this->exit_action->setShortcut(QKeySequence::Quit);
    this->connect(this->exit_action, SIGNAL(triggered()), this, SLOT(close()));

    this->show_file_info = new QAction(tr("&Show Info"),this);
    this->connect(this->show_file_info, SIGNAL(triggered()), this, SLOT(showInfo()));

    this->close_file_info = new QAction(tr("&Close Info"),this);
    this->connect(this->close_file_info, SIGNAL(triggered()), this, SLOT(closeInfo()));

    /*the aboutQT() function is a build in dialog*/
    this->about_qt_qction = new QAction(tr("About &Qt"), this);
    this->connect(this->about_qt_qction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void CoreEngine::buildMenu()
{
    this->fileMenu = new QMenu(tr("&File"),this);
    this->fileMenu->addAction(this->open_action);
    this->fileMenu->addSeparator();
    this->fileMenu->addAction(this->exit_action);

    this->helpMenu = new QMenu(tr("&Help"),this);
    this->helpMenu->addAction(this->show_file_info);
    this->helpMenu->addAction(this->about_qt_qction);

    this->contextMenu = new QMenu;

    this->menuBar()->addMenu(this->fileMenu);
    this->menuBar()->addMenu(this->helpMenu);
}

void CoreEngine::dragEnterEvent(QDragEnterEvent *event)
{
    /*the dragEnterEvent is also needed to implement the Drag&Drop feature*/
    const QMimeData* md = event->mimeData();
    if (event && (md->hasImage() || md->hasUrls() || md->hasText()))
    {
        event->acceptProposedAction();
    }
}
/*
void CoreEngine::dragMoveEvent(QDragMoveEvent *event)
{
    qDebug() << "drag move event occur";
}
*/
void CoreEngine::dropEvent(QDropEvent *event)
{
    /*the dropEvent is emitted whenever a file is dropped by the user over the main widget*/
    if(event && event->mimeData())
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

            if(urls.isEmpty())
            {
                return;
            }

            QString filepath = urls.first().toLocalFile();
            this->open(filepath);
        }
    }
}

void CoreEngine::wheelEvent(QWheelEvent *event)
{
    if (!event->modifiers())
    {
        if (event->delta() < 0 )
        {
            this->navigateForward();
        }

        else if (event->delta() > 0)
        {
            this->navigateBackward();
        }
    }
    else if (event->modifiers() == Qt::ControlModifier)
    {
        if (event->delta() > 0 )
        {
            this->zoomIn();
        }
        else if (event->delta() < 0)
        {
            this->zoomOut();
        }
    }
}

void CoreEngine::closeEvent(QCloseEvent *event)
{
    this->file_info_handler->close();
}

/*
 *the contextMenuEvent is called by systemdependent contextMenu actions
 */
/*
void CoreEngine::contextMenuEvent(QContextMenuEvent *event)
{
    //set the position of the context menu to the current position
    contextMenu->move(event->x(),event->y());
    //for now the contextMenu will be cleared before adding all needed actions
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
*/

void CoreEngine::openFromArgument(char *file)
{
    QString filepath = (QString)file;
    this->open(filepath);
}


CoreEngine::~CoreEngine()
{

}
