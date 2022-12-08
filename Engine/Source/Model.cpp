#include "assimp/cimport.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "Model.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleCamera.h"
#include "ModuleEditor.h"
#include "PanelConsole.h"
#include <list>

Model::Model()
{
}

Model::~Model()
{
}

void Model::Load(const char* file_name)
{
	const aiScene* scene = aiImportFile(file_name, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene)
	{
		LoadTextures(scene);
		LoadMeshes(scene);
	}
	else DEBUGLOG("Error loading %s: %s", file_name, aiGetErrorString());
}

void Model::LoadTextures(const aiScene* scene)
{
	aiString file;
	materials.reserve(scene->mNumMaterials);
	for (unsigned int i = 0; i < scene->mNumMaterials; ++i)
	{
		if (scene->mMaterials[i]->GetTexture(aiTextureType_DIFFUSE, 0, &file) == AI_SUCCESS)
		{
			std::string texture_path = std::string(file.data);
			const size_t lastSlashIndex = texture_path.find_last_of("\\/");
			if (std::string::npos != lastSlashIndex) texture_path.erase(0, lastSlashIndex + 1);
			DEBUGLOG(file.data);
			texture_path = "Textures/" + texture_path;
			materials.push_back(App->texture->Load(texture_path.c_str()));
		}
	}
}

void Model::Draw() {
	for (unsigned int i = 0; i < meshes.size(); i++) meshes[i]->Draw(materials);
}

void Model::LoadMeshes(const aiScene* scene)
{
	meshes = std::vector<Mesh*>(scene->mNumMeshes);
	for (unsigned int i = 0; i < scene->mNumMeshes; ++i) meshes[i] = new Mesh(scene->mMeshes[i]);
	App->editor->AddLog("Meshes loaded");

	minCoords = meshes[0]->min;
	maxCoords = meshes[0]->max;
	numTriangles = meshes[0]->num_vertices * 3;

	for (unsigned int i = 1; i < scene->mNumMeshes; ++i)
	{
		if (maxCoords.x < meshes[i]->max.x) maxCoords.x = meshes[i]->max.x;
		if (minCoords.x > meshes[i]->min.x) minCoords.x = meshes[i]->min.x;

		if (maxCoords.y < meshes[i]->max.y) maxCoords.y = meshes[i]->max.y;
		if (minCoords.y > meshes[i]->min.y) minCoords.y = meshes[i]->min.y;

		if (maxCoords.z < meshes[i]->max.z) maxCoords.z = meshes[i]->max.z;
		if (minCoords.z > meshes[i]->min.z) minCoords.z = meshes[i]->min.z;

		numTriangles += meshes[i]->num_vertices * 3;
	}
	if (maxCoords.x > maxCoords.y && maxCoords.x > maxCoords.z) App->camera->SetPos(math::vec((minCoords.x + maxCoords.x) / 2.0f, (minCoords.y + maxCoords.y) / 2.0f, 2.0f * maxCoords.x));
	else if (maxCoords.y > maxCoords.x && maxCoords.y > maxCoords.z) App->camera->SetPos(math::vec((minCoords.x + maxCoords.x) / 2.0f, (minCoords.y + maxCoords.y) / 2.0f, 2.0f * maxCoords.y));
	else App->camera->SetPos(math::vec((minCoords.x + maxCoords.x) / 2.0f, (minCoords.y + maxCoords.y) / 2.0f, 2.0f * maxCoords.z));
	App->camera->LookAt(GetCenter());
}
