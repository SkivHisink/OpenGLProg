#pragma once
#include "SceneObject.h"
#include <QOpenGLBuffer>
#include <vector>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QVector3D>
namespace
{
	void middle_point(int i, int j, int* max_indx)
	{
		/*auto& vert = cube->vertices;
		auto ver_1_1 = vert[(i)*cube->data_len + 0];
		auto ver_1_2 = vert[(j)*cube->data_len + 0];
		auto ver_2_1 = vert[(i)*cube->data_len + 1];
		auto ver_2_2 = vert[(j)*cube->data_len + 1];
		auto ver_3_1 = vert[(i)*cube->data_len + 2];
		auto ver_3_2 = vert[(j)*cube->data_len + 2];

		vert.push_back((ver_1_1 + ver_1_2) / 2);
		vert.push_back((ver_2_1 + ver_2_2) / 2);
		vert.push_back((ver_3_1 + ver_3_2) / 2);
		vert.push_back(abs(vert[(i)*cube->data_len + 3] + vert[(j)*cube->data_len + 3]) / 2);
		vert.push_back(abs(vert[(i)*cube->data_len + 4] + vert[(j)*cube->data_len + 4]) / 2);
		vert.push_back(abs(vert[(i)*cube->data_len + 5] + vert[(j)*cube->data_len + 5]) / 2);
		vert.push_back(abs(vert[(i)*cube->data_len + 3] + vert[(j)*cube->data_len + 3]) / 2);
		vert.push_back(abs(vert[(i)*cube->data_len + 4] + vert[(j)*cube->data_len + 4]) / 2);
		vert.push_back(abs(vert[(i)*cube->data_len + 5] + vert[(j)*cube->data_len + 5]) / 2);

		++* max_indx;*/
	}
	int number_of_triangle_breaking(int num)
	{
		int numb = 0;
		for (int i = 0; i < num; ++i) {
			numb = numb + static_cast<int>(6 * pow(2, 2 * i + 1));
		}
		return numb;
	}

}
class Cube final: public SceneObject
{
public:
	Cube()
	{
		vertices = {
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
		indices = {
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
		dataLen = 8;
	}
	void splitTrianlges(int numb)
	{
		//int max_indx = 23;
	//auto& indxs = cube->indices;
	//int numb_of_crop = number_of_triangle_breaking(numb);//12 |60|252|1020|formula: prev+6*2^(iter_num+2)
	//std::vector<float> new_vert;
	//for (int i = 0; i < numb_of_crop; ++i) {
	//	middle_point(indxs[i * 3 + 0], indxs[i * 3 + 1], &max_indx);
	//	middle_point(indxs[i * 3 + 0], indxs[i * 3 + 2], &max_indx);
	//	middle_point(indxs[i * 3 + 1], indxs[i * 3 + 2], &max_indx);
	//	//
	//	for (int j = 0; j < 3; ++j)
	//	{
	//		for (int k = 0; k < 9; ++k)
	//		{
	//			cube->vertices.push_back(cube->vertices[indxs[i * 3 + j] + k]);

	//		}
	//	}
	//	max_indx += 3;
	//	cube->indices.push_back(max_indx - 2);
	//	cube->indices.push_back(max_indx - 5);
	//	cube->indices.push_back(max_indx - 4);
	//	//
	//	cube->indices.push_back(max_indx - 5);
	//	cube->indices.push_back(max_indx - 1);
	//	cube->indices.push_back(max_indx - 3);
	//	//									+1
	//	cube->indices.push_back(max_indx - 3);
	//	cube->indices.push_back(max_indx - 4);
	//	cube->indices.push_back(max_indx - 5);
	//	//									+1
	//	cube->indices.push_back(max_indx - 4);
	//	cube->indices.push_back(max_indx - 3);
	//	cube->indices.push_back(max_indx);

	//}
	//for (int i = 0; i < numb_of_crop; ++i)
	//{
	//	cube->indices.erase(cube->indices.begin());
	//	cube->indices.erase(cube->indices.begin());
	//	cube->indices.erase(cube->indices.begin());
	//}
	}
};
