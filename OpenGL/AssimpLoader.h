#pragma once
#include <iostream>
#include <QVector3D>
#include <QVector2D>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"

#include <QColor>
#include <QOpenGLShaderProgram>
#include <random>


class AssimpLoader final
{
	std::string directory;
	SceneObject* obj;
public:
	void loadModel(const std::string& path)
	{
		obj = new SceneObject();
		Assimp::Importer import;
		const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
			return;
		}
		directory = path.substr(0, path.find_last_of('/'));
		for (int j = 0; j < scene->mNumMeshes; ++j) {
			for (int i = 0; i < scene->mMeshes[j]->mNumVertices; ++i)
			{
				obj->getVertices().push_back(scene->mMeshes[j]->mVertices[i][0]);
				obj->getVertices().push_back(scene->mMeshes[j]->mVertices[i][1]);
				obj->getVertices().push_back(scene->mMeshes[j]->mVertices[i][2]);
				obj->getVertices().push_back(scene->mMeshes[j]->mNormals[i][0]);
				obj->getVertices().push_back(scene->mMeshes[j]->mNormals[i][1]);
				obj->getVertices().push_back(scene->mMeshes[j]->mNormals[i][2]);
				if (scene->mMeshes[0]->mTextureCoords[0] != nullptr) {
					obj->getVertices().push_back(scene->mMeshes[j]->mTextureCoords[0][i][0]);
					obj->getVertices().push_back(scene->mMeshes[j]->mTextureCoords[0][i][1]);
				}
				else
				{
					obj->getVertices().push_back(0);
					obj->getVertices().push_back(0);
				}
				if (scene->mMeshes[j]->mTangents != nullptr) {
					obj->getVertices().push_back(scene->mMeshes[j]->mTangents[i][0]);
					obj->getVertices().push_back(scene->mMeshes[j]->mTangents[i][1]);
					obj->getVertices().push_back(scene->mMeshes[j]->mTangents[i][2]);
				}
				else
				{
					obj->getVertices().push_back(0);
					obj->getVertices().push_back(0);
					obj->getVertices().push_back(0);

				}
				if (scene->mMeshes[0]->mTangents != nullptr) {
					obj->getVertices().push_back(scene->mMeshes[j]->mBitangents[i][0]);
					obj->getVertices().push_back(scene->mMeshes[j]->mBitangents[i][1]);
					obj->getVertices().push_back(scene->mMeshes[j]->mBitangents[i][2]);
				}
				else
				{
					obj->getVertices().push_back(0);
					obj->getVertices().push_back(0);
					obj->getVertices().push_back(0);

				}
			}
			obj->setDataLen(14);
			for (int k = 0; k < scene->mMeshes[j]->mNumFaces; ++k) {
				aiFace face = scene->mMeshes[j]->mFaces[k];
				for (int i = 0; i < face.mNumIndices; ++i)
				{
					obj->getIndices().push_back(face.mIndices[i]);
				}
			}
		}
	}

	SceneObject* getObj()
	{
		return obj;
	}
};