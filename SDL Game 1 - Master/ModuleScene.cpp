#include "Globals.h"
#include "Application.h"
#include "ModuleScene.h"
#include "SDL/include/SDL.h"
#include "ModuleTextures.h"

ModuleScene::ModuleScene()
{}

// Destructor
ModuleScene::~ModuleScene()
{}

// Called before render is available
bool ModuleScene::Init()
{
	LOG("Init SDL Scene");
	bool ret = true;

	return ret;
}


bool ModuleScene::Start()
{
	texture = App->textures->Load("ken_stage.png");
	return true;
}

SDL_Texture* ModuleScene::GetTexture() {
	return texture;
}


// Called every draw update
update_status ModuleScene::Update()
{
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleScene::CleanUp()
{
	LOG("Destroying SDL Scene");
	return true;
}