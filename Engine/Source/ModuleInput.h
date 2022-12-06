#pragma once
#include "Module.h"
#include "Globals.h"

typedef unsigned __int8 Uint8;

class ModuleInput : public Module
{
public:

	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status Update();
	bool CleanUp();
	void GetMousePosition(int& x, int& y);
	void GetMouseMotion(int& x, int& y);
	void GetWheel(int& w);

	const Uint8* keyboard = NULL;

private:
	int mouseX, mouseY, mouseMotionX, mouseMotionY, wheel;
};