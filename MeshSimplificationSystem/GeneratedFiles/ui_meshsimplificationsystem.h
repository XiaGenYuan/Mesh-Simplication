/********************************************************************************
** Form generated from reading UI file 'meshsimplificationsystem.ui'
**
** Created: Fri Jan 23 11:13:03 2015
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MESHSIMPLIFICATIONSYSTEM_H
#define UI_MESHSIMPLIFICATIONSYSTEM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MeshSimplificationSystemClass
{
public:
    QAction *action_open;
    QAction *action_mesh_simplification;
    QAction *action_saveas;
    QAction *action_recover;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MeshSimplificationSystemClass)
    {
        if (MeshSimplificationSystemClass->objectName().isEmpty())
            MeshSimplificationSystemClass->setObjectName(QString::fromUtf8("MeshSimplificationSystemClass"));
        MeshSimplificationSystemClass->resize(913, 609);
        action_open = new QAction(MeshSimplificationSystemClass);
        action_open->setObjectName(QString::fromUtf8("action_open"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/MeshSimplificationSystem/Resources/file.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_open->setIcon(icon);
        action_mesh_simplification = new QAction(MeshSimplificationSystemClass);
        action_mesh_simplification->setObjectName(QString::fromUtf8("action_mesh_simplification"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/MeshSimplificationSystem/Resources/simplification.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_mesh_simplification->setIcon(icon1);
        action_saveas = new QAction(MeshSimplificationSystemClass);
        action_saveas->setObjectName(QString::fromUtf8("action_saveas"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/MeshSimplificationSystem/Resources/saveas.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_saveas->setIcon(icon2);
        action_recover = new QAction(MeshSimplificationSystemClass);
        action_recover->setObjectName(QString::fromUtf8("action_recover"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/MeshSimplificationSystem/Resources/recover.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_recover->setIcon(icon3);
        centralWidget = new QWidget(MeshSimplificationSystemClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        MeshSimplificationSystemClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MeshSimplificationSystemClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 913, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        MeshSimplificationSystemClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MeshSimplificationSystemClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MeshSimplificationSystemClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MeshSimplificationSystemClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MeshSimplificationSystemClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuFile->addAction(action_open);
        menuFile->addAction(action_saveas);
        menuEdit->addAction(action_mesh_simplification);
        menuEdit->addAction(action_recover);
        mainToolBar->addAction(action_open);
        mainToolBar->addAction(action_saveas);
        mainToolBar->addAction(action_mesh_simplification);
        mainToolBar->addAction(action_recover);

        retranslateUi(MeshSimplificationSystemClass);

        QMetaObject::connectSlotsByName(MeshSimplificationSystemClass);
    } // setupUi

    void retranslateUi(QMainWindow *MeshSimplificationSystemClass)
    {
        MeshSimplificationSystemClass->setWindowTitle(QApplication::translate("MeshSimplificationSystemClass", "MeshSimplificationSystem", 0, QApplication::UnicodeUTF8));
        action_open->setText(QApplication::translate("MeshSimplificationSystemClass", "Open", 0, QApplication::UnicodeUTF8));
        action_mesh_simplification->setText(QApplication::translate("MeshSimplificationSystemClass", "Mesh Simplification", 0, QApplication::UnicodeUTF8));
        action_saveas->setText(QApplication::translate("MeshSimplificationSystemClass", "Save As", 0, QApplication::UnicodeUTF8));
        action_recover->setText(QApplication::translate("MeshSimplificationSystemClass", "Recover", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MeshSimplificationSystemClass", "File", 0, QApplication::UnicodeUTF8));
        menuEdit->setTitle(QApplication::translate("MeshSimplificationSystemClass", "Edit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MeshSimplificationSystemClass: public Ui_MeshSimplificationSystemClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESHSIMPLIFICATIONSYSTEM_H
