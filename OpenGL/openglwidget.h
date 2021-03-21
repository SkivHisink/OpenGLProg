#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
//
#include "cube.h"
#include "Camera.h"
#include "KeyBoard.h"
#include <QSlider>

#include <chrono>

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT
public:
	bool initialized = false;
	using QOpenGLWidget::QOpenGLWidget;
	OpenGLWidget();
	~OpenGLWidget();
	void setProp(const double prop_n) {
		prop = prop_n;
	}
	void setMorphType(const int mt_n) {
		morph_type = mt_n;
	}
	void setFigureFill(const bool fill_n) {
		figure_fill = fill_n;
	}
	void setFigureLine(const bool line_n) {
		figure_line = line_n;
	}
	void setDepthState(const bool depth_n) {
		depth_state = depth_n;
	}
	void setCullingState(const bool cull_n) {
		culling_state = cull_n;
	}
	double getFPS() {
		return fps;
	}
	void setNumberOfObjectsX(const int val_n) {
		nox = val_n;
	}
	void setNumberOfObjectsY(const int val_n) {
		noy = val_n;
	}
	void setNumberOfObjectsZ(const int val_n) {
		noz = val_n;
	}
protected:
	void mousePressEvent(QMouseEvent* e) override;
	void mouseReleaseEvent(QMouseEvent* e) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void timerEvent(QTimerEvent* e) override;
	void keyPressEvent(QKeyEvent* event) override;
	void keyReleaseEvent(QKeyEvent* event) override;
	void initialize();
	void initializeGL() override;
	// void resizeGL(int w, int h) override;
	void paintGL() override;
	void setAnimating(bool animating);
	//  void initShaders();
	//  void initTextures();
	void keyevent();
public slots:
	void setXRotation(int angle);
	void setYRotation(int angle);
	void setZRotation(int angle);
	void updateFPS();
signals:
	void xRotationChanged(int angle);
	void yRotationChanged(int angle);
	void zRotationChanged(int angle);
	void showFPS();

private:
	void middle_point(int i, int j, int* max_indx);
	QBasicTimer timer;

	GLfloat color_change = 0.0f;
	QOpenGLShaderProgram* m_program = nullptr;
	QVector2D mousePressPosition;
	QVector2D mouseLastPosition;
	int m_frame = 0;

	QVector3D rotationAxis;
	qreal angularSpeed = 0;
	QQuaternion rotation;
	float x_coord = 0;
	float y_coord = 0;
	float z_coord = -4;
	int m_xRot = 0;
	int m_yRot = 0;
	int m_zRot = 0;

	//
	Cube* cube;

	//
	float prop = 0.0;
	int morph_type = 0;
	bool figure_fill = true;
	bool figure_line = false;
	bool depth_state = true;
	bool culling_state = true;
	//keycontrol
	KeyBoard keyboard;
	//
	double fps = 0.0;
	std::chrono::high_resolution_clock::time_point begin;
	int nox = 1;
	int noy = 1;
	int noz = 1;
	std::vector<Qt::Key> key_map = {
		Qt::Key_Escape,  Qt::Key_F1, Qt::Key_PageUp, Qt::Key_PageDown, Qt::Key_R,
		Qt::Key_R , Qt::Key_F, Qt::Key_T,  Qt::Key_G , Qt::Key_Y , Qt::Key_H , Qt::Key_U,
		Qt::Key_J , Qt::Key_Z, Qt::Key_X, Qt::Key_W, Qt::Key_A, Qt::Key_S,  Qt::Key_D ,
		Qt::Key_Q , Qt::Key_E, Qt::Key_C, Qt::Key_V, Qt::Key_B, Qt::Key_1, Qt::Key_2,
		Qt::Key_3, Qt::Key_4, Qt::Key_5, Qt::Key_6, Qt::Key_7, Qt::Key_8, Qt::Key_9, Qt::Key_0 };
	//camera
	Camera camera;
	//light
	Cube* light;
	QVector3D lightPos = QVector3D(0.0f, 5.0f, 0.0f);
	QVector3D lightColor = QVector3D(1.0f, 1.0f, 1.0f);
};

#endif // OPENGLWIDGET_H