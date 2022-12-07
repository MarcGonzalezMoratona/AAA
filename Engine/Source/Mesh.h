#pragma once
#include <assimp/mesh.h>
#include "GL/glew.h"
#include <vector>
#include "../Source/MathGeoLib/Math/float3.h"

class Mesh
{
public:
	Mesh(const aiMesh* mesh);
	virtual ~Mesh();

	void Draw(const std::vector<unsigned>& model_textures);
	int num_vertices, num_indices, material_index;
	float3 min, max;

private:
	void LoadVBO(const aiMesh* mesh);
	void LoadEBO(const aiMesh* mesh);
	void CreateVAO();

	unsigned vbo, ebo, vao;

};

