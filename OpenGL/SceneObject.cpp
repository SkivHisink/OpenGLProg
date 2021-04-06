#include "SceneObject.h"

void SceneObject::initNormal()
{
	for (int i = 0; i < indices.size(); i += 3)
	{
		float indx = indices[i] * dataLen;
		float indx2 = indices[i + 1] * dataLen;
		float indx3 = indices[i + 2] * dataLen;
		QVector3D tmp_1 = QVector3D(vertices[indx] - vertices[indx2],
			vertices[indx + 1] - vertices[indx2 + 1],
			vertices[indx + 2] - vertices[indx2 + 2]);
		QVector3D tmp_2 = QVector3D(vertices[indx2] - vertices[indx3],
			vertices[indx2 + 1] - vertices[indx3 + 1],
			vertices[indx2 + 2] - vertices[indx3 + 2]);
		QVector3D tmp_3 = QVector3D::crossProduct(tmp_1, tmp_2).normalized();
		vertices[indx + 3] = (tmp_3.x());
		vertices[indx + 4] = (tmp_3.y());
		vertices[indx + 5] = (tmp_3.z());
		vertices[indx2 + 3] = (tmp_3.x());
		vertices[indx2 + 4] = (tmp_3.y());
		vertices[indx2 + 5] = (tmp_3.z());
		vertices[indx3 + 3] = (tmp_3.x());
		vertices[indx3 + 4] = (tmp_3.y());
		vertices[indx3 + 5] = (tmp_3.z());
	}
}

void SceneObject::initObj(QObject* f)
{
	vao = new QOpenGLVertexArrayObject(f);
	vao->create();
	vao->bind();

	vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
	vbo->create();
	vbo->setUsagePattern(QOpenGLBuffer::DynamicDraw);
	vbo->bind();
	vbo->allocate(vertices.data(), vertices.size() * sizeof(float));

	ibo = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
	ibo->create();
	ibo->setUsagePattern(QOpenGLBuffer::DynamicDraw);
	ibo->bind();
	ibo->allocate(indices.data(), indices.size() * sizeof(GLuint));
}

void SceneObject::initProg(QObject* widget)
{
	m_program = new QOpenGLShaderProgram(widget);

}

void SceneObject::initShaders(std::string vertexPath, std::string fragmentPath)
{
	m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, vertexPath.c_str());
	m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, fragmentPath.c_str());
	m_program->link();
}

void SceneObject::addTexture(std::string texturePath, QOpenGLTexture::Filter mini_filter , QOpenGLTexture::Filter magni_filter, QOpenGLTexture::WrapMode wrap_mode)
{
	QOpenGLTexture* texture = new QOpenGLTexture(QImage(texturePath.c_str()).mirrored());
	// Set nearest filtering mode for texture minification
	texture->setMinificationFilter(mini_filter);

	// Set bilinear filtering mode for texture magnification
	texture->setMagnificationFilter(magni_filter);
	// Wrap texture coordinates by repeating
	// f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
	texture->setWrapMode(wrap_mode);
	texture_ temp = { texture, texturePath };
	texture_cont.push_back(temp);
}

std::vector<float>& SceneObject::getVertices()
{
	return vertices;
}

std::vector<GLuint>& SceneObject::getIndices()
{
	return indices;
}

const int SceneObject::getDataLen()
{
	return dataLen;
}

QOpenGLShaderProgram* SceneObject::getProgram()
{
	return m_program;
}

QOpenGLVertexArrayObject* SceneObject::getVao()
{
	return vao;
}

QOpenGLBuffer* SceneObject::getVbo()
{
	return vbo;
}

QOpenGLBuffer* SceneObject::getIbo()
{
	return ibo;
}

void SceneObject::enableAndSetAttribute()
{
	m_program->enableAttributeArray("posAttr");
	m_program->setAttributeBuffer("posAttr", GL_FLOAT, 0, 3, dataLen * sizeof(float));

	m_program->enableAttributeArray("normal");
	m_program->setAttributeBuffer("normal", GL_FLOAT, 3 * sizeof(float), 3, dataLen * sizeof(float));
	if (dataLen >= 8) {
		m_program->enableAttributeArray("aTexCoords");
		m_program->setAttributeBuffer("aTexCoords", GL_FLOAT, 6 * sizeof(float), 2, dataLen * sizeof(float));
	}
	if(dataLen>=14)
	{
		m_program->enableAttributeArray("tangens");
		m_program->setAttributeBuffer("tangens", GL_FLOAT, 8 * sizeof(float), 3, dataLen * sizeof(float));
		m_program->enableAttributeArray("bitangens");
		m_program->setAttributeBuffer("bitangens", GL_FLOAT, 11 * sizeof(float), 3, dataLen * sizeof(float));

	}
}
