#pragma once
#include <vector>
#include <QOpenGLBuffer>
#include <vector>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>

class SceneObject
{
protected:
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
	~SceneObject()
	{
		vbo->destroy();
		ibo->destroy();
	}
	void initNormal();
	void initObj(QObject* f);
	void initProg(QObject* widget);
	void initShaders(std::string vertexPath = "", std::string fragmentPath = "");
	void addTexture(std::string texturePath);
	//
	std::vector<float> getVertices();
	std::vector<GLushort> getIndices();
	int getDataLen();
	QOpenGLShaderProgram* getProgram() { return m_program; }
	QOpenGLVertexArrayObject* getVao() { return vao; }
	QOpenGLBuffer* getVbo() { return vbo; }
	QOpenGLBuffer* getIbo() { return ibo; }
	void enableAndSetAttribute();
};
