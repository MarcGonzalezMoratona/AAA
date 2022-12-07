#include "Application.h"
#include "ModuleEditor.h"
#include "ModuleTimer.h"

ModuleTimer::ModuleTimer()
{
}

// Destructor
ModuleTimer::~ModuleTimer()
{
}

// Called before render is available
bool ModuleTimer::Init()
{
	lastTime = SDL_GetTicks();
	return true;
}

bool ModuleTimer::Start()
{
	return true;
}

int ModuleTimer::GetMaxFPS() 
{
	return maxFPS;
}

void ModuleTimer::SetMaxFPS(int fps)
{
	maxFPS = fps;
}

// Called every draw update
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

// Called before quitting
bool ModuleTimer::CleanUp()
{
	App->editor->AddLog("Destroying ModuleTimer");
	return true;
}

