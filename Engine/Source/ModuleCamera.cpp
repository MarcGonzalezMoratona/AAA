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
	if (App->input->keyboard[SDL_SCANCODE_ESCAPE]) return UPDATE_STOP;

	if (App->input->keyboard[SDL_SCANCODE_E]) posY += 0.01f * speed;
	if (App->input->keyboard[SDL_SCANCODE_Q]) posY -= 0.01f * speed;
	if (App->input->keyboard[SDL_SCANCODE_D]) posX += 0.01f * speed;
	if (App->input->keyboard[SDL_SCANCODE_A]) posX -= 0.01f * speed;
	if (App->input->keyboard[SDL_SCANCODE_S]) posZ += 0.01f * speed;
	if (App->input->keyboard[SDL_SCANCODE_W]) posZ -= 0.01f * speed;
	if (App->input->keyboard[SDL_SCANCODE_LSHIFT]) speed = 3.0f;
	if (App->input->keyboard[SDL_SCANCODE_UP]) rotX += 0.01f * speed;
	if (App->input->keyboard[SDL_SCANCODE_DOWN]) rotX -= 0.01f * speed;
	if (App->input->keyboard[SDL_SCANCODE_RIGHT]) rotZ += 0.01f * speed;
	if (App->input->keyboard[SDL_SCANCODE_LEFT]) rotZ -= 0.01f * speed;
	else speed = 1.0f;

	return UPDATE_CONTINUE;
}

void ModuleCamera::SetDistance(float nearPlane, float farPlane) {
	frustum.SetViewPlaneDistances(nearPlane, farPlane);
}

void ModuleCamera::SetKind(FrustumProjectiveSpace projectiveSpace, FrustumHandedness handedness) {
	frustum.SetKind(projectiveSpace, handedness);
}

void ModuleCamera::SetPerspective(float height, float width) {
	frustum.SetPerspective(height, width);
}

void ModuleCamera::SetPos(math::vec pos) {
	frustum.SetPos(pos);
}

void ModuleCamera::SetFront(math::vec front) {
	frustum.SetFront(front);
}

void ModuleCamera::SetUp(math::vec up) {
	frustum.SetUp(up);
}

float4x4 ModuleCamera::ViewMatrix() {
	return frustum.ViewMatrix();
}

float4x4 ModuleCamera::ProjectionMatrix() {
	return frustum.ProjectionMatrix();
}

// Called before quitting
bool ModuleCamera::CleanUp()
{
	DEBUGLOG("Destroying ModuleCamera");

	return true;
}

