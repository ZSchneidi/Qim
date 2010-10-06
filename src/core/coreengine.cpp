#include "coreengine.h"

#define QIMVISLAYERFILE "visuallayer/QimVisualLayer.qml"
#define QIMDEFLAYERFILE "visuallayer/QimDefaultLayer.qml"
#define QIMMAINUILAYERFILE "visuallayer/QimMainUILayer.qml"
#define SCALEFACTORX 0.1
#define SCALEFACTORY 0.1

/*
 *The core engine is the major class which operates with all handler classes.
 */
CoreEngine::CoreEngine(QWidget *parent) :
        QMainWindow(parent)
{
    /*init the index of the currently selected image
     *this index is updated from qml layer and coreengine
     *it depends on how the index was changed see wheelEvent and qmlInterface
     *for more informations
     */
    this->curr_qml_index = 0;

    /*defines the default screen mode*/
    this->is_full_screen = false;

    /*this is the default Window title*/
    this->default_title = "Qim";
    //setWindowIcon(QIcon("theme/icon/qim.icon-256.png"));

    /*extension objects instantiation*/
    this->config_handler = new ConfigHandler;
    this->config_dialog = new ConfigDialog;
    /*initialize the image handler object which provides the image and directory data*/
    this->image_handler = new ImageHandler;

    /*initialize the styling manager*/
    this->theme_manager = new ThemeManager(this);

    /*initialize the info handler object which contains all kinds of information about the shown image*/
    this->file_info_handler = new FileInfoHandler(this);

    /*this object is the interface object between c++ logic layer and the qml ui layer*/
    this->qml_interface = new QmlInterface(this);

    /*instatiate and load the qml declarative ui into the qml viewer*/
    this->visual_qml_view = new QDeclarativeView;

    /*initialize the context with the root context of the qml viewer*/
    this->context = this->visual_qml_view->rootContext();

    /*the zooming feature scales the image by the scale factor*/
    this->scale_factor_x = SCALEFACTORX;
    this->scale_factor_y = SCALEFACTORY;

    /*define visual options of the main window*/
    this->setUpMainWindow();

}

/*define the apearance options of the MainWindow which contains all
 *visual informations like qml layer and so on
 */
void CoreEngine::setUpMainWindow()
{
    /*this fills the parent application window with the qml view*/
    this->visual_qml_view->setResizeMode(QDeclarativeView::SizeRootObjectToView);
    this->visual_qml_view->setAcceptDrops(true);

    /*set the QDeclarativeView as main widget in the main window*/
    this->setCentralWidget(visual_qml_view);
    /*these two methods are used to define the main window as transparent
     *but when using a widget in in the window the transparency effect gets lost
     */
    this->visual_qml_view->setStyleSheet("background:transparent");
    this->visual_qml_view->setAttribute(Qt::WA_TranslucentBackground);
    this->visual_qml_view->setWindowFlags(Qt::FramelessWindowHint);

    this->setStyleSheet("background:transparent;");
    this->setAttribute(Qt::WA_TranslucentBackground);
    /*turn off system native window decorations which are implemented in qml*/
    this->setWindowFlags(Qt::FramelessWindowHint);
    //this->buildActions();
    //this->buildMenu();

    /*this manifests the qmlInterface in the qml environment
     *for more informations see qmlinterface.h
     */
    this->context->setContextProperty("qmlInterface", this->qml_interface );
    /*set the source of the default qim layer qml file as main qml application*/
    this->visual_qml_view->setSource(QUrl(QIMMAINUILAYERFILE));

}

/*setUpQml will be called when an image was loaded and is used to define the data model for the qml view
 *the imageDataModel contains the processed informations about all found images
 *the qmlInterface is designed to share data and signals between QML and C++ logic
 *these propertys are available in QML via the proterty system
 *the setSource of the qml view is called to load the main .qml application
 *see QimVisualLayer.qml for more information about the qml presentation layer
 */
void CoreEngine::setUpQml()
{
    /*for more informations see imagedatamodel.h - imageDataModelList is just a QList of
     *ImageDataModel which will be defined in the ImageHandler class in the ImageHandler::initImageDataModel()
     *method
     */
    this->context->setContextProperty("imageDataModel", QVariant::fromValue(imageDataModelList));

    /*the active_layer in qml_interface has to be switched to the QmlInterface::Visual_layer to enable displaying images
     *more informations about this concept can be found in the QmlInterface header at the changeActiveLayer()
     *declaration
     */
    this->qml_interface->changeActiveLayer(QmlInterface::Visual_layer);

    /*this sendUpdateSignal gets the qml_interface to emit an update signal which is used to
     *determine in which mode the images should be presented see qml_interface documentation
     *for more informations
     *this method is also called when navigating
     */
    this->qml_interface->sendImageScaleSignal();

}

/*This is the main open process to load images. When loading an image
 *the folder which contains the image will be parsed to load a list of
 *all images in this folder except all unsupported files
 */
void CoreEngine::open()
{
    QString file = QFileDialog::getOpenFileName(this,tr("open file"),QDir::currentPath());
    if(!file.isEmpty())
    {
        this->image_handler->loadImage(file);
        /*this updates the index of the currently selected image to synchronize it
         *with the qml layer this is important to avoid asynchron navigation states
         */
        this->curr_qml_index = this->image_handler->getCurFileIndex();
        /*this sends the index to the qml environment to synch the index*/
        this->qml_interface->updateQmlIndex(this->curr_qml_index);
        /*image data initialization to get all image data to qml*/
        this->image_handler->initImageDataModel(this->imageDataModelList);
        /*see setUpQml definition*/
        this->setUpQml();
        /*the file information has to be updated before scaling or manipulate the image otherwise */
        if (this->image_handler->getCurImage().isNull())
        {
            QMessageBox::information(this, tr("Qim - error report"),
                                    tr("Can't convert to QImage."));
            return;
        }
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
        this->image_handler->initImageDataModel(this->imageDataModelList);
        this->setUpQml();
        if (this->image_handler->getCurImage().isNull())
        {
            QMessageBox::information(this, tr("Qim - error report"),
                                     tr("Can't convert to QImage."));
            return;
        }
        this->updateMainTitle(image_handler->getTitleStr());

        return;
    }
    QMessageBox::information(this, tr("Qim - error report"),
                             tr("Can't load file!"));
}

/*sends an updated title string to the qml layer*/
void CoreEngine::updateMainTitle(QString titlestr)
{
    QString newtitle = this->default_title;
    newtitle.append(" - ");
    //this->setWindowTitle(newtitle.append(titlestr));
    /*used to delegate the new title string to the qml environment*/
    this->qml_interface->setNewTitle(newtitle.append(titlestr));
}

/*this method is designed to build the configuration dialog for qim*/
void CoreEngine::openConfig()
{
    this->config_dialog->show();
    //this->config_dialog->setWindowFlags(Qt::WindowStaysOnTopHint);
}

void CoreEngine::zoomIn()
{
    //image_viewport->zoomIn(scale_factor_x,scale_factor_y);
    this->qml_interface->emitZoom(QmlInterface::IN);
}

void CoreEngine::zoomOut()
{
    //image_viewport->zoomOut(scale_factor_x,scale_factor_y);
    this->qml_interface->emitZoom(QmlInterface::OUT);

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
            this->qml_interface->updateQmlIndex(this->curr_qml_index);
            this->qml_interface->sendImageScaleSignal();
            this->updateMainTitle(this->image_handler->getTitleStr());
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
            this->qml_interface->updateQmlIndex(this->curr_qml_index);
            this->qml_interface->sendImageScaleSignal();
            this->updateMainTitle(this->image_handler->getTitleStr());
        }
    }
}


void CoreEngine::toggleFullScreen()
{
    if(this->is_full_screen)
        this->showNormal();
    else if(this->is_full_screen == false)
        this->showFullScreen();
}

void CoreEngine::about()
{

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

    this->show_file_info = new QAction(tr("Show &Info"),this);
    this->connect(this->show_file_info, SIGNAL(triggered()), this, SLOT(showInfo()));

    this->close_file_info = new QAction(tr("Close &Info"),this);
    this->connect(this->close_file_info, SIGNAL(triggered()), this, SLOT(closeInfo()));

    /*the aboutQT() function is a build in dialog*/
    this->about_qt_qction = new QAction(tr("About &Qt"), this);
    this->connect(this->about_qt_qction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    this->show_fullsreen = new QAction(tr("Show &Fullscreen"),this);
    this->connect(this->show_fullsreen, SIGNAL(triggered()), this, SLOT(showFullScreen()));

    this->close_fullsreen = new QAction(tr("Close &Fullscreen"),this);
    this->connect(this->close_fullsreen, SIGNAL(triggered()), this, SLOT(showNormal()));
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
    this->helpMenu->addAction(this->show_fullsreen);

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

/*the resize event is needed to forward the current window size to the qml environment*/
/*void CoreEngine::resizeEvent(QResizeEvent *event)
{
    this->qml_interface->setNewSize(event->size());
}
*/
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
    this->contextMenu->move(event->x(),event->y());
    //for now the contextMenu will be cleared before adding all needed actions
    this->contextMenu->clear();
    if(this->file_info_handler->isVisible())
    {
        this->contextMenu->addAction(this->close_file_info);
    }
    else
    {
        this->contextMenu->addAction(this->show_file_info);
    }

    if (this->isFullScreen())
    {
        this->contextMenu->addAction(this->close_fullsreen);
    }
    else
    {
        this->contextMenu->addAction(this->show_fullsreen);
    }
    this->contextMenu->show();
}
*/

void CoreEngine::openFromArgument(char *file)
{
    QString filepath = (QString)file;
    this->open(filepath);
}

/*synchronize the qml index in the coreengine and the image_handler
 *the qml_interface updates the index by itself
 */
void CoreEngine::setQmlIndex(int index)
{
    this->curr_qml_index = index;
    this->image_handler->setCurFileIndex(index);
}


//OPEN,CLOSE,ABOUT,FULLSCREEN,CONFIG
void CoreEngine::callCoreAction(CoreAction action)
{

    qDebug() << "recieve action " << action;
    switch(action)
    {
    case 0: this->open();
            break;
    case 1: this->close();
            break;
    case 2: this->about();
            break;
    case 3: this->toggleFullScreen();
            break;
    case 4: this->openConfig();
            break;
    }
}



CoreEngine::~CoreEngine()
{

}
