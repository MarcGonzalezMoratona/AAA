#include "Application.h"
#include "ModuleEditor.h"
#include "ModuleTimer.h"
#include "PanelConsole.h"

ModuleTimer::ModuleTimer()
{
}

ModuleTimer::~ModuleTimer()
{
}

bool ModuleTimer::Init()
{
	lastTime = SDL_GetTicks();
	return true;
}

bool ModuleTimer::Start()
{
	return true;
}

update_status ModuleTimer::Update()
{
	Uint32 currentTime = SDL_GetTicks();
	deltaTime = (float)(currentTime - lastTime) / 1000.0f;
	if (deltaTime < 1.0f / maxFPS) {
		SDL_Delay(1.0f / maxFPS - deltaTime);
		deltaTime = 1.0f / maxFPS;
	}
	lastTime = currentTime;
	fps = 1.0f / deltaTime;
	return UPDATE_CONTINUE;
}

bool ModuleTimer::CleanUp()
{
	App->editor->AddLog("Destroying ModuleTimer");
	return true;
}

