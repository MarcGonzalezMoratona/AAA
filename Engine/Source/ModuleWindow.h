#ifndef __ModuleWindow_H__
#define __ModuleWindow_H__

#include "Module.h"
#include "SDL/include/SDL.h"

class Application;

class ModuleWindow : public Module
{
public:

	ModuleWindow();
	virtual ~ModuleWindow();
	bool Init();
	update_status Update();
	bool CleanUp();

	// getters
	const char* GetTitle();
	unsigned GetWidth();
	unsigned GetHeight();
	float GetBrightness();
	bool IsFullscreen();
	bool IsResizable();
	bool IsBorderless();
	bool IsFullscreenDesktop();

	// setters
	void SetFullscreen(bool b);
	void SetResizable(bool b);
	void SetBorderless(bool b);
	void SetFullscreenDesktop(bool b);
	void SetBrightness(float b);
	void SetSizes(int w, int h);
	void SetTitle(const char* t);

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