/********************************************************************************
** Form generated from reading UI file 'EmbeddedSystemDebugger.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EMBEDDEDSYSTEMDEBUGGER_H
#define UI_EMBEDDEDSYSTEMDEBUGGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EmbeddedSystemDebuggerClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *EmbeddedSystemDebuggerClass)
    {
        if (EmbeddedSystemDebuggerClass->objectName().isEmpty())
            EmbeddedSystemDebuggerClass->setObjectName(QString::fromUtf8("EmbeddedSystemDebuggerClass"));
        EmbeddedSystemDebuggerClass->resize(600, 400);
        menuBar = new QMenuBar(EmbeddedSystemDebuggerClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        EmbeddedSystemDebuggerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(EmbeddedSystemDebuggerClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        EmbeddedSystemDebuggerClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(EmbeddedSystemDebuggerClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        EmbeddedSystemDebuggerClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(EmbeddedSystemDebuggerClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        EmbeddedSystemDebuggerClass->setStatusBar(statusBar);

        retranslateUi(EmbeddedSystemDebuggerClass);

        QMetaObject::connectSlotsByName(EmbeddedSystemDebuggerClass);
    } // setupUi

    void retranslateUi(QMainWindow *EmbeddedSystemDebuggerClass)
    {
        EmbeddedSystemDebuggerClass->setWindowTitle(QCoreApplication::translate("EmbeddedSystemDebuggerClass", "EmbeddedSystemDebugger", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EmbeddedSystemDebuggerClass: public Ui_EmbeddedSystemDebuggerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMBEDDEDSYSTEMDEBUGGER_H
