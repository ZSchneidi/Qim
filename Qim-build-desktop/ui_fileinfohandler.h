/********************************************************************************
** Form generated from reading UI file 'fileinfohandler.ui'
**
** Created: Thu 8. Jul 00:05:05 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILEINFOHANDLER_H
#define UI_FILEINFOHANDLER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FileInfoHandler
{
public:
    QTableWidget *fileinfotable;
    QPushButton *close_button;

    void setupUi(QWidget *FileInfoHandler)
    {
        if (FileInfoHandler->objectName().isEmpty())
            FileInfoHandler->setObjectName(QString::fromUtf8("FileInfoHandler"));
        FileInfoHandler->resize(301, 400);
        FileInfoHandler->setMaximumSize(QSize(301, 400));
        FileInfoHandler->setWindowOpacity(8);
        FileInfoHandler->setStyleSheet(QString::fromUtf8(""));
        fileinfotable = new QTableWidget(FileInfoHandler);
        if (fileinfotable->columnCount() < 2)
            fileinfotable->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        fileinfotable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        fileinfotable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        if (fileinfotable->rowCount() < 10)
            fileinfotable->setRowCount(10);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        __qtablewidgetitem2->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        fileinfotable->setItem(0, 0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        __qtablewidgetitem3->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        fileinfotable->setItem(1, 0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        __qtablewidgetitem4->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        fileinfotable->setItem(2, 0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        __qtablewidgetitem5->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        fileinfotable->setItem(3, 0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        __qtablewidgetitem6->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        __qtablewidgetitem6->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        fileinfotable->setItem(4, 0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        __qtablewidgetitem7->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        __qtablewidgetitem7->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        fileinfotable->setItem(5, 0, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        __qtablewidgetitem8->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        __qtablewidgetitem8->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        fileinfotable->setItem(6, 0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        __qtablewidgetitem9->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        __qtablewidgetitem9->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        fileinfotable->setItem(7, 0, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        __qtablewidgetitem10->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        __qtablewidgetitem10->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        fileinfotable->setItem(8, 0, __qtablewidgetitem10);
        fileinfotable->setObjectName(QString::fromUtf8("fileinfotable"));
        fileinfotable->setGeometry(QRect(0, 0, 302, 225));
        fileinfotable->setMaximumSize(QSize(302, 225));
        fileinfotable->setAcceptDrops(false);
        fileinfotable->setAutoScroll(true);
        fileinfotable->setShowGrid(true);
        fileinfotable->setGridStyle(Qt::CustomDashLine);
        fileinfotable->setSortingEnabled(false);
        fileinfotable->setRowCount(10);
        fileinfotable->setColumnCount(2);
        fileinfotable->horizontalHeader()->setVisible(false);
        fileinfotable->horizontalHeader()->setCascadingSectionResizes(true);
        fileinfotable->horizontalHeader()->setDefaultSectionSize(150);
        fileinfotable->horizontalHeader()->setMinimumSectionSize(27);
        fileinfotable->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        fileinfotable->verticalHeader()->setVisible(false);
        fileinfotable->verticalHeader()->setDefaultSectionSize(20);
        fileinfotable->verticalHeader()->setMinimumSectionSize(19);
        fileinfotable->verticalHeader()->setStretchLastSection(false);
        close_button = new QPushButton(FileInfoHandler);
        close_button->setObjectName(QString::fromUtf8("close_button"));
        close_button->setGeometry(QRect(110, 340, 75, 23));

        retranslateUi(FileInfoHandler);

        QMetaObject::connectSlotsByName(FileInfoHandler);
    } // setupUi

    void retranslateUi(QWidget *FileInfoHandler)
    {
        FileInfoHandler->setWindowTitle(QApplication::translate("FileInfoHandler", "File informations", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = fileinfotable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("FileInfoHandler", "Property", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = fileinfotable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("FileInfoHandler", "Value", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = fileinfotable->isSortingEnabled();
        fileinfotable->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem2 = fileinfotable->item(0, 0);
        ___qtablewidgetitem2->setText(QApplication::translate("FileInfoHandler", "File name", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = fileinfotable->item(1, 0);
        ___qtablewidgetitem3->setText(QApplication::translate("FileInfoHandler", "Width", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = fileinfotable->item(2, 0);
        ___qtablewidgetitem4->setText(QApplication::translate("FileInfoHandler", "Heigth", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = fileinfotable->item(3, 0);
        ___qtablewidgetitem5->setText(QApplication::translate("FileInfoHandler", "Depth", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem6 = fileinfotable->item(4, 0);
        ___qtablewidgetitem6->setText(QApplication::translate("FileInfoHandler", "Hor. dpi", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem7 = fileinfotable->item(5, 0);
        ___qtablewidgetitem7->setText(QApplication::translate("FileInfoHandler", "Ver. dpi", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem8 = fileinfotable->item(6, 0);
        ___qtablewidgetitem8->setText(QApplication::translate("FileInfoHandler", "File size", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem9 = fileinfotable->item(7, 0);
        ___qtablewidgetitem9->setText(QApplication::translate("FileInfoHandler", "File type", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem10 = fileinfotable->item(8, 0);
        ___qtablewidgetitem10->setText(QApplication::translate("FileInfoHandler", "Last change", 0, QApplication::UnicodeUTF8));
        fileinfotable->setSortingEnabled(__sortingEnabled);

        close_button->setText(QApplication::translate("FileInfoHandler", "Schlie\303\237en", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FileInfoHandler: public Ui_FileInfoHandler {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILEINFOHANDLER_H
