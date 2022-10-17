#pragma once
#include "Module.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleScene : public Module
{
public:

	ModuleScene();
	~ModuleScene();

	bool Init();
	bool Start();
	update_status Update();
	bool CleanUp();
	SDL_Texture* GetTexture();


private:
	SDL_Texture* texture;

};