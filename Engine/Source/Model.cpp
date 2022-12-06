#include "assimp/cimport.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "Model.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleEditor.h"

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
	else
	{
		DEBUGLOG("Error loading %s: %s", file_name, aiGetErrorString());
	}
}

void Model::LoadTextures(const aiScene* scene)
{
	aiString file;
	materials.reserve(scene->mNumMaterials);
	for (unsigned i = 0; i < scene->mNumMaterials; ++i)
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
	for (int i = 0; i < meshes.size(); i++) meshes[i]->Draw(materials);
}

void Model::LoadMeshes(const aiScene* scene)
{
	meshes = std::vector<Mesh*>(scene->mNumMeshes);
	for (unsigned i = 0; i < scene->mNumMeshes; ++i) meshes[i] = new Mesh(scene->mMeshes[i]);
	App->editor->AddLog("Meshes loaded");
}

