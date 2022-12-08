#include "Globals.h"
#include "Application.h"
#include "ModuleCamera.h"
#include "ModuleInput.h"
#include "ModuleWindow.h"
#include "ModuleEditor.h"
#include "ModuleDebugDraw.h"
#include "ModuleRender.h"
#include "ModuleTimer.h"
#include "Model.h"
#include "../Source/MathGeoLib/Math/float3x3.h"
#include "debugdraw.h"
#include "DirectXTex.h"

ModuleCamera::ModuleCamera()
{
}

ModuleCamera::~ModuleCamera()
{
}

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
	return true;
}

void ModuleCamera::Rotate(const float3x3& rotationMatrix) {
	float3 oldFront = frustum.Front().Normalized();
	float3 oldUp = frustum.Up().Normalized();
	frustum.SetFront(rotationMatrix.MulDir(oldFront));
	frustum.SetUp(rotationMatrix.MulDir(oldUp));
}

void ModuleCamera::Move(const float3& direction) {
	frustum.SetPos(frustum.Pos() + direction * (movementSpeed * App->timer->GetDeltaTime()));
}

void ModuleCamera::Zoom(const float3& direction, int wheel) {
	frustum.SetPos(frustum.Pos() + direction * (zoomSpeed * wheel * App->timer->GetDeltaTime()));
}

void ModuleCamera::drawAxis() {
	dd::axisTriad(float4x4::identity, 0.1f, 1.0f);
	dd::xzSquareGrid(-10, 10, 0.0f, 1.0f, dd::colors::Gray);
}

update_status ModuleCamera::Update()
{
	float4x4 model = float4x4::FromTRS(
		float3(0.0f, 0.0f, 0.0f),
		float4x4::RotateX(0),
		float3(1.0f, 1.0f, 1.0f));

	float4x4 view = App->camera->ViewMatrix();
	float4x4 proj = App->camera->ProjectionMatrix();

	drawAxis();
	App->debugDraw->Draw(view, proj, App->window->GetWidth(), App->window->GetHeight());

	SDL_PumpEvents();
	if (App->input->keyboard[SDL_SCANCODE_ESCAPE]) return UPDATE_STOP;

	int mouseX, mouseY;
	App->input->GetMouseMotion(mouseX, mouseY);

	// Movement
	if (App->input->keyboard[SDL_SCANCODE_E]) Move(float3::unitY);
	if (App->input->keyboard[SDL_SCANCODE_Q]) Move(-float3::unitY);
	if (App->input->keyboard[SDL_SCANCODE_D]) Move(frustum.WorldRight());
	if (App->input->keyboard[SDL_SCANCODE_A]) Move(-frustum.WorldRight());
	if (App->input->keyboard[SDL_SCANCODE_W]) Move(frustum.Front());
	if (App->input->keyboard[SDL_SCANCODE_S]) Move(-frustum.Front());
	if (App->input->keyboard[SDL_SCANCODE_F]) LookAt(App->renderer->GetModel()->GetCenter());

	if (App->input->keyboard[SDL_SCANCODE_LALT] && App->input->GetOrbit()) {
		if (mouseY < 0) Move(-float3::unitY);
		if (mouseY > 0) Move(float3::unitY);
		if (mouseX > 0) Move(-frustum.WorldRight());
		if (mouseX < 0) Move(frustum.WorldRight());
		LookAt(App->renderer->GetModel()->GetCenter());
	}

	// Rotation
	if (App->input->keyboard[SDL_SCANCODE_DOWN]) Rotate(float3x3::RotateAxisAngle(frustum.WorldRight().Normalized(), -rotationSpeed * DEGTORAD * App->timer->GetDeltaTime()));
	if (App->input->keyboard[SDL_SCANCODE_UP]) Rotate(float3x3::RotateAxisAngle(frustum.WorldRight().Normalized(), rotationSpeed * DEGTORAD * App->timer->GetDeltaTime()));
	if (App->input->keyboard[SDL_SCANCODE_LEFT]) Rotate(float3x3::RotateY(rotationSpeed * DEGTORAD * App->timer->GetDeltaTime()));
	if (App->input->keyboard[SDL_SCANCODE_RIGHT]) Rotate(float3x3::RotateY(-rotationSpeed * DEGTORAD * App->timer->GetDeltaTime()));

	if (mouseX < 0) Rotate(float3x3::RotateY(-rotationSpeed * DEGTORAD * App->timer->GetDeltaTime()));
	if (mouseX > 0) Rotate(float3x3::RotateY(rotationSpeed * DEGTORAD * App->timer->GetDeltaTime()));
	if (mouseY > 0) Rotate(float3x3::RotateAxisAngle(frustum.WorldRight().Normalized(), rotationSpeed * DEGTORAD * App->timer->GetDeltaTime()));
	if (mouseY < 0) Rotate(float3x3::RotateAxisAngle(frustum.WorldRight().Normalized(), -rotationSpeed * DEGTORAD * App->timer->GetDeltaTime()));

	// Zoom
	int wheel;
	App->input->GetWheel(wheel);
	if(wheel != 0) Zoom(frustum.Front(), wheel);

	// Speed
	if (App->input->keyboard[SDL_SCANCODE_LSHIFT]) movementSpeed = 9.0f;
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

bool ModuleCamera::CleanUp()
{
	App->editor->AddLog("Destroying ModuleCamera");
	return true;
}

void ModuleCamera::LookAt(const float3& lookAt)
{
	float3x3 direction = float3x3::LookAt(frustum.Front(), (lookAt - frustum.Pos()).Normalized(), frustum.Up(), float3::unitY);
	SetFront(direction.MulDir(frustum.Front()).Normalized());
	SetUp(direction.MulDir(frustum.Up()).Normalized());
}