#pragma once

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleRenderExercise;
class ModuleProgram;
class ModuleDebugDraw;
class ModuleCamera;
class ModuleTexture;
class ModuleEditor;
class ModuleTimer;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	bool Start();
	update_status Update();
	bool CleanUp();

public:
	ModuleRender* renderer = nullptr;
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleRenderExercise* renderExercise = nullptr;
	ModuleProgram* program = nullptr;
	ModuleDebugDraw* debugDraw = nullptr;
	ModuleCamera* camera = nullptr;
	ModuleTexture* texture = nullptr;
	ModuleEditor* editor = nullptr;
	ModuleTimer* timer = nullptr;

	char engineName[25] = "LEGO engine";
	char organization[25] = "";

private:

	std::list<Module*> modules;

};

extern Application* App;
