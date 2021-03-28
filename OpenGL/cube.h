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
		//positions
		// front
		-1.0, -1.0,  1.0, 0.5f, 0.5f, 0.5f, 0.0f, 0.0f, //0
		 1.0, -1.0,  1.0, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, //1
		 1.0,  1.0,  1.0, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, //2
		-1.0,  1.0,  1.0, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, //3
		// right											  
		 1.0, -1.0,  1.0, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, //4  - 1
		 1.0, -1.0, -1.0, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, //5  - 5
		 1.0,  1.0, -1.0, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, //6  - 6
		 1.0,  1.0,  1.0, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, //7  - 2
		// back												  	   - 
		-1.0,  1.0, -1.0, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, //8  - 7
		 1.0,  1.0, -1.0, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, //9  - 6
		 1.0, -1.0, -1.0, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, //10 - 5
		-1.0, -1.0, -1.0, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, //11 - 4
		// left												  	   - 
		-1.0, -1.0, -1.0, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, //12 - 4
		-1.0, -1.0,  1.0, 0.5f, 0.5f, 0.5f, 1.0f, 0.0f, //13 - 0
		-1.0,  1.0,  1.0, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, //14 - 3
		-1.0,  1.0, -1.0, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, //15 - 7
		// bottom											  	   - 
		-1.0, -1.0, -1.0, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, //16 - 4
		 1.0, -1.0, -1.0, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, //17 - 5
		 1.0, -1.0,  1.0, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, //18 - 1
		-1.0, -1.0,  1.0, 0.5f, 0.5f, 0.5f, 0.0f, 1.0f, //19 - 0
		// top												  	   - 
		-1.0,  1.0,  1.0, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, //20 - 3
		 1.0,  1.0,  1.0, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, //21 - 2
		 1.0,  1.0, -1.0, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, //22 - 6
		-1.0,  1.0, -1.0, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, //23 - 7
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
	int data_len = 8;
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
};

#endif // CUBE_H
