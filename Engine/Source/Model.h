#pragma once
#include "Mesh.h"
#include "ModuleTexture.h"
#include "MathGeoLib/Math/float4x4.h"
#include <vector>
#include "GL/glew.h"
#include "assimp/scene.h"

class Model
{

public:
	Model();
	~Model();
	void Load(const char* file_name);
	void Draw();

	inline float3 GetCenter()
	{
		return float3((minCoords.x + maxCoords.x) / 2.0f, (minCoords.y + maxCoords.y) / 2.0f, (minCoords.z + maxCoords.z) / 2.0f);
	}

	inline int GetTriangleCount()
	{
		return numTriangles;
	}

private:
	void LoadMeshes(const aiScene* scene);
	void LoadTextures(const aiScene* scene);

	std::vector<unsigned> materials;
	std::vector<Mesh*> meshes;
	float3 minCoords, maxCoords;
	int numTriangles;
};

