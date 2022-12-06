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


// Called every draw update
update_status ModuleTimer::Update()
{
	Uint32 currentTime = SDL_GetTicks();
	delta_time = (float)(currentTime - lastTime) / 1000.0f;
	lastTime = currentTime;
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleTimer::CleanUp()
{
	App->editor->AddLog("Destroying ModuleTimer");
	return true;
}

