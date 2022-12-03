#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"

ModuleWindow::ModuleWindow()
{
}

// Destructor
ModuleWindow::~ModuleWindow()
{
}

// Brightness
float ModuleWindow::GetBrightness() {
	return SDL_GetWindowBrightness(window);
}

void ModuleWindow::SetBrightness(float b) {
	SDL_SetWindowBrightness(window, b);
}

// Screen width
unsigned ModuleWindow::GetWidth() {
	int width, height;
	SDL_GetWindowSize(window, &width, &height);
	return width;
}

// Screen height
unsigned ModuleWindow::GetHeight() {
	int width, height;
	SDL_GetWindowSize(window, &width, &height);
	return height;
}

void ModuleWindow::SetSizes(int w, int h){
	SDL_SetWindowSize(window, w, h);
}

// Resizable
bool ModuleWindow::IsResizable() {
	return resizable;
}

void ModuleWindow::SetResizable(bool b) {
	resizable = b;
}

// Borderless
bool ModuleWindow::IsBorderless() {
	return borderless;
}

void ModuleWindow::SetBorderless(bool b) {
	borderless = b;
}

// Fullscreen
bool ModuleWindow::IsFullscreen() {
	return fullscreen;
}

void ModuleWindow::SetFullscreen(bool b) {
	fullscreen = b;
}

// Fullscreen desktop
bool ModuleWindow::IsFullscreenDesktop() {
	return fullscreen_desktop;
}

void ModuleWindow::SetFullscreenDesktop(bool b) {
	fullscreen_desktop = b;
}

// Title
const char* ModuleWindow::GetTitle() {
	return SDL_GetWindowTitle(window);
}

void ModuleWindow::SetTitle(const char* t) {
	SDL_SetWindowTitle(window, t);
}

//void ModuleWindow::SetOrganization(const char* t) {
//	SDL_SetWindowTitle(window, t);
//}


// Called before render is available
bool ModuleWindow::Init()
{
	DEBUGLOG("Init SDL window & surface");
	bool ret = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		DEBUGLOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		// Create window
		Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;

		if (resizable) flags |= SDL_WINDOW_RESIZABLE;
		if (fullscreen) flags |= SDL_WINDOW_FULLSCREEN;
		if (fullscreen_desktop) flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		if (borderless) flags |= SDL_WINDOW_BORDERLESS;

		window = SDL_CreateWindow(App->engineName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, flags);

		if (window == NULL)
		{
			DEBUGLOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			// Get window surface
			screen_surface = SDL_GetWindowSurface(window);
		}
	}

	return ret;
}

update_status ModuleWindow::Update() {
	SDL_SetWindowResizable(window, (SDL_bool)resizable);
	if (fullscreen_desktop) SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	else if (fullscreen) SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	else SDL_SetWindowFullscreen(window, SDL_FALSE);
	SDL_SetWindowBordered(window, (SDL_bool)!borderless);

	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModuleWindow::CleanUp()
{
	DEBUGLOG("Destroying SDL window and quitting all SDL systems");

	// Destroy window
	if (window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	// Quit SDL subsystems
	SDL_Quit();
	return true;
}

