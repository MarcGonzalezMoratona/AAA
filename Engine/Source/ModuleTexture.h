#ifndef __ModuleTexture_H__
#define __ModuleTexture_H__

#include "Module.h"
#include "SDL/include/SDL.h"

class Application;

class ModuleTexture : public Module
{
public:

	ModuleTexture();
	virtual ~ModuleTexture();
	bool Init();
	update_status Update();
	bool CleanUp();

	GLuint texture_object;

private:
};

#endif // __ModuleTexture_H__