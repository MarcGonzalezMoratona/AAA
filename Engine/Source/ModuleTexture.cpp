#include "Globals.h"
#include "Application.h"
#include "ModuleTexture.h"

ModuleTexture::ModuleTexture()
{
}

// Destructor
ModuleTexture::~ModuleTexture()
{
}

// Called before render is available
bool ModuleTexture::Init()
{
	return true;
}

// Called every draw update
update_status ModuleTexture::Update()
{

	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModuleTexture::CleanUp()
{
	DEBUGLOG("Destroying ModuleTexture");

	return true;
}

