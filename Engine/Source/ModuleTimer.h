#ifndef __ModuleTimer_H__
#define __ModuleTimer_H__

#include "Module.h"
#include "DirectXTex.h"
#include "SDL/include/SDL.h"
#include <GL/glew.h>

using namespace DirectX;

class ModuleTimer : public Module
{
public:

	ModuleTimer();
	virtual ~ModuleTimer();
	bool Init();
	update_status Update();
	bool CleanUp();


private:
};

#endif // __ModuleTimer_H__