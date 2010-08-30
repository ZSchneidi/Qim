/********************************************************************************
** Form generated from reading UI file 'mainviewer.ui'
**
** Created: Mon 30. Aug 17:39:30 2010
**      by: Qt User Interface Compiler version 4.7.0
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
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainViewer
{
public:
    QWidget *centralWidget;

    void setupUi(QMainWindow *MainViewer)
    {
        if (MainViewer->objectName().isEmpty())
            MainViewer->setObjectName(QString::fromUtf8("MainViewer"));
        MainViewer->resize(600, 400);
        MainViewer->setCursor(QCursor(Qt::ArrowCursor));
        MainViewer->setContextMenuPolicy(Qt::PreventContextMenu);
        MainViewer->setWindowOpacity(1);
        MainViewer->setAutoFillBackground(false);
        MainViewer->setStyleSheet(QString::fromUtf8("background:qlineargradient(spread:pad, x1:1, y1:1, x2:1, y2:0, stop:0 rgba(59, 59, 59, 180), stop:1 rgba(102, 102, 102, 0));"));
        centralWidget = new QWidget(MainViewer);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        MainViewer->setCentralWidget(centralWidget);

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
