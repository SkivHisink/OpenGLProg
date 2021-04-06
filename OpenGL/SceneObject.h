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
		QOpenGLTexture* texture;
		std::string name;
	};
	std::vector<float> vertices;
	std::vector<GLuint> indices;
	int dataLen;
	QOpenGLVertexArrayObject* vao = nullptr;
	QOpenGLBuffer* vbo = nullptr;
	QOpenGLBuffer* ibo = nullptr;
	QOpenGLShaderProgram* m_program = nullptr;
public:
	std::vector<texture_> texture_cont;
	~SceneObject()
	{
		vbo->destroy();
		ibo->destroy();
	}
	void initNormal();
	void initObj(QObject* f);
	void initProg(QObject* widget);
	void initShaders(std::string vertexPath = "", std::string fragmentPath = "");
	void addTexture(std::string texturePath, QOpenGLTexture::Filter mini_filter = QOpenGLTexture::Nearest, QOpenGLTexture::Filter magni_filter = QOpenGLTexture::Linear, QOpenGLTexture::WrapMode wrap_mode = QOpenGLTexture::Repeat);
	//
	std::vector<float>& getVertices();
	std::vector<GLuint>& getIndices();
	const int getDataLen();
	QOpenGLShaderProgram* getProgram();
	QOpenGLVertexArrayObject* getVao();
	QOpenGLBuffer* getVbo();
	QOpenGLBuffer* getIbo();
	//
	void setDataLen(int dataLen_) { dataLen = dataLen_; }
	//
	void resize(int multi)
	{
		for (int i = 0; i < vertices.size() / dataLen; i += 1)
		{
			vertices[i * dataLen] *= multi;
			vertices[i * dataLen + 1] *= multi;
			vertices[i * dataLen + 2] *= multi;
		}

	}
	void enableAndSetAttribute();
};
