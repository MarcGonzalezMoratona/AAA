#include "Globals.h"
#include "Application.h"
#include "ModuleRenderExercise.h"
#include "ModuleWindow.h"
#include "SDL.h"
#include "GL/glew.h"

ModuleRenderExercise::ModuleRenderExercise()
{

}

// Destructor
ModuleRenderExercise::~ModuleRenderExercise()
{
}

// Called before render is available
bool ModuleRenderExercise::Init()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4); // desired version
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // we want a double buffer
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24); // we want to have a depth buffer with 24 bits
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8); // we want to have a stencil buffer with 8 bits

	LOG("Creating Renderer context");

	SDL_GL_CreateContext(App->window->window);

	GLenum err = glewInit();

	LOG("Using Glew %s", glewGetString(GLEW_VERSION));
	LOG("Vendor: %s", glGetString(GL_VENDOR));
	LOG("Renderer: %s", glGetString(GL_RENDERER));
	LOG("OpenGL version supported %s", glGetString(GL_VERSION));
	LOG("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	glEnable(GL_DEPTH_TEST); // Enable depth test
	glEnable(GL_CULL_FACE); // Enable cull backward faces
	glFrontFace(GL_CCW); // Front faces will be counter clockwise

	return true;
}

update_status ModuleRenderExercise::PreUpdate()
{
	int w, h;
	SDL_GetWindowSize(App->window->window, &w, &h);
	glViewport(0, 0, w, h);

	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleRenderExercise::Update()
{

	return UPDATE_CONTINUE;
}

update_status ModuleRenderExercise::PostUpdate()
{
	SDL_GL_SwapWindow(App->window->window);
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRenderExercise::CleanUp()
{
	LOG("Destroying renderer");

	//Destroy window
	SDL_GL_DeleteContext(App->window->window);
	return true;
}

void ModuleRenderExercise::WindowResized(unsigned width, unsigned height)
{
}

