/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "openglwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    OpenGLWidget *widget;
    QSlider *XSlider;
    QSlider *YSlider;
    QSlider *ZSlider;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QCheckBox *FillBox;
    QCheckBox *LineBox;
    QCheckBox *DCBox;
    QLabel *label_fps;
    QCheckBox *CullingBox;
    QSlider *NumbersOfObjectsX;
    QSlider *NumbersOfObjectsY;
    QSlider *NumbersOfObjectsZ;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1920, 950);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        widget = new OpenGLWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 1500, 900));
        XSlider = new QSlider(centralwidget);
        XSlider->setObjectName(QString::fromUtf8("XSlider"));
        XSlider->setGeometry(QRect(1540, 20, 301, 16));
        XSlider->setMaximum(5760);
        XSlider->setSingleStep(16);
        XSlider->setPageStep(240);
        XSlider->setOrientation(Qt::Horizontal);
        XSlider->setTickInterval(240);
        YSlider = new QSlider(centralwidget);
        YSlider->setObjectName(QString::fromUtf8("YSlider"));
        YSlider->setGeometry(QRect(1540, 60, 301, 16));
        YSlider->setMaximum(5760);
        YSlider->setSingleStep(16);
        YSlider->setPageStep(240);
        YSlider->setOrientation(Qt::Horizontal);
        YSlider->setTickInterval(240);
        ZSlider = new QSlider(centralwidget);
        ZSlider->setObjectName(QString::fromUtf8("ZSlider"));
        ZSlider->setGeometry(QRect(1540, 100, 301, 16));
        ZSlider->setMaximum(5760);
        ZSlider->setSingleStep(16);
        ZSlider->setPageStep(240);
        ZSlider->setOrientation(Qt::Horizontal);
        ZSlider->setTickInterval(240);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(1540, 0, 231, 21));
        label->setMidLineWidth(-2);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(1540, 40, 251, 16));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(1540, 80, 221, 16));
        FillBox = new QCheckBox(centralwidget);
        FillBox->setObjectName(QString::fromUtf8("FillBox"));
        FillBox->setGeometry(QRect(1550, 470, 72, 19));
        FillBox->setChecked(true);
        LineBox = new QCheckBox(centralwidget);
        LineBox->setObjectName(QString::fromUtf8("LineBox"));
        LineBox->setGeometry(QRect(1550, 500, 72, 19));
        DCBox = new QCheckBox(centralwidget);
        DCBox->setObjectName(QString::fromUtf8("DCBox"));
        DCBox->setGeometry(QRect(1550, 440, 231, 19));
        DCBox->setChecked(true);
        label_fps = new QLabel(centralwidget);
        label_fps->setObjectName(QString::fromUtf8("label_fps"));
        label_fps->setGeometry(QRect(1540, 230, 91, 16));
        CullingBox = new QCheckBox(centralwidget);
        CullingBox->setObjectName(QString::fromUtf8("CullingBox"));
        CullingBox->setGeometry(QRect(1550, 420, 72, 19));
        CullingBox->setChecked(true);
        NumbersOfObjectsX = new QSlider(centralwidget);
        NumbersOfObjectsX->setObjectName(QString::fromUtf8("NumbersOfObjectsX"));
        NumbersOfObjectsX->setGeometry(QRect(1540, 280, 301, 16));
        NumbersOfObjectsX->setMinimum(1);
        NumbersOfObjectsX->setMaximum(100);
        NumbersOfObjectsX->setOrientation(Qt::Horizontal);
        NumbersOfObjectsY = new QSlider(centralwidget);
        NumbersOfObjectsY->setObjectName(QString::fromUtf8("NumbersOfObjectsY"));
        NumbersOfObjectsY->setGeometry(QRect(1540, 330, 301, 16));
        NumbersOfObjectsY->setMinimum(1);
        NumbersOfObjectsY->setMaximum(100);
        NumbersOfObjectsY->setOrientation(Qt::Horizontal);
        NumbersOfObjectsZ = new QSlider(centralwidget);
        NumbersOfObjectsZ->setObjectName(QString::fromUtf8("NumbersOfObjectsZ"));
        NumbersOfObjectsZ->setGeometry(QRect(1540, 380, 301, 16));
        NumbersOfObjectsZ->setMinimum(1);
        NumbersOfObjectsZ->setMaximum(100);
        NumbersOfObjectsZ->setOrientation(Qt::Horizontal);
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(1540, 260, 171, 16));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(1540, 310, 171, 16));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(1540, 360, 171, 16));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1920, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "X axis slider", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Y axis slider", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Z axis slider", nullptr));
        FillBox->setText(QCoreApplication::translate("MainWindow", "Fill", nullptr));
        LineBox->setText(QCoreApplication::translate("MainWindow", "Line", nullptr));
        DCBox->setText(QCoreApplication::translate("MainWindow", "Depth", nullptr));
        label_fps->setText(QCoreApplication::translate("MainWindow", "FPS:", nullptr));
        CullingBox->setText(QCoreApplication::translate("MainWindow", "Culling", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Number of X axis objecs", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Number of Y axis objecs", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Number of Z axis objecs", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
