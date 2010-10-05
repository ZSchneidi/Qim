# -------------------------------------------------
# Project created by QtCreator 2010-06-02T19:48:16
# -------------------------------------------------

QT       += core gui\
         declarative

TARGET = Qim
TEMPLATE = app
SOURCES += main.cpp \
    core/coreengine.cpp \
    manager/pluginmmanager.cpp \
    manager/thememanager.cpp \
    core/imagehandler.cpp \
    core/filesupport.cpp \
    core/fileinfohandler.cpp \
    core/imagedatamodel.cpp \
    core/fileinfothread.cpp \
    core/qmlinterface.cpp

HEADERS += core/coreengine.h \
    manager/pluginmmanager.h \
    manager/thememanager.h \
    core/imagehandler.h \
    core/filesupport.h \
    core/fileinfohandler.h \
    core/imagedatamodel.h \
    core/fileinfothread.h \
    core/qmlinterface.h


FORMS += mainviewer.ui \
    core/fileinfohandler.ui

TRANSLATIONS = theme/language/qim_lang_de_DE.ts

OTHER_FILES += \
    visuallayer/QimVisualLayer.qml \
    visuallayer/ContextListView.qml \
    visuallayer/elements/ImageListDelegate.qml \
    visuallayer/elements/ShadowBox.qml \
    visuallayer/elements/ListDelegate.qml \
    visuallayer/elements/ImageListVisualDataModel.qml \
    visuallayer/elements/ImageListDelegateDetails.qml \
    visuallayer/elements/QimDefaultLayer.qml \
    visuallayer/QimDefaultLayer.qml \
    visuallayer/elements/CustomWindowResizer.qml \
    visuallayer/elements/CustomTitleBar.qml \
    visuallayer/elements/CustomMenuBar.qml \
    visuallayer/QimMainUILayer.qml
