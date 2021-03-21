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
		-1.0, -1.0,  1.0, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, //0
		1.0, -1.0,  1.0, 0.0f, 0.0f, 1.0f, 0.5f, 0.5f, 0.5f,  //1
		1.0,  1.0,  1.0, 0.0f, 1.0f, 0.0f, 0.5f, 0.5f, 0.5f,  //2
		-1.0,  1.0,  1.0, 0.0f, 1.0f, 1.0f, 0.5f, 0.5f, 0.5f, //3
		// right											  
		1.0, -1.0,  1.0, 0.0f, 0.0f, 1.0f, 0.5f, 0.5f, 0.5f,  //4  - 1
		1.0, -1.0, -1.0, 1.0f, 0.0f, 1.0f, 0.5f, 0.5f, 0.5f,  //5  - 5
		1.0,  1.0, -1.0, 1.0f, 1.0f, 0.0f, 0.5f, 0.5f, 0.5f,  //6  - 6
		1.0,  1.0,  1.0, 0.0f, 1.0f, 0.0f, 0.5f, 0.5f, 0.5f,  //7  - 2
		// back												  	   - 
		-1.0,  1.0, -1.0, 1.0f, 1.0f, 1.0f, 0.5f, 0.5f, 0.5f, //8  - 7
		1.0,  1.0, -1.0, 1.0f, 1.0f, 0.0f, 0.5f, 0.5f, 0.5f,  //9  - 6
		1.0, -1.0, -1.0, 1.0f, 0.0f, 1.0f, 0.5f, 0.5f, 0.5f,  //10 - 5
		-1.0, -1.0, -1.0, 1.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.5f, //11 - 4
		// left												  	   - 
		-1.0, -1.0, -1.0, 1.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.5f, //12 - 4
		-1.0, -1.0,  1.0, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f,  //13 - 0
		-1.0,  1.0,  1.0, 0.0f, 1.0f, 1.0f, 0.5f, 0.5f, 0.5f,  //14 - 3
		-1.0,  1.0, -1.0, 1.0f, 1.0f, 1.0f, 0.5f, 0.5f, 0.5f, //15 - 7
		// bottom											  	   - 
		-1.0, -1.0, -1.0, 1.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.5f, //16 - 4
		1.0, -1.0, -1.0, 1.0f, 0.0f, 1.0f, 0.5f, 0.5f, 0.5f,  //17 - 5
		1.0, -1.0,  1.0, 0.0f, 0.0f, 1.0f, 0.5f, 0.5f, 0.5f,  //18 - 1
		-1.0, -1.0,  1.0, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, //19 - 0
		// top												  	   - 
		-1.0,  1.0,  1.0, 0.0f, 1.0f, 1.0f, 0.5f, 0.5f, 0.5f, //20 - 3
		1.0,  1.0,  1.0, 0.0f, 1.0f, 0.0f, 0.5f, 0.5f, 0.5f,  //21 - 2
		1.0,  1.0, -1.0, 1.0f, 1.0f, 0.0f, 0.5f, 0.5f, 0.5f,  //22 - 6
		-1.0,  1.0, -1.0, 1.0f, 1.0f, 1.0f, 0.5f, 0.5f, 0.5f, //23 - 7
	};
	std::vector<GLushort> indices = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		4, 5, 6,
		6, 7, 4,
		// back
		8, 9, 10,
		10, 11, 8,
		// left
		12, 13, 14,
		14, 15, 12,
		// bottom
		16, 17, 18,
		18, 19, 16,
		// top
		20, 21, 22,
		22, 23, 20
	};
	int data_len = 9;
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
		for (int i = 0; i < indices.size(); i += 3)
		{
			float indx = indices[i] * data_len;
			float indx2 = indices[i + 1] * data_len;
			float indx3 = indices[i + 2] * data_len;
			QVector3D tmp_1 = QVector3D(vertices[indx] - vertices[indx2],
				vertices[indx + 1] - vertices[indx2 + 1],
				vertices[indx + 2] - vertices[indx2 + 2]);
			QVector3D tmp_2 = QVector3D(vertices[indx2] - vertices[indx3],
				vertices[indx2 + 1] - vertices[indx3 + 1],
				vertices[indx2 + 2] - vertices[indx3 + 2]);
			QVector3D tmp_3 = QVector3D::crossProduct(tmp_1, tmp_2).normalized();
			vertices[indx + 6] = (tmp_3.x());
			vertices[indx + 7] = (tmp_3.y());
			vertices[indx + 8] = (tmp_3.z());
			vertices[indx2 + 6] = (tmp_3.x());
			vertices[indx2 + 7] = (tmp_3.y());
			vertices[indx2 + 8] = (tmp_3.z());
			vertices[indx3 + 6] = (tmp_3.x());
			vertices[indx3 + 7] = (tmp_3.y());
			vertices[indx3 + 8] = (tmp_3.z());
		}
	}
	void setWhiteColot()
	{
		for (int i = 0; i < vertices.size() / data_len; ++i)
		{
			vertices[i * data_len + 3] = 1;
			vertices[i * data_len + 4] = 1;
			vertices[i * data_len + 5] = 1;
		}
	}
};

#endif // CUBE_H
