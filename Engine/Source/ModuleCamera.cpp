#include "Globals.h"
#include "Application.h"
#include "ModuleCamera.h"
#include "ModuleInput.h"

ModuleCamera::ModuleCamera()
{
}

// Destructor
ModuleCamera::~ModuleCamera()
{
}

// Called before render is available
bool ModuleCamera::Init()
{
	return true;
}

// Called every draw update
update_status ModuleCamera::Update()
{
	SDL_PumpEvents();

	// TODO 1: Make the application properly close when ESC is pressed (do not use exit())
	if (App->input->keyboard[SDL_SCANCODE_ESCAPE]) return UPDATE_STOP;

	if (App->input->keyboard[SDL_SCANCODE_E]) posY += 0.01f * speed;
	if (App->input->keyboard[SDL_SCANCODE_Q]) posY -= 0.01f * speed;
	if (App->input->keyboard[SDL_SCANCODE_D]) posX += 0.01f * speed;
	if (App->input->keyboard[SDL_SCANCODE_A]) posX -= 0.01f * speed;
	if (App->input->keyboard[SDL_SCANCODE_S]) posZ += 0.01f * speed;
	if (App->input->keyboard[SDL_SCANCODE_W]) posZ -= 0.01f * speed;
	if (App->input->keyboard[SDL_SCANCODE_LSHIFT]) speed = 3.0f;
	else speed = 1.0f;

	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModuleCamera::CleanUp()
{
	DEBUGLOG("Destroying ModuleCamera");

	return true;
}

