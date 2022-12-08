#ifndef __ModuleWindow_H__
#define __ModuleWindow_H__

#include "Module.h"
#include "SDL/include/SDL.h"

class Application;

class ModuleWindow : public Module
{
public:

	ModuleWindow();
	~ModuleWindow();

	bool Init() override;
	update_status Update() override;
	bool CleanUp() override;

	inline const char* GetTitle()
	{
		return SDL_GetWindowTitle(window);
	}

	unsigned GetWidth();
	unsigned GetHeight();

	inline float GetBrightness()
	{
		return SDL_GetWindowBrightness(window);
	}

	inline bool IsFullscreen() {
		return fullscreen;
	}

	inline bool IsResizable() 
	{
		return resizable;
	}

	inline bool IsBorderless()
	{
		return borderless;
	}

	inline bool IsFullscreenDesktop()
	{
		return fullscreen_desktop;
	}

	inline void SetFullscreen(bool b)
	{
		fullscreen = b;
	}

	void SetResizable(bool b)
	{
		resizable = b;
	}

	void SetBorderless(bool b)
	{
		borderless = b;
	}

	void SetFullscreenDesktop(bool b)
	{
		fullscreen_desktop = b;
	}

	inline void SetBrightness(float b)
	{
		SDL_SetWindowBrightness(window, b);
	}

	inline void SetSizes(int w, int h)
	{
		SDL_SetWindowSize(window, w, h);
	}

	inline void SetTitle(const char* t)
	{
		SDL_SetWindowTitle(window, t);
	}

	SDL_Window* window = NULL;
	SDL_Surface* screen_surface = NULL;

private:
	unsigned screen_width = 1280;
	unsigned screen_height = 720;
	bool fullscreen = false;
	bool resizable = true;
	bool borderless = false;
	bool fullscreen_desktop = false;
	float brightness = 1.0f;
};

#endif // __ModuleWindow_H__