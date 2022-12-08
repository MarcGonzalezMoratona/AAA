#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleEditor.h"
#include "PanelConsole.h"

ModuleWindow::ModuleWindow()
{
}

ModuleWindow::~ModuleWindow()
{
}

unsigned ModuleWindow::GetWidth() {
	int width, height;
	SDL_GetWindowSize(window, &width, &height);
	return width;
}

unsigned ModuleWindow::GetHeight() {
	int width, height;
	SDL_GetWindowSize(window, &width, &height);
	return height;
}

void ModuleWindow::GetWindowSize(int& width, int& height) {
	SDL_GetWindowSize(window, &width, &height);
}

bool ModuleWindow::Init()
{
	App->editor->AddLog("Init SDL window & surface");
	bool ret = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		DEBUGLOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		SDL_DisplayMode dm;

		if (SDL_GetDesktopDisplayMode(0, &dm) != 0)
		{
			SDL_Log("SDL_GetDesktopDisplayMode failed: %s", SDL_GetError());
			ret = false;
		}

		screen_width = dm.w/3*2;
		screen_height = dm.h/3*2;

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

