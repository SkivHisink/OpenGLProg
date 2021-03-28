#pragma once
#include <vector>
#include <QOpenGLBuffer>
#include <vector>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>
#include <QVector3D>
#include <QOpenGLWidget>

class SceneObject
{
	struct texture_
	{
		QOpenGLTexture texture;
		std::string name;
	};
	std::vector<float> vertices;
	std::vector<GLushort> indices;
	std::vector<texture_> textures;
	int dataLen;
	QOpenGLVertexArrayObject* vao = nullptr;
	QOpenGLBuffer* vbo = nullptr;
	QOpenGLBuffer* ibo = nullptr;
	QOpenGLShaderProgram* m_program = nullptr;
public:
	void initNormal();
	void initObj(QObject* f);
	void initProg(QOpenGLWidget* widget);
	void initShaders(std::string vertexPath = "", std::string fragmentPath = "");
	void addTexture(std::string texturePath);
	//
	std::vector<float> getVertices();
	std::vector<GLushort> getIndices();
	int getDataLen();
};
