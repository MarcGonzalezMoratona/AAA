#pragma once
#include "Module.h"
#include "Globals.h"

typedef unsigned __int8 Uint8;

class ModuleInput : public Module
{
public:

	ModuleInput();
	~ModuleInput();

	bool Init() override;
	update_status Update() override;
	bool CleanUp() override;

	void GetMousePosition(int& x, int& y);
	void GetMouseMotion(int& x, int& y);
	void GetOrbitMouseMotion(int& x, int& y);
	void GetWheel(int& w);

	inline bool GetOrbit()
	{
		return orbit;
	}

	const Uint8* keyboard = NULL;

private:
	int mouseX, mouseY, mouseMotionX, mouseMotionY, orbitMouseMotionX, orbitMouseMotionY, wheel;
	bool orbit;
};