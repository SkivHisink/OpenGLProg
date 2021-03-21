#pragma once
#pragma once
#include <GL/gl.h>
#include <qmatrix4x4.h>

class Camera final
{
public:
	QVector3D cameraPos = QVector3D(0.0f, 0.0f, 3.0f);
	QVector3D cameraFront = QVector3D(0.0f, 0.0f, -1.0f);
	QVector3D cameraUp = QVector3D(0.0f, 1.0f, 0.0f);
	QVector3D camera = { 0.f, 0.f, 5.f };
	GLfloat yaw = -90.0f;
	GLfloat pitch = 0.0f;
	float FOV = 60.0f;
	float aspectRatio = 4.0f / 3.0f;
	QMatrix4x4 getProjectionMatrix()
	{
		QMatrix4x4 projection;
		projection.perspective(FOV, aspectRatio, 0.1f, 100.0f);
		return projection;
	}
	QMatrix4x4 getViewMatrix() const
	{
		QMatrix4x4 view;
		view.lookAt(cameraPos, (cameraPos + cameraFront), cameraUp);
		return view;
	}

};
