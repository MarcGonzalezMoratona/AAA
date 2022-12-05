#pragma once
#include <vector>
#include "GL/glew.h"
#include <assimp/mesh.h>

class Mesh
{
public:
	Mesh(const aiMesh* mesh);
	virtual ~Mesh();

	void Draw(const std::vector<unsigned>& model_textures);

private:
	void LoadVBO(const aiMesh* mesh);
	void LoadEBO(const aiMesh* mesh);
	void CreateVAO();

	unsigned vbo, ebo, vao;
	int num_vertices, num_indices, material_index;

};

