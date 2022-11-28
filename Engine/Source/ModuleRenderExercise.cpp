#include "Globals.h"
#include "Application.h"
#include "ModuleRenderExercise.h"
#include "ModuleProgram.h"
#include "ModuleDebugDraw.h"
#include "ModuleCamera.h"
#include "ModuleTexture.h"
#include "SDL.h"
#include "GL/glew.h"
#include "../Source/MathGeoLib/Geometry/Frustum.h"
#include "debugdraw.h"
#include "DirectXTex.h"

using namespace DirectX;
using namespace std;
using namespace dd;

ModuleRenderExercise::ModuleRenderExercise()
{
}

ModuleRenderExercise::~ModuleRenderExercise()
{
}

bool ModuleRenderExercise::Init()
{

	DEBUGLOG("Creating render exercise");

	float vtx_data[] = { 
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	};

	unsigned int triangles[] = {
		0, 1, 3,
		3, 2, 0
	};

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vtx_data), vtx_data, GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(triangles), triangles, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glEnable(GL_TEXTURE_2D);

	glGenTextures(1, &tbo);
	glBindTexture(GL_TEXTURE_2D, tbo);
	
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_MIRRORED_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	ScratchImage srcImg;
	ScratchImage image = App->texture->LoadTexture(L"textures/Baboon.ppm", nullptr, srcImg);
	
	GLint internalFormat, format, type;
	TexMetadata metadata = image.GetMetadata();

	App->texture->LoadMetadata(metadata, internalFormat, format, type);
	
	glTexImage2D(GL_TEXTURE_2D,0, internalFormat, metadata.width, metadata.height, 0, format, type, image.GetPixels());
	glGenerateMipmap(GL_TEXTURE_2D);

	return true;
}

update_status ModuleRenderExercise::PreUpdate()
{
	return UPDATE_CONTINUE;
}


update_status ModuleRenderExercise::Update()
{
	float4x4 model = float4x4::FromTRS(
		float3(0.0f, 0.0f, 0.0f),
		float4x4::RotateX(0),
		float3(1.0f, 1.0f, 1.0f));

	App->camera->SetKind(FrustumProjectiveSpace::FrustumSpaceGL, FrustumHandedness::FrustumRightHanded);
	App->camera->SetDistance(0.1f, 100.0f);
	App->camera->SetPerspective(2.f * atanf(tanf(math::pi / 4.0f * 0.5f) * SCREEN_WIDTH / SCREEN_HEIGHT), math::pi / 4.0f);

	App->camera->SetPos(float3(App->camera->posX, App->camera->posY, App->camera->posZ));
	App->camera->SetFront(-float3::unitZ);
	App->camera->SetUp(float3::unitY);

	float4x4 view = App->camera->ViewMatrix();
	float4x4 proj = App->camera->ProjectionMatrix();

 	axisTriad(float4x4::identity, 0.1f, 1.0f);
	xzSquareGrid(-10, 10, 0.0f, 1.0f, colors::Gray);
	App->debugDraw->Draw(view, proj, SCREEN_WIDTH, SCREEN_HEIGHT);

	glUseProgram(App->program->program);

	glUniformMatrix4fv(0, 1, GL_TRUE, &model[0][0]);
	glUniformMatrix4fv(1, 1, GL_TRUE, &view[0][0]);
	glUniformMatrix4fv(2, 1, GL_TRUE, &proj[0][0]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tbo);
	glBindVertexArray(vao);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	return UPDATE_CONTINUE;
}

update_status ModuleRenderExercise::PostUpdate()
{
	return UPDATE_CONTINUE;
}

bool ModuleRenderExercise::CleanUp()
{
	DEBUGLOG("Destroying render exercise");
	glDeleteProgram(App->program->program);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &ebo);
	glDeleteTextures(1, &tbo);
	return true;
}

