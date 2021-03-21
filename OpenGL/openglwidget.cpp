#include "openglwidget.h"

#include <QGuiApplication>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QScreen>
#include <QtMath>
#include <QMouseEvent>
#include <QKeyEvent>

static void qNormalizeAngle(int& angle)
{
	while (angle < 0)
		angle += 360 * 16;
	while (angle > 360 * 16)
		angle -= 360 * 16;
}

void OpenGLWidget::setXRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != m_xRot) {
		m_xRot = angle;
		emit xRotationChanged(angle);
		update();
	}
}

void OpenGLWidget::setYRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != m_yRot) {
		m_yRot = angle;
		emit yRotationChanged(angle);
		update();
	}
}

void OpenGLWidget::setZRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != m_zRot) {
		m_zRot = angle;
		emit zRotationChanged(angle);
		update();
	}
}
void OpenGLWidget::middle_point(int i, int j, int* max_indx)
{
	auto& vert = cube->vertices;
	auto ver_1_1 = vert[(i) * 6 + 0];
	auto ver_1_2 = vert[(j) * 6 + 0];
	auto ver_2_1 = vert[(i) * 6 + 1];
	auto ver_2_2 = vert[(j) * 6 + 1];
	auto ver_3_1 = vert[(i) * 6 + 2];
	auto ver_3_2 = vert[(j) * 6 + 2];

	vert.push_back((ver_1_1 + ver_1_2) / 2);
	vert.push_back((ver_2_1 + ver_2_2) / 2);
	vert.push_back((ver_3_1 + ver_3_2) / 2);
	vert.push_back(abs(vert[(i) * 6 + 3] + vert[(j) * 6 + 3]) / 2);
	vert.push_back(abs(vert[(i) * 6 + 4] + vert[(j) * 6 + 4]) / 2);
	vert.push_back(abs(vert[(i) * 6 + 5] + vert[(j) * 6 + 5]) / 2);

	++* max_indx;
}
int number_of_triangle_breaking(int num)
{
	int numb = 0;
	for (int i = 0; i < num; ++i) {
		numb = numb + static_cast<int>(6 * pow(2, 2 * i + 1));
	}
	return numb;
}

void OpenGLWidget::initialize()
{
	m_program = new QOpenGLShaderProgram(this);
	m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, "lightFragment.vs");
	m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, "fragment.fs");
	m_program->link();
	auto log = m_program->log();

	//m_program->log();
	// Use QBasicTimer because its faster than QTimer
	timer.start(12, this);
	//
	cube = new Cube();
	int max_indx = 8;
	auto& indxs = cube->indices;
	int numb_of_crop = number_of_triangle_breaking(3);//12 |60|252|1020|formula: prev+6*2^(iter_num+2)
	std::vector<float> new_vert;
	for (int i = 0; i < numb_of_crop; ++i) {
		middle_point(indxs[i * 3 + 0], indxs[i * 3 + 1], &max_indx);
		middle_point(indxs[i * 3 + 0], indxs[i * 3 + 2], &max_indx);
		middle_point(indxs[i * 3 + 1], indxs[i * 3 + 2], &max_indx);
		//
		cube->indices.push_back(indxs[i * 3 + 0]);
		cube->indices.push_back(max_indx - 3);
		cube->indices.push_back(max_indx - 2);
		//
		cube->indices.push_back(max_indx - 3);
		cube->indices.push_back(indxs[i * 3 + 1]);
		cube->indices.push_back(max_indx - 1);
		//
		cube->indices.push_back(max_indx - 1);
		cube->indices.push_back(max_indx - 2);
		cube->indices.push_back(max_indx - 3);
		//
		cube->indices.push_back(max_indx - 2);
		cube->indices.push_back(max_indx - 1);
		cube->indices.push_back(indxs[i * 3 + 2]);

	}
	for (int i = 0; i < numb_of_crop; ++i)
	{
		cube->indices.erase(cube->indices.begin());
		cube->indices.erase(cube->indices.begin());
		cube->indices.erase(cube->indices.begin());
	}

	cube->init(this);
	cube->init_normal();
	m_program->enableAttributeArray("posAttr");
	m_program->setAttributeBuffer("posAttr", GL_FLOAT, 0, 3, 6 * sizeof(float));

	m_program->enableAttributeArray("colAttr");
	m_program->setAttributeBuffer("colAttr", GL_FLOAT, 3 * sizeof(float), 3, 6 * sizeof(float));
	//key control

	light = new Cube();
	light->init(this);
	light->setWhiteColot();
	m_program->enableAttributeArray("posAttr");
	m_program->setAttributeBuffer("posAttr", GL_FLOAT, 0, 3, 6 * sizeof(float));

	m_program->enableAttributeArray("colAttr");
	m_program->setAttributeBuffer("colAttr", GL_FLOAT, 3 * sizeof(float), 3, 6 * sizeof(float));


	keyboard.pressed_button.assign(60, false);
	// light

	begin = std::chrono::high_resolution_clock::now();
}

void OpenGLWidget::initializeGL()
{
	initializeOpenGLFunctions();
	setFocusPolicy(Qt::StrongFocus);

}

void OpenGLWidget::mousePressEvent(QMouseEvent* e)
{
	mousePressPosition = QVector2D(e->localPos());
	if (e->button() == Qt::RightButton) {
		angularSpeed = 0;
	}
	if (e->buttons() & Qt::LeftButton) {
		mouseLastPosition = QVector2D(e->pos());
	}
}

void OpenGLWidget::mouseReleaseEvent(QMouseEvent* e)
{
	if (e->button() == Qt::RightButton) {
		// Mouse release position - mouse press position
		QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

		// Rotation axis is perpendicular to the mouse position difference
		// vector
		QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

		// Accelerate angular speed relative to the length of the mouse sweep
		qreal acc = diff.length() / 100.0;

		// Calculate new rotation axis as weighted sum
		rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

		// Increase angular speed
		angularSpeed += acc;
	}
}
void OpenGLWidget::mouseMoveEvent(QMouseEvent* event)
{
	if (event->buttons() & Qt::RightButton) {
		QVector2D diff = QVector2D(event->pos()) - mouseLastPosition;
		rotationAxis = QVector3D(diff.y(), diff.x(), 0.0).normalized();
		qreal angle = diff.length() / 4.0;
		rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angle) * rotation;
	}
	if (event->buttons() & Qt::LeftButton) {
		QVector2D diff = QVector2D(event->pos()) - mouseLastPosition;
		diff *= 0.1f;//sensitivity
		camera.yaw += diff.x();
		camera.pitch -= diff.y();
		if (camera.pitch > 89.0f)
			camera.pitch = 89.0f;
		if (camera.pitch < -89.0f)
			camera.pitch = -89.0f;
		QVector3D front = { cos(qDegreesToRadians(camera.pitch)) * cos(qDegreesToRadians(camera.yaw)) ,
			sin(qDegreesToRadians(camera.pitch)) ,
			cos(qDegreesToRadians(camera.pitch)) * sin(qDegreesToRadians(camera.yaw)) };
		camera.cameraFront = front.normalized();
	}
	if (event->buttons() & Qt::MiddleButton)
	{
		QVector2D diff = QVector2D(event->pos()) - mouseLastPosition;
		y_coord += diff.y() / 850;
		x_coord += diff.x() / 1500;
	}
	mouseLastPosition = QVector2D(event->pos());
}
void OpenGLWidget::timerEvent(QTimerEvent*)
{
	// Decrease angular speed (friction)
	angularSpeed *= 0.99;

	// Stop rotation when speed goes below threshold
	if (angularSpeed < 0.01) {
		angularSpeed = 0.0;
	}
	else {
		// Update rotation
		rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;
	}
	// Request an update
	update();
}

void OpenGLWidget::paintGL()
{
	if (!initialized)
	{
		initialize();
		initialized = true;
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (depth_state) {
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
	}
	else {
		glDisable(GL_DEPTH_TEST);
	}
	if (culling_state) {
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);//GL_BACK
	}
	else {
		glDisable(GL_CULL_FACE);
	}
	if (figure_fill) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	if (figure_line) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	if (figure_fill && figure_line)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_POLYGON_OFFSET_LINE);
		glPolygonOffset(1, 1);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	glShadeModel(GL_SMOOTH);
	m_program->bind();
	QMatrix4x4 matrix;
	std::vector<QMatrix4x4> trate_cont;//translate+rotate=trate
	for (int i = 0; i < nox; ++i) {
		for (int j = 0; j < noy; ++j) {
			for (int k = 0; k < noz; ++k) {
				QMatrix4x4 mat1;
				mat1.translate(pow(-1, i) * 4 * ((i + 1) / 2), pow(-1, k) * 4 * ((k + 1) / 2), -j * 4);
				mat1.rotate(rotation);
				mat1.rotate(180.0f - (m_xRot / 16.0f), 1, 0, 0);
				mat1.rotate(m_yRot / 16.0f, 0, 1, 0);
				mat1.rotate(m_zRot / 16.0f, 0, 0, 1);
				trate_cont.push_back(mat1);
			}
		}
	}
	matrix.translate(x_coord, y_coord, z_coord);
	//keyEvent
	keyevent();
	if (color_change != 0) {
		for (int i = 0; i < 8; ++i)
		{
			cube->vertices[i * 6 + 3] += color_change;
			cube->vertices[i * 6 + 4] += color_change;
			cube->vertices[i * 6 + 5] += color_change;
		}
		color_change = 0;
	}
	m_program->setUniformValue("viewPos", camera.cameraPos);
	m_program->setUniformValue("lightPos", lightPos);
	m_program->setUniformValue("lightColor", lightColor);
	m_program->setUniformValue("view", camera.getViewMatrix());
	m_program->setUniformValue("projection", camera.getProjectionMatrix());

	cube->vao->bind();
	cube->vbo->write(0, cube->vertices.data(), cube->vertices.size() * sizeof(float));
	for (auto trate : trate_cont) {
		m_program->setUniformValue("model", matrix * trate);
		glDrawElements(GL_TRIANGLES, cube->indices.size(), GL_UNSIGNED_SHORT, 0);
	}
	cube->vao->release();

	light->vao->bind();
	light->vbo->write(0, light->vertices.data(), light->vertices.size() * sizeof(float));
	QMatrix4x4 mat1 = QMatrix4x4();
	mat1.setToIdentity();
	mat1.translate(lightPos);
	m_program->setUniformValue("view", camera.getViewMatrix());
	m_program->setUniformValue("projection", camera.getProjectionMatrix());
	m_program->setUniformValue("model", matrix * mat1);
	glDrawElements(GL_TRIANGLES, light->indices.size(), GL_UNSIGNED_SHORT, 0);
	light->vao->release();

	m_program->release();

	++m_frame;
	//fps
	auto timet = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - begin);
	if (timet.count() > 0.5) {
		begin = std::chrono::high_resolution_clock::now();
		fps = static_cast<float>(m_frame) / timet.count();
		m_frame = 0;
		updateFPS();
	}
}

void OpenGLWidget::updateFPS() {
	emit showFPS();
}

OpenGLWidget::OpenGLWidget()
{
	QSurfaceFormat format;
	format.setSamples(16);
	format.setVersion(3, 3);
	format.setProfile(QSurfaceFormat::CoreProfile);

	setFormat(format);
}

OpenGLWidget::~OpenGLWidget()
{
	makeCurrent();
	doneCurrent();
	cube->vbo->destroy();
	cube->ibo->destroy();
	light->vbo->destroy();
	light->ibo->destroy();
}

void OpenGLWidget::keyPressEvent(QKeyEvent* event)
{
	keyboard.keyPressEvent(event->key());
}

void OpenGLWidget::keyReleaseEvent(QKeyEvent* event)
{
	keyboard.keyReleaseEvent(event->key());
}

void OpenGLWidget::keyevent()
{
	if (keyboard.pressed_button[0])
	{
		close();
	}
	if (keyboard.pressed_button[1])
	{
		setWindowState(windowState() ^ Qt::WindowFullScreen);
	}
	if (keyboard.pressed_button[2])
	{
		color_change += 0.1f;
	}
	if (keyboard.pressed_button[3])
	{
		color_change -= 0.1f;
	}
	if (keyboard.pressed_button[4])//R
	{
		camera.FOV -= 1.0f;
	}
	if (keyboard.pressed_button[5])//F
	{
		camera.FOV += 1.0f;
	}
	if (keyboard.pressed_button[6])
	{
		rotation = QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), 1) * rotation;
	}
	if (keyboard.pressed_button[7])
	{
		rotation = QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), -1) * rotation;
	}
	if (keyboard.pressed_button[8])
	{
		rotation = QQuaternion::fromAxisAndAngle(QVector3D(0, 1, 0), 1) * rotation;
	}
	if (keyboard.pressed_button[9])
	{
		rotation = QQuaternion::fromAxisAndAngle(QVector3D(0, 1, 0), -1) * rotation;
	}
	if (keyboard.pressed_button[10])
	{
		rotation = QQuaternion::fromAxisAndAngle(QVector3D(0, 0, 1), 1) * rotation;
	}
	if (keyboard.pressed_button[11])
	{
		rotation = QQuaternion::fromAxisAndAngle(QVector3D(0, 0, 1), -1) * rotation;
	}
	if (keyboard.pressed_button[12])
	{
		camera.aspectRatio += 0.1f;
	}
	if (keyboard.pressed_button[13])
	{
		camera.aspectRatio -= 0.1f;
	}
	if (keyboard.pressed_button[14])
	{

	}
	GLfloat cameraSpeed = 0.1f;
	if (keyboard.pressed_button[15])
	{
		//z_coord += 0.1f;
		camera.cameraPos += cameraSpeed * camera.cameraFront;
	}
	if (keyboard.pressed_button[16])
	{
		QVector3D tmp = tmp.crossProduct(camera.cameraFront, camera.cameraUp);
		tmp.normalize();
		camera.cameraPos -= tmp * cameraSpeed;
	}
	if (keyboard.pressed_button[17])
	{
		//z_coord -= 0.1f;
		camera.cameraPos -= cameraSpeed * camera.cameraFront;
	}
	if (keyboard.pressed_button[18])
	{
		//x_coord -= 0.1f;
		QVector3D tmp = QVector3D::crossProduct(camera.cameraFront, camera.cameraUp).normalized();
		camera.cameraPos += tmp * cameraSpeed;
	}
	if (keyboard.pressed_button[19])
	{
		y_coord += 0.1f;
	}
	if (keyboard.pressed_button[20])
	{
		y_coord -= 0.1f;
	}
	if (keyboard.pressed_button[21])
	{
		rotation = QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), 1) * rotation;
	}
	if (keyboard.pressed_button[22])
	{
		rotation = QQuaternion::fromAxisAndAngle(QVector3D(0, 1, 0), 1) * rotation;
	}
	if (keyboard.pressed_button[23])
	{
		rotation = QQuaternion::fromAxisAndAngle(QVector3D(0, 0, 1), 1) * rotation;
	}
	if (keyboard.pressed_button[24])//1 is red
	{
		for (int i = 0; i < cube->vertices.size() / 6; ++i)
		{
			cube->vertices[i * 6 + 3] = 1;
			cube->vertices[i * 6 + 4] = 0;
			cube->vertices[i * 6 + 5] = 0;
		}
	}
	if (keyboard.pressed_button[25])//2 is green
	{
		for (int i = 0; i < cube->vertices.size() / 6; ++i)
		{
			cube->vertices[i * 6 + 3] = 0;
			cube->vertices[i * 6 + 4] = 1;
			cube->vertices[i * 6 + 5] = 0;
		}
	}
	if (keyboard.pressed_button[26])//3 is blue
	{
		for (int i = 0; i < cube->vertices.size() / 6; ++i)
		{
			cube->vertices[i * 6 + 3] = 0;
			cube->vertices[i * 6 + 4] = 0;
			cube->vertices[i * 6 + 5] = 1;
		}
	}
	if (keyboard.pressed_button[27])//4 is aqua
	{
		for (int i = 0; i < cube->vertices.size() / 6; ++i)
		{
			cube->vertices[i * 6 + 3] = 0;
			cube->vertices[i * 6 + 4] = 1;
			cube->vertices[i * 6 + 5] = 1;
		}
	}
	if (keyboard.pressed_button[28])//5 is pink
	{
		for (int i = 0; i < cube->vertices.size() / 6; ++i)
		{
			cube->vertices[i * 6 + 3] = 1;
			cube->vertices[i * 6 + 4] = 0;
			cube->vertices[i * 6 + 5] = 1;
		}
	}
	if (keyboard.pressed_button[29])//6 is yellow
	{
		for (int i = 0; i < cube->vertices.size() / 6; ++i)
		{
			cube->vertices[i * 6 + 3] = 1;
			cube->vertices[i * 6 + 4] = 1;
			cube->vertices[i * 6 + 5] = 0;
		}
	}
	if (keyboard.pressed_button[30])//7 is black and white
	{
		for (int i = 0; i < cube->vertices.size() / 6; ++i)
		{
			cube->vertices[i * 6 + 3] = (float)i / 8;
			cube->vertices[i * 6 + 4] = (float)i / 8;
			cube->vertices[i * 6 + 5] = (float)i / 8;
		}
	}
	if (keyboard.pressed_button[31])//8 is inverse black and white
	{
		for (int i = 0; i < cube->vertices.size() / 6; ++i)
		{
			cube->vertices[i * 6 + 3] = 1.0 - (float)i / 8;
			cube->vertices[i * 6 + 4] = 1.0 - (float)i / 8;
			cube->vertices[i * 6 + 5] = 1.0 - (float)i / 8;
		}
	}
	if (keyboard.pressed_button[32])//9 is color inversion
	{
		for (int i = 0; i < cube->vertices.size() / 6; ++i)
		{
			cube->vertices[i * 6 + 3] = 1.0 - cube->vertices[i * 6 + 3];
			cube->vertices[i * 6 + 4] = 1.0 - cube->vertices[i * 6 + 4];
			cube->vertices[i * 6 + 5] = 1.0 - cube->vertices[i * 6 + 5];
		}
		keyboard.pressed_button[32] = !keyboard.pressed_button[32];
	}
	if (keyboard.pressed_button[33])//return standart colors
	{
		int a = 0;
		int b = 0;
		int c = 0;
		for (int i = 0; i < 48 / 6; ++i)
		{
			cube->vertices[i * 6 + 5] = a;
			cube->vertices[i * 6 + 4] = b;
			cube->vertices[i * 6 + 3] = c;
			++a;
			if (a == 2) {
				a = 0;
				++b;
				if (b == 2) {
					b = 0;
					++c;
				}
			}
		}
		for (int i = 48 / 6; i < cube->vertices.size() / 6; ++i) {
			cube->vertices[(i + 0) * 6 + 3] = abs(cube->vertices[(i - 5) * 6 + 3] + cube->vertices[(i - 6) * 6 + 3]) / 2;
			cube->vertices[(i + 0) * 6 + 4] = abs(cube->vertices[(i - 5) * 6 + 4] + cube->vertices[(i - 6) * 6 + 4]) / 2;
			cube->vertices[(i + 0) * 6 + 5] = abs(cube->vertices[(i - 5) * 6 + 5] + cube->vertices[(i - 6) * 6 + 5]) / 2;
		}
	}
}
