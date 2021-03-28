#include "openglwidget.h"

#include <QGuiApplication>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QScreen>
#include <QtMath>
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
void OpenGLWidget::setAmbientStregth(int val)
{
	float tmp = ((float)val) / 1000;
	if (tmp != ambientStrength) {
		ambientStrength = tmp;
	}
}
void OpenGLWidget::setSpecularStrength(int val)
{
	float tmp = ((float)val) / 100;
	if (tmp != specularStrength) {
		specularStrength = tmp;
	}
}
void OpenGLWidget::setDiffuseStrength(int val)
{
	float tmp = ((float)val) / 100;
	if (tmp != diffuseStrength) {
		diffuseStrength = tmp;
	}
}
void OpenGLWidget::setCAttenuation(int val)
{
	float tmp = ((float)val) / 100;
	if (tmp != attenuationConstant) {
		attenuationConstant = tmp;
	}
}
void OpenGLWidget::setLAttenuation(int val)
{
	float tmp = ((float)val) / 100;
	if (tmp != attenuationLinear) {
		attenuationLinear = tmp;
	}
}
void OpenGLWidget::setSAttenuation(int val)
{
	float tmp = ((float)val) / 100;
	if (tmp != attenuationSquare) {
		attenuationSquare = tmp;
	}
}
void OpenGLWidget::setMaterial(int val)
{
	if (val != numb_of_mat) {
		numb_of_mat = val;
		material = mC.material_collection[numb_of_mat];
	}
}
void OpenGLWidget::setRS(int val)
{
	float tmp = ((float)val) / 10;
	if (tmp != rotate_speed) {
		rotate_speed = tmp;
	}
}


void OpenGLWidget::initialize()
{
	//main object of scene
	cube = new Cube();
	cube->initProg(this);
	cube->initShaders("shaders\\ObjTexture.vs", "shaders\\ObjWithLightAndTexture.fs");
	//light
	light = new Cube();
	light->initProg(this);
	light->initShaders("shaders\\SimpleObj.vs", "shaders\\SimpleObj.fs");
	second_light = new Cube();
	second_light->initProg(this);
	second_light->initShaders("shaders\\SimpleObj.vs", "shaders\\SimpleObj.fs");
	//init keyboard control
	keyboard = new KeyBoard();
	// Use QBasicTimer because its faster than QTimer
	timer.start(12, this);
	//


	cube->initObj(this);
	cube->initNormal();
	cube->enableAndSetAttribute();
	light->initObj(this);
	light->initNormal();
	light->enableAndSetAttribute();
	second_light->initObj(this);
	second_light->initNormal();
	second_light->enableAndSetAttribute();
	//key control
	keyboard->pressed_button.assign(60, false);
	// light

	begin = std::chrono::high_resolution_clock::now();

	//texture
	initTextures();
}

void OpenGLWidget::initializeGL()
{
	initializeOpenGLFunctions();
	setFocusPolicy(Qt::StrongFocus);

}
void OpenGLWidget::initTextures()
{
	// Load cube.png image
	texture = new QOpenGLTexture(QImage("container2.png").mirrored());
	texture2 = new QOpenGLTexture(QImage("container2_specular.png").mirrored());
	// Set nearest filtering mode for texture minification
	texture->setMinificationFilter(QOpenGLTexture::Nearest);
	texture2->setMinificationFilter(QOpenGLTexture::Nearest);

	// Set bilinear filtering mode for texture magnification
	texture->setMagnificationFilter(QOpenGLTexture::Linear);
	texture2->setMagnificationFilter(QOpenGLTexture::Linear);

	// Wrap texture coordinates by repeating
	// f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
	texture->setWrapMode(QOpenGLTexture::Repeat);
	texture2->setWrapMode(QOpenGLTexture::Repeat);
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
double bft = 0;
void OpenGLWidget::paintGL()
{
	if (!initialized)
	{
		initialize();
		initialized = true;
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(120.0f / 256, 120.0f / 256, 120.0f / 256, 0.5f);
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
	//std::vector<GLfloat> ambient_matrial_red_plastic = { 0,0,0 };
	//glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_matrial_red_plastic.data());
	cube->getProgram()->bind();
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
	cube->getProgram()->setUniformValue("viewPos", camera.cameraPos);
	cube->getProgram()->setUniformValue("lightPos", lightPos);
	cube->getProgram()->setUniformValue("lightColor", lightColor);
	cube->getProgram()->setUniformValue("view", camera.getViewMatrix());
	cube->getProgram()->setUniformValue("projection", camera.getProjectionMatrix());
	cube->getProgram()->setUniformValue("strength", QVector3D(ambientStrength, specularStrength, diffuseStrength));
	cube->getProgram()->setUniformValue("attenuationParam", QVector3D(attenuationConstant, attenuationLinear, attenuationSquare));
	cube->getProgram()->setUniformValue("material.ambient", material.ambient[0], material.ambient[1], material.ambient[2]);
	glActiveTexture(GL_TEXTURE0);
	texture->bind();
	cube->getProgram()->setUniformValue("material.diffuse", 0);
	glActiveTexture(GL_TEXTURE1);
	texture2->bind();
	cube->getProgram()->setUniformValue("material.specular", 1);
	cube->getProgram()->setUniformValue("material.shininess", material.shininess);
	cube->getProgram()->setUniformValue("slightPos", sl_lightPos);
	cube->getProgram()->setUniformValue("slightColor", sl_lightColor);
	cube->getProgram()->setUniformValue("dirLight.direction", camera.cameraPos);
	cube->getProgram()->setUniformValue("dirLight.ambient", 0.3f, 0.24f, 0.14f);
	cube->getProgram()->setUniformValue("dirLight.diffuse", 0.7f, 0.42f, 0.26f);
	cube->getProgram()->setUniformValue("dirLight.specular", 0.5f, 0.5f, 0.5f);

	cube->getVao()->bind();
	cube->getVbo()->bind();

	cube->getVbo()->write(0, cube->getVertices().data(), cube->getVertices().size() * sizeof(float));
	for (auto trate : trate_cont) {
		cube->getProgram()->setUniformValue("model", trate);
		glDrawElements(GL_TRIANGLES, cube->getIndices().size(), GL_UNSIGNED_SHORT, 0);
	}
	cube->getVao()->release();
	cube->getProgram()->release();
	light->getProgram()->bind();
	QMatrix4x4 mat1 = QMatrix4x4();
	mat1.setToIdentity();
	mat1.translate(lightPos);
	light->getProgram()->setUniformValue("view", camera.getViewMatrix());
	light->getProgram()->setUniformValue("projection", camera.getProjectionMatrix());
	light->getProgram()->setUniformValue("model", mat1);
	light->getProgram()->setUniformValue("color", 1, 1, 1);
	light->getVao()->bind();
	light->getVbo()->bind();
	light->getVbo()->write(0, light->getVertices().data(), light->getVertices().size() * sizeof(float));
	glDrawElements(GL_TRIANGLES, light->getIndices().size(), GL_UNSIGNED_SHORT, 0);
	light->getVao()->release();

	second_light->getProgram()->bind();
	mat1 = QMatrix4x4();
	mat1.setToIdentity();
	mat1.translate(sl_lightPos);
	second_light->getProgram()->setUniformValue("view", camera.getViewMatrix());
	second_light->getProgram()->setUniformValue("projection", camera.getProjectionMatrix());
	second_light->getProgram()->setUniformValue("model", mat1);
	second_light->getProgram()->setUniformValue("color", 1, 0, 0);
	second_light->getVao()->bind();
	second_light->getVbo()->bind();
	second_light->getVbo()->write(0, second_light->getVertices().data(), second_light->getVertices().size() * sizeof(float));
	glDrawElements(GL_TRIANGLES, second_light->getIndices().size(), GL_UNSIGNED_SHORT, 0);
	second_light->getVao()->release();
	++m_frame;
	//fps
	auto timet = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - begin);
	lightPos = QVector3D(1.0f + sin(bft) * 2.0f + ligth_x_move, 10.0 + ligth_y_move, -40 + sin(bft / 2.0f) * 1.0f + ligth_z_move);
	bft += 0.01;
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
	format.setProfile(QSurfaceFormat::CompatibilityProfile);

	setFormat(format);
}

OpenGLWidget::~OpenGLWidget()
{
	makeCurrent();
	doneCurrent();
}

void OpenGLWidget::keyPressEvent(QKeyEvent* event)
{
	keyboard->keyPressEvent(event->key());
}

void OpenGLWidget::keyReleaseEvent(QKeyEvent* event)
{
	keyboard->keyReleaseEvent(event->key());
}

void OpenGLWidget::keyevent()
{
	if (keyboard->pressed_button[0])
	{
		close();
	}
	if (keyboard->pressed_button[1])
	{
		setWindowState(windowState() ^ Qt::WindowFullScreen);
	}
	if (keyboard->pressed_button[2])
	{
		color_change += 0.1f;
	}
	if (keyboard->pressed_button[3])
	{
		color_change -= 0.1f;
	}
	if (keyboard->pressed_button[4])//R
	{
		camera.FOV -= 1.0f;
	}
	if (keyboard->pressed_button[5])//F
	{
		camera.FOV += 1.0f;
	}
	if (keyboard->pressed_button[6])
	{
		rotation = QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), 1) * rotation;
	}
	if (keyboard->pressed_button[7])
	{
		rotation = QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), -1) * rotation;
	}
	if (keyboard->pressed_button[8])
	{
		rotation = QQuaternion::fromAxisAndAngle(QVector3D(0, 1, 0), 1) * rotation;
	}
	if (keyboard->pressed_button[9])
	{
		rotation = QQuaternion::fromAxisAndAngle(QVector3D(0, 1, 0), -1) * rotation;
	}
	if (keyboard->pressed_button[10])
	{
		rotation = QQuaternion::fromAxisAndAngle(QVector3D(0, 0, 1), 1) * rotation;
	}
	if (keyboard->pressed_button[11])
	{
		rotation = QQuaternion::fromAxisAndAngle(QVector3D(0, 0, 1), -1) * rotation;
	}
	if (keyboard->pressed_button[12])
	{
		camera.aspectRatio += 0.1f;
	}
	if (keyboard->pressed_button[13])
	{
		camera.aspectRatio -= 0.1f;
	}
	if (keyboard->pressed_button[14])
	{

	}
	GLfloat cameraSpeed = 0.3f;
	if (keyboard->pressed_button[15])
	{
		//z_coord += 0.1f;
		camera.cameraPos += cameraSpeed * camera.cameraFront;
	}
	if (keyboard->pressed_button[16])
	{
		QVector3D tmp = tmp.crossProduct(camera.cameraFront, camera.cameraUp);
		tmp.normalize();
		camera.cameraPos -= tmp * cameraSpeed;
	}
	if (keyboard->pressed_button[17])
	{
		//z_coord -= 0.1f;
		camera.cameraPos -= cameraSpeed * camera.cameraFront;
	}
	if (keyboard->pressed_button[18])
	{
		//x_coord -= 0.1f;
		QVector3D tmp = QVector3D::crossProduct(camera.cameraFront, camera.cameraUp).normalized();
		camera.cameraPos += tmp * cameraSpeed;
	}
	if (keyboard->pressed_button[19])
	{
		//y_coord += 0.1f;
		camera.cameraPos += QVector3D(0.0, -1.0 * cameraSpeed, 0.0);
	}
	if (keyboard->pressed_button[20])
	{
		//y_coord -= 0.1f;
		camera.cameraPos += QVector3D(0.0, 1.0 * cameraSpeed, 0.0);
	}
	if (keyboard->pressed_button[21])
	{
		rotation = QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), rotate_speed) * rotation;
	}
	if (keyboard->pressed_button[22])
	{
		rotation = QQuaternion::fromAxisAndAngle(QVector3D(0, 1, 0), rotate_speed) * rotation;
	}
	if (keyboard->pressed_button[23])
	{
		rotation = QQuaternion::fromAxisAndAngle(QVector3D(0, 0, 1), rotate_speed) * rotation;
	}
	if (keyboard->pressed_button[24])//1 is red
	{
	}
	if (keyboard->pressed_button[25])//2 is green
	{
	}
	if (keyboard->pressed_button[26])//3 is blue
	{
	}
	if (keyboard->pressed_button[27])//4 is aqua
	{
	}
	if (keyboard->pressed_button[28])//5 is pink
	{
	}
	if (keyboard->pressed_button[29])//6 is yellow
	{
	}
	if (keyboard->pressed_button[30])//7 is black and white
	{
	}
	if (keyboard->pressed_button[31])//8 is inverse black and white
	{
	}
	if (keyboard->pressed_button[32])//9 is color inversion
	{

	}
	if (keyboard->pressed_button[33])//return standart colors
	{

	}
	if (keyboard->pressed_button[37])
	{
		ligth_x_move += 0.2f;
	}
	if (keyboard->pressed_button[35])
	{
		ligth_x_move -= 0.2f;
	}
	if (keyboard->pressed_button[36])
	{
		ligth_z_move += 0.2f;
	}
	if (keyboard->pressed_button[34])
	{
		ligth_z_move -= 0.2f;
	}
	if (keyboard->pressed_button[38])
	{
		ligth_y_move += 0.2f;
	}
	if (keyboard->pressed_button[39])
	{
		ligth_y_move -= 0.2f;
	}
}
