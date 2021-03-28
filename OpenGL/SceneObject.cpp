#include <SceneObject.h>

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
	ibo->allocate(indices.data(), indices.size() * sizeof(GLushort));
}

void SceneObject::initProg(QOpenGLWidget* widget)
{
	m_program = new QOpenGLShaderProgram(widget);
	
}

void SceneObject::initShaders(std::string vertexPath, std::string fragmentPath)
{
	m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, vertexPath.c_str());
	m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, fragmentPath.c_str());
	m_program->link();
}

void SceneObject::addTexture(std::string texturePath)
{
}

std::vector<float> SceneObject::getVertices()
{
	return vertices;
}

std::vector<GLushort> SceneObject::getIndices()
{
	return indices;
}

int SceneObject::getDataLen()
{
	return dataLen;
}
