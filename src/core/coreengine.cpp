#include "coreengine.h"
#include "globaldefinitions.h"


CoreEngine::CoreEngine(QWidget *parent) :
        QMainWindow(parent)
{
    /*init the index of the currently selected image
     *this index is updated from qml layer and coreengine
     *it depends on how the index was changed see wheelEvent and qmlInterface
     *for more informations
     */
    this->curr_qml_index = 0;

    /*this is the default Window title*/
    this->default_title = "Qim";
    //setWindowIcon(QIcon("theme/icon/qim.icon-256.png"));

    /*extension objects instantiation*/
    this->main_local = new QLocale;

    /** the CustomDialogBox is an object which provides the dialog for machine -> user communication*/
    this->dialog_box = new CustomDialogBox();

    this->imange_data_model = new ImageDataModel();

    /*this is the config handling class it is important that the confighandler is
     *instatiated before proceed with other classes which use the config handler
     */
    this->config_handler = new ConfigHandler(this);
    this->config_dialog = new ConfigDialog(this,this,this->getConfigHandler());
    /*initialize the image handler object which provides the image and directory data*/
    this->image_handler = new ImageHandler(this);

    /*initialize the styling manager*/
//this->theme_manager = new ThemeManager(this);

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


    /*signal slot connections*/
    /** connect opacity changes in the config dialog with the QmlInterface*/
    connect(this->config_handler,SIGNAL(backgroundOpacityChanged(float)),this->qml_interface,SLOT(on_backgroundOpacityChanged(float)));
    /** connect color changes in the config dialog with the QmlInterface*/
    connect(this->config_handler,SIGNAL(backgroundColorChanged(QString)),this->qml_interface,SLOT(on_backgroundColorChanged(QString)));
    /** connect blacklisted formats line edit in the config dialog with FileSupport::initFileBlacklistMap*/
    connect(this->config_handler,SIGNAL(blacklistedFormatsChanged(QString)),this->image_handler->getFileSupport(),SLOT(onBlacklistedFormatsChanged(QString)));

    /*define visual options of the main window*/
    this->setUpMainWindow();


}

/**
 *define the apearance options of the MainWindow which contains all
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


    this->setMinimumSize(500,400);
    //this->setStyleSheet("background:transparent;");
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

    /*set the window size to the via config defined size if maximized or fullscreen is set
     *the size will be ignored
     */

    if(this->config_handler->startMaximized())
        this->showMaximized();
    else if(this->config_handler->startFullScreen())
        this->showFullScreen();
    else
        this->resize(this->config_handler->defWindowSize());
    this->show();
}

/**
 *setUpQml will be called when an image was loaded and is used to define the data model for the qml view
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
this->imange_data_model->debugModel();
    this->context->setContextProperty("imageDataModel", QVariant::fromValue(this->imange_data_model->getDataModel()));

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

/**
 *This is the main open process to load images. When loading an image
 *the folder which contains the image will be parsed to load a list of
 *all images in this folder except all unsupported files
 */
void CoreEngine::open()
{
    QString file = QFileDialog::getOpenFileName(this,tr("open file"),QDir::currentPath());
    if(!file.isEmpty() && this->image_handler->isFileSupported(file))
    {
        this->image_handler->loadImage(file);
        /*this updates the index of the currently selected image to synchronize it
         *with the qml layer this is important to avoid asynchron navigation states
         */
        this->curr_qml_index = this->image_handler->getCurFileIndex();
        /*this sends the index to the qml environment to synch the index*/
        this->qml_interface->updateQmlIndex(this->curr_qml_index);
        /*image data initialization to get all image data to qml*/
        this->image_handler->initImageDataModel(this->imange_data_model->getDataModel());
        /*see setUpQml definition*/
        this->setUpQml();
        /*the file information has to be updated before scaling or manipulate the image otherwise */
        if (this->image_handler->getCurImage().isNull())
        {
            this->dialog_box->showDialogBox(tr("Qim - error report"),tr("Can't convert to QImage."));
            return;
        }
        this->updateMainTitle(this->image_handler->getTitleStr());
        return;
    }
    this->dialog_box->showDialogBox(tr("Qim - wrong file format"),tr("Please select a valid file!"));
}

/**
 * Is an overloaded function of open()
 * Was desiged to open the file defined by filepath
 * @param filepath defines the file you want to open
 */
void CoreEngine::open(QString filepath)
{
    if(!filepath.isEmpty())
    {
        this->image_handler->loadImage(filepath);
        this->curr_qml_index = this->image_handler->getCurFileIndex();
        this->qml_interface->updateQmlIndex(this->curr_qml_index);
        this->image_handler->initImageDataModel(this->imange_data_model->getDataModel());
        this->setUpQml();
        if (this->image_handler->getCurImage().isNull())
        {
            this->dialog_box->showDialogBox(tr("Qim - error report"),tr("Can't convert to QImage."));
            return;
        }
        this->updateMainTitle(image_handler->getTitleStr());

        return;
    }
    this->dialog_box->showDialogBox(tr("Qim - error report"),tr("No File selected"));
}

/**
 * designed to change to application title
 * the new title string will be forwarded to the QmlInterface::setNewTitle()
 *
 * @param titlestr defines the new title
 */
void CoreEngine::updateMainTitle(QString titlestr)
{
    QString newtitle = this->default_title;
    newtitle.append(" - ");
    //this->setWindowTitle(newtitle.append(titlestr));
    /*used to delegate the new title string to the qml environment*/
    this->qml_interface->setNewTitle(newtitle.append(titlestr));
}

/**this method is designed to build the configuration dialog for qim*/
void CoreEngine::openConfig()
{
    this->config_dialog->show();
    //this->config_dialog->setWindowFlags(Qt::WindowStaysOnTopHint);
}

/** this slot is called on a mouse wheel event and prompt QmlInterface::emitZoom() with QmlInterface::IN to increase the image size*/
void CoreEngine::zoomIn()
{
    //image_viewport->zoomIn(scale_factor_x,scale_factor_y);
    this->qml_interface->emitZoom(QmlInterface::IN);
}

/** this slot is called on a mouse wheel event and prompt QmlInterface::emitZoom() with QmlInterface::OUT to decrease the image size*/
void CoreEngine::zoomOut()
{
    //image_viewport->zoomOut(scale_factor_x,scale_factor_y);
    this->qml_interface->emitZoom(QmlInterface::OUT);

}

/** this method is used to display the FileInfoHandler dialog*/
void CoreEngine::showInfo()
{
    if(!this->file_info_handler->isVisible())
    {
        this->file_info_handler->show();
    }
}

/** this method is used to close the FileInfoHandler dialog*/
void CoreEngine::closeInfo()
{
    if(this->file_info_handler->isVisible())
    {
        this->file_info_handler->close();
    }
}

/**
  * this method is called on mous wheel event and navigates through the
  * ImageHandler::file_info_list on calling ImageHandler::loadNextImage()
  *
  */
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

/**
  * this method is called on mous wheel event and navigates through the
  * ImageHandler::file_info_list on calling ImageHandler::loadPrevImage()
  *
  */
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

/** this method was designed to switch on and off the FullScreen mode of the application*/
void CoreEngine::toggleFullScreen()
{
    if(this->isFullScreen())
    {
        this->showNormal();
        //this->resize(DEFAULT_WINDOW_SIZE_WIDTH,DEFAULT_WINDOW_SIZE_HEIGHT);
        this->resize(this->config_handler->defWindowSize().width(),this->config_handler->defWindowSize().height());
    }
    else if(!this->isFullScreen())
        this->showFullScreen();
}

/** this method was designed to switch on and off the Maximized mode of the application*/
void CoreEngine::toggleMaxWindow()
{
    if(this->isMaximized())
    {
        this->showNormal();
        //this->resize(DEFAULT_WINDOW_SIZE_WIDTH,DEFAULT_WINDOW_SIZE_HEIGHT);
        this->resize(this->config_handler->defWindowSize().width(),this->config_handler->defWindowSize().height());
    }
    else if(!this->isMaximized())
    {
        this->showMaximized();
    }
}

/** currently no implemented*/
void CoreEngine::about()
{

}

/** builds all Actions for the menu is only used when the ui is not implemented in qml*/
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

/** builds the none qml menus*/
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

/** the dragEnterEvent() is called whenever the user enters the application window with a file in drag mode*/
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

/** this event is called when the user drops the file over the application window*/
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

/** the wheelEvent is called on mous wheel actions*/
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

/** if anything is left to do befor closing the application do it here*/
void CoreEngine::closeEvent(QCloseEvent *event)
{
    /*if the window is maximized or fullscreen do not write the current size to config
     * this would overwrite the last defined size with the fullscreen or maximized size
     */
    if(!this->isMaximized() && !this->isFullScreen() )
        this->config_handler->setDefWindowSize(this->size());
    /*if the window is maximized write this to config*/
    this->config_handler->setStartMaximized(this->isMaximized());
    /*if the window is in fullscreen write this to config*/
    this->config_handler->setStartFullScreen(this->isFullScreen());
    /*updates the config file with the new values*/
    this->config_handler->writeNewConfig();
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

/** this method can be used to open a file from the main() function it only converts the file parameter to QString*/
void CoreEngine::openFromArgument(char *file)
{
    QString filepath = (QString)file;
    this->open(filepath);
}

/**
 *synchronize the qml index in the coreengine and the image_handler
 *the qml_interface updates the index by itself
 */
void CoreEngine::setQmlIndex(int index)
{
    this->curr_qml_index = index;
    this->image_handler->setCurFileIndex(index);
}

/** this method is called from the qml ui layer to forward several actions in the application core
 * @param action is a CoreEngine::CoreAction which defines the action that will be called
 */

void CoreEngine::callCoreAction(CoreAction action)
{
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
    case 5: this->toggleMaxWindow();
            break;
    }
}

/** currently not implemented*/
bool CoreEngine::showErrorDialog(const QString msg)
{
    qDebug() << "error: " << msg;
    return false;
}

CoreEngine::~CoreEngine()
{

}
