#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleEditor.h"
#include "ModuleCamera.h"
#include "Model.h"
#include "SDL.h"
#include "GL/glew.h"

ModuleRender::ModuleRender()
{
}

// Destructor
ModuleRender::~ModuleRender()
{
}

void __stdcall OurOpenGLErrorFunction(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	//const char* tmp_source = "", * tmp_type = "", * tmp_severity = "";
	//switch (source) {
	//	case GL_DEBUG_SOURCE_API: tmp_source = "API"; break;
	//	case GL_DEBUG_SOURCE_WINDOW_SYSTEM: tmp_source = "Window System"; break;
	//	case GL_DEBUG_SOURCE_SHADER_COMPILER: tmp_source = "Shader Compiler"; break;
	//	case GL_DEBUG_SOURCE_THIRD_PARTY: tmp_source = "Third Party"; break;
	//	case GL_DEBUG_SOURCE_APPLICATION: tmp_source = "Application"; break;
	//	case GL_DEBUG_SOURCE_OTHER: tmp_source = "Other"; break;
	//};
	//switch (type) {
	//	case GL_DEBUG_TYPE_ERROR: tmp_type = "Error"; break;
	//	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: tmp_type = "Deprecated Behaviour"; break;
	//	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: tmp_type = "Undefined Behaviour"; break;
	//	case GL_DEBUG_TYPE_PORTABILITY: tmp_type = "Portability"; break;
	//	case GL_DEBUG_TYPE_PERFORMANCE: tmp_type = "Performance"; break;
	//	case GL_DEBUG_TYPE_MARKER: tmp_type = "Marker"; break;
	//	case GL_DEBUG_TYPE_PUSH_GROUP: tmp_type = "Push Group"; break;
	//	case GL_DEBUG_TYPE_POP_GROUP: tmp_type = "Pop Group"; break;
	//	case GL_DEBUG_TYPE_OTHER: tmp_type = "Other"; break;
	//};
	//switch (severity) {
	//	case GL_DEBUG_SEVERITY_HIGH: tmp_severity = "high"; break;
	//	case GL_DEBUG_SEVERITY_MEDIUM: tmp_severity = "medium"; break;
	//	case GL_DEBUG_SEVERITY_LOW: tmp_severity = "low"; break;
	//	case GL_DEBUG_SEVERITY_NOTIFICATION: tmp_severity = "notification"; break;
	//};
	//DEBUGLOG("<Source:%s> <Type:%s> <Severity:%s> <ID:%d> <Message:%s>\n", tmp_source, tmp_type, tmp_severity, id, message);
}

// Called before render is available
bool ModuleRender::Init()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4); // desired version
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // we want a double buffer
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24); // we want to have a depth buffer with 24 bits
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8); // we want to have a stencil buffer with 8 bits
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);

	App->editor->AddLog("Creating Renderer context");

	context = SDL_GL_CreateContext(App->window->window);

	GLenum err = glewInit();

	DEBUGLOG("Using Glew %s", glewGetString(GLEW_VERSION));
	DEBUGLOG("OpenGL version supported %s", glGetString(GL_VERSION));
	DEBUGLOG("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	glEnable(GL_DEPTH_TEST); // Enable depth test
	glEnable(GL_CULL_FACE); // Enable cull backward faces
	glFrontFace(GL_CCW); // Front faces will be counter clockwise

    #ifdef _DEBUG
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

	glDebugMessageCallback(OurOpenGLErrorFunction, nullptr);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, true);
    #endif

	return true;
}


bool ModuleRender::Start()
{
	// Create and load Bakerhouse model
	model = new Model();
	App->editor->AddLog("Loading bakerhouse...");
	model->Load("Models/Bakerhouse.fbx");
	return true;
}

update_status ModuleRender::PreUpdate()
{
	int w, h;
	SDL_GetWindowSize(App->window->window, &w, &h);
	glViewport(0, 0, w, h);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleRender::Update()
{
	model->Draw();
	return UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
	SDL_GL_SwapWindow(App->window->window);
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
	App->editor->AddLog("Destroying renderer");

	//Destroy window
	SDL_GL_DeleteContext(App->window->window);
	return true;
}

void ModuleRender::WindowResized(unsigned width, unsigned height)
{
	App->camera->SetAspectRatio(float(width), float(height));
}

