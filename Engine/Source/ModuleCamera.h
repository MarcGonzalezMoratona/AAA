#ifndef __ModuleCamera_H__
#define __ModuleCamera_H__

#include "Module.h"
#include "SDL/include/SDL.h"

class Application;

class ModuleCamera : public Module
{
public:

	ModuleCamera();
	virtual ~ModuleCamera();
	bool Init();
	update_status Update();
	bool CleanUp();
	float posX = 0.0f, posY = 1.0f, posZ = 8.0f;
	float speed = 5.0f;

private:
};

#endif // __ModuleCamera_H__