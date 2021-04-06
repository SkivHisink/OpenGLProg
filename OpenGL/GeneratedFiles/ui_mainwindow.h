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
    QSlider *AmbientStrengthSlider;
    QSlider *SpecularStrength;
    QSlider *diffuseSlider;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QSlider *AttenuationConstantSlider;
    QSlider *AttenuationLinearSlider;
    QSlider *AttenuationSquareSlider;
    QSlider *MaterialSlider;
    QLabel *MaterialType;
    QLabel *NoOiS;
    QSlider *RSSlider;
    QLabel *label_4;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1851, 950);
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
        AmbientStrengthSlider = new QSlider(centralwidget);
        AmbientStrengthSlider->setObjectName(QString::fromUtf8("AmbientStrengthSlider"));
        AmbientStrengthSlider->setGeometry(QRect(1520, 550, 321, 22));
        AmbientStrengthSlider->setMaximum(5000);
        AmbientStrengthSlider->setPageStep(10);
        AmbientStrengthSlider->setValue(100);
        AmbientStrengthSlider->setOrientation(Qt::Horizontal);
        SpecularStrength = new QSlider(centralwidget);
        SpecularStrength->setObjectName(QString::fromUtf8("SpecularStrength"));
        SpecularStrength->setGeometry(QRect(1520, 590, 321, 22));
        SpecularStrength->setMaximum(1000);
        SpecularStrength->setValue(500);
        SpecularStrength->setOrientation(Qt::Horizontal);
        diffuseSlider = new QSlider(centralwidget);
        diffuseSlider->setObjectName(QString::fromUtf8("diffuseSlider"));
        diffuseSlider->setGeometry(QRect(1520, 630, 321, 22));
        diffuseSlider->setMaximum(10000);
        diffuseSlider->setValue(1000);
        diffuseSlider->setOrientation(Qt::Horizontal);
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(1520, 530, 171, 16));
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(1520, 570, 171, 16));
        label_10 = new QLabel(centralwidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(1520, 610, 171, 16));
        label_11 = new QLabel(centralwidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(1520, 660, 171, 16));
        label_12 = new QLabel(centralwidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(1530, 710, 171, 16));
        label_13 = new QLabel(centralwidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(1530, 680, 171, 16));
        label_14 = new QLabel(centralwidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(1530, 750, 171, 16));
        AttenuationConstantSlider = new QSlider(centralwidget);
        AttenuationConstantSlider->setObjectName(QString::fromUtf8("AttenuationConstantSlider"));
        AttenuationConstantSlider->setGeometry(QRect(1520, 690, 321, 22));
        AttenuationConstantSlider->setMaximum(5000);
        AttenuationConstantSlider->setValue(1000);
        AttenuationConstantSlider->setOrientation(Qt::Horizontal);
        AttenuationLinearSlider = new QSlider(centralwidget);
        AttenuationLinearSlider->setObjectName(QString::fromUtf8("AttenuationLinearSlider"));
        AttenuationLinearSlider->setGeometry(QRect(1520, 730, 321, 22));
        AttenuationLinearSlider->setMaximum(2500);
        AttenuationLinearSlider->setValue(300);
        AttenuationLinearSlider->setOrientation(Qt::Horizontal);
        AttenuationSquareSlider = new QSlider(centralwidget);
        AttenuationSquareSlider->setObjectName(QString::fromUtf8("AttenuationSquareSlider"));
        AttenuationSquareSlider->setGeometry(QRect(1520, 770, 321, 22));
        AttenuationSquareSlider->setMaximum(1000);
        AttenuationSquareSlider->setValue(100);
        AttenuationSquareSlider->setOrientation(Qt::Horizontal);
        MaterialSlider = new QSlider(centralwidget);
        MaterialSlider->setObjectName(QString::fromUtf8("MaterialSlider"));
        MaterialSlider->setGeometry(QRect(1510, 850, 331, 22));
        MaterialSlider->setMaximum(23);
        MaterialSlider->setValue(23);
        MaterialSlider->setOrientation(Qt::Horizontal);
        MaterialType = new QLabel(centralwidget);
        MaterialType->setObjectName(QString::fromUtf8("MaterialType"));
        MaterialType->setGeometry(QRect(1510, 830, 171, 16));
        NoOiS = new QLabel(centralwidget);
        NoOiS->setObjectName(QString::fromUtf8("NoOiS"));
        NoOiS->setGeometry(QRect(1540, 210, 171, 16));
        RSSlider = new QSlider(centralwidget);
        RSSlider->setObjectName(QString::fromUtf8("RSSlider"));
        RSSlider->setGeometry(QRect(1540, 140, 301, 16));
        RSSlider->setMinimum(-7200);
        RSSlider->setMaximum(7200);
        RSSlider->setSingleStep(16);
        RSSlider->setPageStep(240);
        RSSlider->setValue(10);
        RSSlider->setOrientation(Qt::Horizontal);
        RSSlider->setTickInterval(240);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(1540, 120, 221, 16));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1851, 21));
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
        label_8->setText(QCoreApplication::translate("MainWindow", "Ambient strength", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Specular strength", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Diffuse strength", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Attenuation", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "Linear", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "Constant", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "Square", nullptr));
        MaterialType->setText(QCoreApplication::translate("MainWindow", "Material Type:", nullptr));
        NoOiS->setText(QCoreApplication::translate("MainWindow", "Number of objects in scene:", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Rotation speed", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
