#include "Globals.h"
#include "Application.h"
#include "ModuleCamera.h"
#include "ModuleInput.h"
#include "ModuleWindow.h"
#include "ModuleDebugDraw.h"
#include "ModuleTimer.h"
#include "../Source/MathGeoLib/Math/float3x3.h"
#include "../Source/MathGeoLib/Math/float3.h"
#include "debugdraw.h"
#include "DirectXTex.h"

using namespace DirectX;
using namespace std;
using namespace dd;

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
	SetKind(FrustumProjectiveSpace::FrustumSpaceGL, FrustumHandedness::FrustumRightHanded);
	SetDistance(0.1f, 100.0f);
	SetPerspective(2.f * atanf(tanf(math::pi / 4.0f * 0.5f) * App->window->GetWidth() / App->window->GetHeight()), math::pi / 4.0f);
	SetPos(float3(posX, posY, posZ));

	SetFront(-float3::unitZ);
	SetUp(float3::unitY);

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
	float3 oldFront = frustum.Front().Normalized();
	float3 oldUp = frustum.Up().Normalized();
	frustum.SetFront(rotationMatrix.MulDir(oldFront));
	frustum.SetUp(rotationMatrix.MulDir(oldUp));
}

void ModuleCamera::Move(const float3& direction) {
	frustum.SetPos(frustum.Pos() + direction * (movementSpeed * App->timer->delta_time));
}

void ModuleCamera::Zoom(const float3& direction, int wheel) {
	frustum.SetPos(frustum.Pos() + direction * (zoomSpeed * wheel * App->timer->delta_time));
}


// Called every draw update
update_status ModuleCamera::Update()
{
	float4x4 model = float4x4::FromTRS(
		float3(0.0f, 0.0f, 0.0f),
		float4x4::RotateX(0),
		float3(1.0f, 1.0f, 1.0f));

	float4x4 view = App->camera->ViewMatrix();
	float4x4 proj = App->camera->ProjectionMatrix();

	axisTriad(float4x4::identity, 0.1f, 1.0f);
	xzSquareGrid(-10, 10, 0.0f, 1.0f, colors::Gray);
	App->debugDraw->Draw(view, proj, App->window->GetWidth(), App->window->GetHeight());

	SDL_PumpEvents();
	if (App->input->keyboard[SDL_SCANCODE_ESCAPE]) return UPDATE_STOP;

	// movement
	if (App->input->keyboard[SDL_SCANCODE_E]) Move(float3::unitY);
	if (App->input->keyboard[SDL_SCANCODE_Q]) Move(-float3::unitY);
	if (App->input->keyboard[SDL_SCANCODE_D]) Move(frustum.WorldRight());
	if (App->input->keyboard[SDL_SCANCODE_A]) Move(-frustum.WorldRight());
	if (App->input->keyboard[SDL_SCANCODE_W]) Move(frustum.Front());
	if (App->input->keyboard[SDL_SCANCODE_S]) Move(-frustum.Front());

	// rotate
	int mouseX, mouseY;
	App->input->GetMouseMotion(mouseX, mouseY);

	if (mouseX < 0) Rotate(float3x3::RotateY(-rotationSpeed * DEGTORAD * App->timer->delta_time));
	if (mouseX > 0) Rotate(float3x3::RotateY(rotationSpeed * DEGTORAD * App->timer->delta_time));
	if (mouseY > 0) Rotate(float3x3::RotateAxisAngle(frustum.WorldRight().Normalized(), rotationSpeed * DEGTORAD * App->timer->delta_time));
	if (mouseY < 0) Rotate(float3x3::RotateAxisAngle(frustum.WorldRight().Normalized(), -rotationSpeed * DEGTORAD * App->timer->delta_time));

	// zoom
	int wheel;
	App->input->GetWheel(wheel);
	if(wheel != 0) Zoom(frustum.Front(), wheel);

	// speed
	if (App->input->keyboard[SDL_SCANCODE_LSHIFT]) movementSpeed = 8.0f;
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

