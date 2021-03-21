#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QObject>
#include <QSlider>
#include <QSpinBox>
#include <QLabel>
#include <sstream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //for moving x axis
    connect(ui->XSlider, &QSlider::valueChanged, ui->widget, &OpenGLWidget::setXRotation);
    connect(ui->widget, &OpenGLWidget::xRotationChanged, ui->XSlider, &QSlider::setValue);
    //for moving y axis
    connect(ui->YSlider, &QSlider::valueChanged, ui->widget, &OpenGLWidget::setYRotation);
    connect(ui->widget, &OpenGLWidget::yRotationChanged, ui->YSlider, &QSlider::setValue);
    ////for moving z axis
    connect(ui->ZSlider, &QSlider::valueChanged, ui->widget, &OpenGLWidget::setZRotation);
    connect(ui->widget, &OpenGLWidget::zRotationChanged, ui->ZSlider, &QSlider::setValue);
	//
    connect(ui->FillBox, &QCheckBox::stateChanged, this, &MainWindow::FillMode);
    connect(ui->LineBox, &QCheckBox::stateChanged, this, &MainWindow::FillMode);
    connect(ui->DCBox, &QCheckBox::stateChanged, this, &MainWindow::FillMode);
    connect(ui->CullingBox, &QCheckBox::stateChanged, this, &MainWindow::FillMode);
    //
    connect(ui->widget,&OpenGLWidget::showFPS, this, &MainWindow::showFPS);
    //Numbers of objects on scene
    connect(ui->NumbersOfObjectsX, &QSlider::valueChanged, this, &MainWindow::changeNumberOfObj);
    connect(ui->NumbersOfObjectsY, &QSlider::valueChanged, this, &MainWindow::changeNumberOfObj);
    connect(ui->NumbersOfObjectsZ, &QSlider::valueChanged, this, &MainWindow::changeNumberOfObj);
    //for AmbientStregth
    connect(ui->AmbientStrengthSlider, &QSlider::valueChanged, ui->widget, &OpenGLWidget::setAmbientStregth);
    connect(ui->widget, &OpenGLWidget::ambientStregthChanged, ui->AmbientStrengthSlider, &QSlider::setValue);
	//for SpecularStregth
    connect(ui->SpecularStrength, &QSlider::valueChanged, ui->widget, &OpenGLWidget::setSpecularStrength);
    connect(ui->widget, &OpenGLWidget::specularStrengthChanged, ui->SpecularStrength, &QSlider::setValue);
    //for diffeseStregth
    connect(ui->diffuseSlider, &QSlider::valueChanged, ui->widget, &OpenGLWidget::setDiffuseStrength);
    connect(ui->widget, &OpenGLWidget::DiffuseChanged, ui->diffuseSlider, &QSlider::setValue);
	//
    connect(ui->AttenuationConstantSlider, &QSlider::valueChanged, ui->widget, &OpenGLWidget::setCAttenuation);
    connect(ui->widget, &OpenGLWidget::CAttenuationChanged, ui->AttenuationConstantSlider, &QSlider::setValue);
    //for SpecularStregth
    connect(ui->AttenuationLinearSlider, &QSlider::valueChanged, ui->widget, &OpenGLWidget::setLAttenuation);
    connect(ui->widget, &OpenGLWidget::LAttenuationChanged, ui->AttenuationLinearSlider, &QSlider::setValue);
    //for diffeseStregth
    connect(ui->AttenuationSquareSlider, &QSlider::valueChanged, ui->widget, &OpenGLWidget::setSAttenuation);
    connect(ui->widget, &OpenGLWidget::SAttenuationChanged, ui->AttenuationSquareSlider, &QSlider::setValue);
    //for Material
    connect(ui->MaterialSlider, &QSlider::valueChanged, ui->widget, &OpenGLWidget::setMaterial);
    connect(ui->widget, &OpenGLWidget::MaterialChanged, ui->MaterialSlider, &QSlider::setValue);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeNumberOfObj()
{
    ui->widget->setNumberOfObjectsX(ui->NumbersOfObjectsX->value());
    ui->widget->setNumberOfObjectsY(ui->NumbersOfObjectsY->value());
    ui->widget->setNumberOfObjectsZ(ui->NumbersOfObjectsZ->value());
}

void MainWindow::showFPS()
{
    std::string lel="FPS:"+std::to_string(ui->widget->getFPS());
    ui->label_fps->clear();
    ui->label_fps->setText(lel.c_str());
    ui->label_fps->update();
}

void MainWindow::FillMode()
{
    ui->widget->setFigureFill(ui->FillBox->checkState());
    ui->widget->setFigureLine(ui->LineBox->checkState());
    ui->widget->setDepthState(ui->DCBox->checkState());
    ui->widget->setCullingState(ui->CullingBox->checkState());
}
