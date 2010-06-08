/********************************************************************************
** Form generated from reading UI file 'mainviewer.ui'
**
** Created: Wed 2. Jun 19:49:02 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINVIEWER_H
#define UI_MAINVIEWER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainViewer
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainViewer)
    {
        if (MainViewer->objectName().isEmpty())
            MainViewer->setObjectName(QString::fromUtf8("MainViewer"));
        MainViewer->resize(600, 400);
        menuBar = new QMenuBar(MainViewer);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        MainViewer->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainViewer);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainViewer->addToolBar(mainToolBar);
        centralWidget = new QWidget(MainViewer);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        MainViewer->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainViewer);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainViewer->setStatusBar(statusBar);

        retranslateUi(MainViewer);

        QMetaObject::connectSlotsByName(MainViewer);
    } // setupUi

    void retranslateUi(QMainWindow *MainViewer)
    {
        MainViewer->setWindowTitle(QApplication::translate("MainViewer", "MainViewer", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainViewer: public Ui_MainViewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINVIEWER_H
