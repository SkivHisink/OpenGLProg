#ifndef CUBE_H
#define CUBE_H
#include <QOpenGLBuffer>
#include <vector>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QVector3D>
class Cube
{
public:
	Cube();
	std::vector<float> vertices = {
		// front
		  -1.0, -1.0,  1.0, 0.5f, 0.5f, 0.5f,
		   1.0, -1.0,  1.0, 0.0f, 0.0f, 1.0f,
		   1.0,  1.0,  1.0, 0.0f, 1.0f, 0.0f,
		  -1.0,  1.0,  1.0, 0.0f, 1.0f, 1.0f,
		  // back
		  -1.0, -1.0, -1.0, 1.0f, 0.0f, 0.0f,
		   1.0, -1.0, -1.0, 1.0f, 0.0f, 1.0f,
		   1.0,  1.0, -1.0, 1.0f, 1.0f, 0.0f,
		  -1.0,  1.0, -1.0, 1.0f, 1.0f, 1.0f
	};
	std::vector<float> normal;
	std::vector<GLushort> indices = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	QOpenGLBuffer* vbo;
	QOpenGLBuffer* ibo;
	QOpenGLVertexArrayObject* vao;
	void init(QObject* f)
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
	void init_normal()
	{
		for (int i = 0; i < indices.size() / 6; ++i)
		{
			if (i + 1 < indices.size())
			{
				float indx = indices[i] * 6;
				QVector3D tmp_1 = QVector3D(vertices[indx], vertices[indx + 1], vertices[indx + 2]);
				QVector3D tmp_2 = QVector3D(vertices[indx + 6], vertices[indx + 7], vertices[indx + 8]);
				QVector3D tmp_3 = QVector3D::crossProduct(tmp_1, tmp_2);
				normal.push_back(tmp_3.x());
				normal.push_back(tmp_3.y());
				normal.push_back(tmp_3.z());
			}
			else
			{
				float indx = indices[i] * 6;
				QVector3D tmp_1 = QVector3D(vertices[indx], vertices[indx + 1], vertices[indx + 2]);
				QVector3D tmp_2 = QVector3D(vertices[indx - 6], vertices[indx - 5], vertices[indx - 4]);
				QVector3D tmp_3 = QVector3D::crossProduct(tmp_1, tmp_2).normalized();
				normal.push_back(tmp_3.x());
				normal.push_back(tmp_3.y());
				normal.push_back(tmp_3.z());
			}
		}
	}
	void setWhiteColot()
	{
		for (int i = 0; i < vertices.size() / 6; ++i)
		{
			vertices[i * 6 + 3] = 1;
			vertices[i * 6 + 4] = 1;
			vertices[i * 6 + 5] = 1;
		}
	}
};

#endif // CUBE_H
