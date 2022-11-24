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
	return true;
}

// Called every draw update
update_status ModuleTimer::Update()
{
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleTimer::CleanUp()
{
	DEBUGLOG("Destroying ModuleTexture");
	return true;
}

