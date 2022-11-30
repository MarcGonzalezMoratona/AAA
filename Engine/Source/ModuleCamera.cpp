#include "Globals.h"
#include "Application.h"
#include "ModuleCamera.h"
#include "ModuleInput.h"
#include "ModuleTimer.h"
#include "../Source/MathGeoLib/Math/float3x3.h"
#include "../Source/MathGeoLib/Math/float3.h"

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

bool ModuleCamera::Start()
{
	//SetKind(FrustumProjectiveSpace::FrustumSpaceGL, FrustumHandedness::FrustumRightHanded);
	//SetDistance(0.1f, 100.0f);
	//SetPerspective(2.f * atanf(tanf(math::pi / 4.0f * 0.5f) * SCREEN_WIDTH / SCREEN_HEIGHT), math::pi / 4.0f);

	//SetPos(float3(posX, posY, posZ));
	SetFront(-float3::unitZ);
	//SetUp(float3::unitY);
	return true;
}

void ModuleCamera::Rotate(const float3x3& rotationMatrix) {
	vec oldFront = frustum.Front().Normalized();
	vec oldUp = frustum.Up().Normalized();
	frustum.SetFront(rotationMatrix.MulDir(oldFront));
	frustum.SetUp(rotationMatrix.MulDir(oldUp));
}

// Called every draw update
update_status ModuleCamera::Update()
{
	SDL_PumpEvents();
	if (App->input->keyboard[SDL_SCANCODE_ESCAPE]) return UPDATE_STOP;

	if (App->input->keyboard[SDL_SCANCODE_E]) posY += movementSpeed * App->timer->delta_time;
	if (App->input->keyboard[SDL_SCANCODE_Q]) posY -= movementSpeed * App->timer->delta_time;
	if (App->input->keyboard[SDL_SCANCODE_D]) posX += movementSpeed * App->timer->delta_time;
	if (App->input->keyboard[SDL_SCANCODE_A]) posX -= movementSpeed * App->timer->delta_time;
	if (App->input->keyboard[SDL_SCANCODE_S]) posZ += movementSpeed * App->timer->delta_time;
	if (App->input->keyboard[SDL_SCANCODE_W]) posZ -= movementSpeed * App->timer->delta_time;
	if (App->input->keyboard[SDL_SCANCODE_LSHIFT]) movementSpeed = 8.0f;
	if (App->input->keyboard[SDL_SCANCODE_RIGHT]) Rotate(float3x3::RotateY(-rotationSpeed * DEGTORAD));
	if (App->input->keyboard[SDL_SCANCODE_LEFT]) Rotate(float3x3::RotateY(rotationSpeed * DEGTORAD));
	if (App->input->keyboard[SDL_SCANCODE_UP]) Rotate(float3x3::RotateAxisAngle(frustum.WorldRight().Normalized(),rotationSpeed * DEGTORAD));
	if (App->input->keyboard[SDL_SCANCODE_DOWN]) Rotate(float3x3::RotateAxisAngle(frustum.WorldRight().Normalized(),-rotationSpeed * DEGTORAD));
	else movementSpeed = 3.0f;

	return UPDATE_CONTINUE;
}

void ModuleCamera::SetAspectRatio(float w, float h) {
	frustum.SetHorizontalFovAndAspectRatio(frustum.HorizontalFov(), w / h);
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

