# -------------------------------------------------
# Project created by QtCreator 2010-06-02T19:48:16
# -------------------------------------------------
TARGET = Qim
TEMPLATE = app
SOURCES += main.cpp \
    core/coreengine.cpp \
    manager/pluginmmanager.cpp \
    manager/thememanager.cpp \
    core/imagehandler.cpp \
    core/filesupport.cpp \
    core/fileinfohandler.cpp \
    core/viewport.cpp
HEADERS += core/coreengine.h \
    manager/pluginmmanager.h \
    manager/thememanager.h \
    core/imagehandler.h \
    core/filesupport.h \
    core/fileinfohandler.h \
    core/viewport.h
FORMS += mainviewer.ui \
    core/fileinfohandler.ui

TRANSLATIONS = theme/language/qim_lang_de_DE.ts
