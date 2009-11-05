/********************************************************************************
** Form generated from reading ui file 'cornerspp.ui'
**
** Created: Sat Oct 31 22:33:03 2009
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_CORNERSPP_H
#define UI_CORNERSPP_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CornersFrameClass
{
public:
    QAction *actionConfig;
    QAction *actionExit;
    QAction *actionAbout;
    QAction *actionNew_game;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *CornersFrameClass)
    {
        if (CornersFrameClass->objectName().isEmpty())
            CornersFrameClass->setObjectName(QString::fromUtf8("CornersFrameClass"));
        CornersFrameClass->resize(500, 500);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(50);
        sizePolicy.setVerticalStretch(50);
        sizePolicy.setHeightForWidth(CornersFrameClass->sizePolicy().hasHeightForWidth());
        CornersFrameClass->setSizePolicy(sizePolicy);
        CornersFrameClass->setMinimumSize(QSize(100, 100));
        actionConfig = new QAction(CornersFrameClass);
        actionConfig->setObjectName(QString::fromUtf8("actionConfig"));
        actionConfig->setAutoRepeat(false);
        actionConfig->setMenuRole(QAction::NoRole);
        actionExit = new QAction(CornersFrameClass);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionExit->setMenuRole(QAction::QuitRole);
        actionAbout = new QAction(CornersFrameClass);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionAbout->setMenuRole(QAction::AboutRole);
        actionNew_game = new QAction(CornersFrameClass);
        actionNew_game->setObjectName(QString::fromUtf8("actionNew_game"));
        centralwidget = new QWidget(CornersFrameClass);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        CornersFrameClass->setCentralWidget(centralwidget);
        menubar = new QMenuBar(CornersFrameClass);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 500, 23));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        CornersFrameClass->setMenuBar(menubar);
        statusbar = new QStatusBar(CornersFrameClass);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        CornersFrameClass->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionNew_game);
        menuFile->addAction(actionConfig);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuHelp->addAction(actionAbout);

        retranslateUi(CornersFrameClass);

        QMetaObject::connectSlotsByName(CornersFrameClass);
    } // setupUi

    void retranslateUi(QMainWindow *CornersFrameClass)
    {
        CornersFrameClass->setWindowTitle(QApplication::translate("CornersFrameClass", "Welcome to Corners!", 0, QApplication::UnicodeUTF8));
        actionConfig->setText(QApplication::translate("CornersFrameClass", "Config", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionConfig->setToolTip(QApplication::translate("CornersFrameClass", "open configuration dialog", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionExit->setText(QApplication::translate("CornersFrameClass", "Exit", 0, QApplication::UnicodeUTF8));
        actionExit->setShortcut(QApplication::translate("CornersFrameClass", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("CornersFrameClass", "About", 0, QApplication::UnicodeUTF8));
        actionNew_game->setText(QApplication::translate("CornersFrameClass", "New game", 0, QApplication::UnicodeUTF8));
        actionNew_game->setShortcut(QApplication::translate("CornersFrameClass", "Ctrl+N", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("CornersFrameClass", "File", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("CornersFrameClass", "Help", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CornersFrameClass: public Ui_CornersFrameClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CORNERSPP_H
