#include "openglwidget.h"

#include <QGuiApplication>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QScreen>
#include <QtMath>
#include <QKeyEvent>
#include "AssimpLoader.h"
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
	float tmp = static_cast<float>(val) / 1000;
	if (tmp != ambientStrength) {
		ambientStrength = tmp;
	}
}
void OpenGLWidget::setSpecularStrength(int val)
{
	float tmp = static_cast<float>(val) / 100;
	if (tmp != specularStrength) {
		specularStrength = tmp;
	}
}
void OpenGLWidget::setDiffuseStrength(int val)
{
	float tmp = static_cast<float>(val) / 100;
	if (tmp != diffuseStrength) {
		diffuseStrength = tmp;
	}
}
void OpenGLWidget::setCAttenuation(int val)
{
	float tmp = static_cast<float>(val) / 100;
	if (tmp != attenuationConstant) {
		attenuationConstant = tmp;
	}
}
void OpenGLWidget::setLAttenuation(int val)
{
	float tmp = static_cast<float>(val) / 100;
	if (tmp != attenuationLinear) {
		attenuationLinear = tmp;
	}
}
void OpenGLWidget::setSAttenuation(int val)
{
	float tmp = static_cast<float>(val) / 100;
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
	float tmp = static_cast<float>(val) / 10;
	if (tmp != rotate_speed) {
		rotate_speed = tmp;
	}
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
void OpenGLWidget::simple_init(SceneObject* obj, bool init_normals)
{
	obj->initProg(this);
	obj->initShaders("shaders\\SimpleObj.vs", "shaders\\SimpleObj.fs");
	obj->initObj(this);
	if (init_normals)
		obj->initNormal();
	obj->enableAndSetAttribute();
}

void  OpenGLWidget::obj_init(SceneObject* obj, bool init_normals)
{
	obj->initProg(this);
	obj->initShaders("shaders\\ObjTexture.vs", "shaders\\ObjWithLightAndTexture.fs");
	obj->initObj(this);
	obj->enableAndSetAttribute();
}
Cube* task5(OpenGLWidget* it_widget, int i)
{
	Cube* obj = new Cube();
	obj->initProg(it_widget);
	obj->initNormal();
	obj->initShaders("shaders\\Task5.vs", "shaders\\Task5.fs");
	obj->initObj(it_widget);
	obj->enableAndSetAttribute();
	int val = obj->getIndices().size() - 6;
	for (int i = 0; i < val; ++i)
		obj->getIndices().pop_back();
	val = obj->getVertices().size() - 4 * obj->getDataLen();
	for (int i = 0; i < val; ++i)
		obj->getVertices().pop_back();
	obj->getVertices()[0 + 1] = obj->getVertices()[0 + 1] * 100;
	obj->getVertices()[3 * obj->getDataLen() + 1] = obj->getVertices()[3 * obj->getDataLen() + 1] * 100;
	obj->getVertices()[1 * obj->getDataLen() + 1] = obj->getVertices()[1 * obj->getDataLen() + 1] * 100;
	obj->getVertices()[2 * obj->getDataLen() + 1] = obj->getVertices()[2 * obj->getDataLen() + 1] * 100;
	obj->getVertices()[0] += i;
	obj->getVertices()[1 * obj->getDataLen()] += i;
	obj->getVertices()[2 * obj->getDataLen()] += i;
	obj->getVertices()[3 * obj->getDataLen()] += i;
	obj->getVertices()[0 * obj->getDataLen() + 2] -= 5;
	obj->getVertices()[1 * obj->getDataLen() + 2] -= 5;
	obj->getVertices()[2 * obj->getDataLen() + 2] -= 5;
	obj->getVertices()[3 * obj->getDataLen() + 2] -= 5;

	return obj;
}
void OpenGLWidget::initialize()
{
	//main object of scene
	AssimpLoader load;
	//
	load.loadModel("materials\\MeshSphere.obj");
	SceneObject* obj = load.getObj();
	obj->resize(6);
	obj_init(obj, false);
	obj->addTexture("materials\\Earth_Albedo.jpg");
	obj->addTexture("materials\\Earth_Albedo.jpg");
	obj->addTexture("materials\\Earth_NormalMap.jpg");
	cube = static_cast<Cube*>(obj);
	//0
	load.loadModel("materials\\MeshCube.obj");
	obj = load.getObj();
	obj_init(obj, false);
	obj->addTexture("container2.png");
	obj->addTexture("container2_specular.png");
	obj->addTexture("NormalMap.png");
	obj_cont.push_back(obj);
	//1
	load.loadModel("materials\\MeshHouse.obj");
	obj = load.getObj();
	obj_init(obj, false);
	obj->addTexture("container2.png");
	obj->addTexture("container2_specular.png");
	obj->addTexture("NormalMap.png");
	obj_cont.push_back(obj);
	//
	/*load.loadModel("materials\\buggatti2.obj");
	obj = load.getObj();
	obj_init(obj, false);
	obj->addTexture("container2.png");
	obj->addTexture("container2_specular.png");
	obj->addTexture("NormalMap.png");
	obj_cont.push_back(obj);*/
	//2
	obj = task5(this, 0);
	obj->addTexture("materials\\sand.jpg",
		QOpenGLTexture::Nearest,
		QOpenGLTexture::Nearest);
	obj_cont.push_back(obj);
	//3
	obj = task5(this, 2);
	obj->addTexture("materials\\sand.jpg",
		QOpenGLTexture::LinearMipMapNearest,
		QOpenGLTexture::LinearMipMapNearest);
	obj_cont.push_back(obj);
	//4
	obj = task5(this, 4);
	obj->addTexture("materials\\sand.jpg",
		QOpenGLTexture::LinearMipMapLinear,
		QOpenGLTexture::Linear);
	obj_cont.push_back(obj);
	//5
	obj = task5(this, 6);
	obj->addTexture("materials\\sand.jpg",
		QOpenGLTexture::LinearMipMapLinear,
		QOpenGLTexture::Linear);
	obj_cont.push_back(obj);
	//6
	obj = task5(this, 8);
	obj->addTexture("materials\\road_1.jpg",
		QOpenGLTexture::LinearMipMapLinear,
		QOpenGLTexture::Linear);
	obj_cont.push_back(obj);
	//7
	obj = task5(this, 10);
	obj->addTexture("materials\\road_1.jpg",
		QOpenGLTexture::LinearMipMapLinear,
		QOpenGLTexture::Linear);
	obj->addTexture("materials\\road_2.jpg",
		QOpenGLTexture::LinearMipMapLinear,
		QOpenGLTexture::Linear);
	obj_cont.push_back(obj);
	//8
	obj = task5(this, 12);
	obj->addTexture("materials\\road_1.jpg",
		QOpenGLTexture::LinearMipMapLinear,
		QOpenGLTexture::Linear);
	obj->addTexture("materials\\road_2.jpg",
		QOpenGLTexture::LinearMipMapLinear,
		QOpenGLTexture::Linear);
	obj->addTexture("materials\\road_3.jpg",
		QOpenGLTexture::LinearMipMapLinear,
		QOpenGLTexture::Linear);
	obj_cont.push_back(obj);
	//light
	light = new Cube();
	simple_init(light, false);
	second_light = new Cube();
	simple_init(second_light, false);
	//init keyboard control
	keyboard = new KeyBoard();
	// Use QBasicTimer because its faster than QTimer
	timer.start(12, this);
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
	texture = new QOpenGLTexture(QImage("materials\\Earth_Albedo.jpg").mirrored());
	texture2 = new QOpenGLTexture(QImage("materials\\Earth_Albedo.jpg").mirrored());
	texture3 = new QOpenGLTexture(QImage("materials\\Earth_NormalMap.jpg").mirrored());
	// Set nearest filtering mode for texture minification
	texture->setMinificationFilter(QOpenGLTexture::Nearest);
	texture2->setMinificationFilter(QOpenGLTexture::Nearest);
	texture3->setMinificationFilter(QOpenGLTexture::Nearest);

	// Set bilinear filtering mode for texture magnification
	texture->setMagnificationFilter(QOpenGLTexture::Linear);
	texture2->setMagnificationFilter(QOpenGLTexture::Linear);
	texture3->setMagnificationFilter(QOpenGLTexture::Linear);

	// Wrap texture coordinates by repeating
	// f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
	texture->setWrapMode(QOpenGLTexture::Repeat);
	texture2->setWrapMode(QOpenGLTexture::Repeat);
	texture3->setWrapMode(QOpenGLTexture::Repeat);
}

void OpenGLWidget::drawMainObj(SceneObject* obj_)
{
	obj_->getProgram()->bind();
	std::vector<QMatrix4x4> trate_cont;//translate+rotate=trate
	for (int i = 0; i < nox; ++i) {
		for (int j = 0; j < noy; ++j) {
			for (int k = 0; k < noz; ++k) {
				QMatrix4x4 mat1;
				mat1.translate(pow(-1, i) * 5 * ((i + 1) / 2), pow(-1, k) * 5 * ((k + 1) / 2), -j * 5);
				mat1.rotate(rotation);
				mat1.rotate(180.0f - (m_xRot / 16.0f), 1, 0, 0);
				mat1.rotate(m_yRot / 16.0f, 0, 1, 0);
				mat1.rotate(m_zRot / 16.0f, 0, 0, 1);
				trate_cont.push_back(mat1);
			}
		}
	}
	obj_->getProgram()->setUniformValue("viewPos", camera.cameraPos);
	obj_->getProgram()->setUniformValue("lightPos", lightPos);
	obj_->getProgram()->setUniformValue("lightColor", lightColor);
	obj_->getProgram()->setUniformValue("view", camera.getViewMatrix());
	obj_->getProgram()->setUniformValue("projection", camera.getProjectionMatrix());
	obj_->getProgram()->setUniformValue("strength", QVector3D(ambientStrength, specularStrength, diffuseStrength));
	obj_->getProgram()->setUniformValue("attenuationParam", QVector3D(attenuationConstant, attenuationLinear, attenuationSquare));
	obj_->getProgram()->setUniformValue("material.ambient", material.ambient[0], material.ambient[1], material.ambient[2]);
	glActiveTexture(GL_TEXTURE0);
	obj_->texture_cont[0].texture->bind();
	cube->getProgram()->setUniformValue("material.diffuse", 0);
	glActiveTexture(GL_TEXTURE1);
	obj_->texture_cont[1].texture->bind();
	cube->getProgram()->setUniformValue("material.specular", 1);
	glActiveTexture(GL_TEXTURE2);
	obj_->texture_cont[2].texture->bind();
	obj_->getProgram()->setUniformValue("textureNormalMap", 2);
	obj_->getProgram()->setUniformValue("material.shininess", material.shininess);
	obj_->getProgram()->setUniformValue("slightPos", sl_lightPos);
	obj_->getProgram()->setUniformValue("slightColor", sl_lightColor);
	obj_->getProgram()->setUniformValue("dirLight.direction", camera.cameraPos);
	obj_->getProgram()->setUniformValue("dirLight.ambient", 0.3f, 0.24f, 0.14f);
	obj_->getProgram()->setUniformValue("dirLight.diffuse", 0.7f, 0.42f, 0.26f);
	obj_->getProgram()->setUniformValue("dirLight.specular", 0.5f, 0.5f, 0.5f);

	obj_->getVao()->bind();
	obj_->getVbo()->bind();

	obj_->getVbo()->write(0, obj_->getVertices().data(), obj_->getVertices().size() * sizeof(float));
	for (auto trate : trate_cont) {
		obj_->getProgram()->setUniformValue("model", trate);
		glDrawElements(GL_TRIANGLES, obj_->getIndices().size(), GL_UNSIGNED_INT, 0);
	}
	obj_->getVao()->release();
	obj_->getProgram()->release();
}
void OpenGLWidget::drawotherObj(SceneObject* obj_, QVector3D trans)
{
	obj_->getProgram()->bind();

	QMatrix4x4 mat1;
	mat1.translate(trans);
	mat1.rotate(rotation);
	mat1.rotate(180.0f - (m_xRot / 16.0f), 1, 0, 0);
	mat1.rotate(m_yRot / 16.0f, 0, 1, 0);
	mat1.rotate(m_zRot / 16.0f, 0, 0, 1);


	obj_->getProgram()->setUniformValue("viewPos", camera.cameraPos);
	obj_->getProgram()->setUniformValue("lightPos", lightPos);
	obj_->getProgram()->setUniformValue("lightColor", lightColor);
	obj_->getProgram()->setUniformValue("view", camera.getViewMatrix());
	obj_->getProgram()->setUniformValue("projection", camera.getProjectionMatrix());
	obj_->getProgram()->setUniformValue("strength", QVector3D(ambientStrength, specularStrength, diffuseStrength));
	obj_->getProgram()->setUniformValue("attenuationParam", QVector3D(attenuationConstant, attenuationLinear, attenuationSquare));
	obj_->getProgram()->setUniformValue("material.ambient", material.ambient[0], material.ambient[1], material.ambient[2]);
	glActiveTexture(GL_TEXTURE0);
	obj_->texture_cont[0].texture->bind();
	cube->getProgram()->setUniformValue("material.diffuse", 0);
	glActiveTexture(GL_TEXTURE1);
	obj_->texture_cont[1].texture->bind();
	cube->getProgram()->setUniformValue("material.specular", 1);
	glActiveTexture(GL_TEXTURE2);
	obj_->texture_cont[2].texture->bind();
	obj_->getProgram()->setUniformValue("textureNormalMap", 2);
	obj_->getProgram()->setUniformValue("material.shininess", material.shininess);
	obj_->getProgram()->setUniformValue("slightPos", sl_lightPos);
	obj_->getProgram()->setUniformValue("slightColor", sl_lightColor);
	obj_->getProgram()->setUniformValue("dirLight.direction", camera.cameraPos);
	obj_->getProgram()->setUniformValue("dirLight.ambient", 0.3f, 0.24f, 0.14f);
	obj_->getProgram()->setUniformValue("dirLight.diffuse", 0.7f, 0.42f, 0.26f);
	obj_->getProgram()->setUniformValue("dirLight.specular", 0.5f, 0.5f, 0.5f);

	obj_->getVao()->bind();
	obj_->getVbo()->bind();

	obj_->getVbo()->write(0, obj_->getVertices().data(), obj_->getVertices().size() * sizeof(float));

	obj_->getProgram()->setUniformValue("model", mat1);
	glDrawElements(GL_TRIANGLES, obj_->getIndices().size(), GL_UNSIGNED_INT, 0);

	obj_->getVao()->release();
	obj_->getProgram()->release();
}
void OpenGLWidget::SimpledrawObj(SceneObject* obj_, QVector3D trans, QVector3D color)
{
	obj_->getProgram()->bind();
	QMatrix4x4 mat1 = QMatrix4x4();
	mat1.setToIdentity();
	mat1.translate(trans);
	obj_->getProgram()->setUniformValue("view", camera.getViewMatrix());
	obj_->getProgram()->setUniformValue("projection", camera.getProjectionMatrix());
	obj_->getProgram()->setUniformValue("model", mat1);
	obj_->getProgram()->setUniformValue("color", color);
	obj_->getVao()->bind();
	obj_->getVbo()->bind();
	obj_->getVbo()->write(0, obj_->getVertices().data(), obj_->getVertices().size() * sizeof(float));
	glDrawElements(GL_TRIANGLES, obj_->getIndices().size(), GL_UNSIGNED_INT, 0);
	obj_->getVao()->release();
}
void OpenGLWidget::Task5Obj(SceneObject* obj_, bool anisotropy)
{
	obj_->getProgram()->bind();

	QMatrix4x4 mat1;
	mat1.rotate(rotation);
	mat1.rotate(180.0f - (m_xRot / 16.0f), 1, 0, 0);
	mat1.rotate(m_yRot / 16.0f, 0, 1, 0);
	mat1.rotate(m_zRot / 16.0f, 0, 0, 1);

	QVector3D text_exist={0,0,0};
	obj_->getProgram()->setUniformValue("viewPos", camera.cameraPos);
	obj_->getProgram()->setUniformValue("lightPos", lightPos);
	obj_->getProgram()->setUniformValue("lightColor", lightColor);
	obj_->getProgram()->setUniformValue("view", camera.getViewMatrix());
	obj_->getProgram()->setUniformValue("projection", camera.getProjectionMatrix());
	obj_->getProgram()->setUniformValue("strength", QVector3D(ambientStrength, specularStrength, diffuseStrength));
	obj_->getProgram()->setUniformValue("attenuationParam", QVector3D(attenuationConstant, attenuationLinear, attenuationSquare));
	obj_->getProgram()->setUniformValue("material.ambient", material.ambient[0], material.ambient[1], material.ambient[2]);
	glActiveTexture(GL_TEXTURE0);
	obj_->texture_cont[0].texture->bind();
	text_exist += {2, 0, 0};
	if (anisotropy)
	{
		float ans = 0.0f;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &ans);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, ans);
	}
	else
	{
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 0.0f);
	}
	cube->getProgram()->setUniformValue("textureroad1", 0);
	cube->getProgram()->setUniformValue("material.diffuse", material.diffuse[0], material.diffuse[1], material.diffuse[2]);
	cube->getProgram()->setUniformValue("material.specular", material.specular[0], material.specular[1], material.specular[2]);
	if (obj_->texture_cont.size() > 1) {
		glActiveTexture(GL_TEXTURE1);
		obj_->texture_cont[1].texture->bind();
		text_exist += {0, 2, 0};
		if (anisotropy)
		{
			float ans = 0.0f;
			glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &ans);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, ans);
		}
		else
		{
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 0.0f);
		}
		cube->getProgram()->setUniformValue("textureroad2", 1);
	}
	if (obj_->texture_cont.size() > 2) {
		glActiveTexture(GL_TEXTURE2);
		obj_->texture_cont[2].texture->bind();
		text_exist += {0, 0, 2};
		if (anisotropy)
		{
			float ans = 0.0f;
			glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &ans);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, ans);
		}
		else
		{
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 0.0f);
		}
		obj_->getProgram()->setUniformValue("textureroad3", 2);
	}
	obj_->getProgram()->setUniformValue("material.shininess", material.shininess);
	obj_->getProgram()->setUniformValue("textureExist", text_exist);
	obj_->getVao()->bind();
	obj_->getVbo()->bind();

	obj_->getVbo()->write(0, obj_->getVertices().data(), obj_->getVertices().size() * sizeof(float));

	obj_->getProgram()->setUniformValue("model", mat1);
	glDrawElements(GL_TRIANGLES, obj_->getIndices().size(), GL_UNSIGNED_INT, 0);

	obj_->getVao()->release();
	obj_->getProgram()->release();
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
	QMatrix4x4 matrix;

	matrix.translate(x_coord, y_coord, z_coord);
	//keyEvent
	keyevent();
	//drawMainObj(cube);
	drawotherObj(obj_cont[0], QVector3D(10, 10, 10));
	drawotherObj(obj_cont[1], QVector3D(10, 10, -10));
	//drawotherObj(obj_cont[2], QVector3D(10, -10, -10));
	//3
	Task5Obj(obj_cont[2], false);
	//4
	Task5Obj(obj_cont[3], false);
	//5
	Task5Obj(obj_cont[4], false);
	//6
	Task5Obj(obj_cont[5], true);
	//7
	Task5Obj(obj_cont[6], true);
	//7
	Task5Obj(obj_cont[7], true);
	//7
	Task5Obj(obj_cont[8], true);
	//
	SimpledrawObj(light, lightPos, lightColor);
	SimpledrawObj(second_light, sl_lightPos, sl_lightColor);
	++m_frame;
	//fps
	auto timet = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - begin);
	//lightPos = QQuaternion::fromAxisAndAngle({ 0,1,0 }, 0.8) * lightPos;
	lightPos = QVector3D(1.0f + +ligth_x_move, 10.0 + ligth_y_move, 10 + ligth_z_move);
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
