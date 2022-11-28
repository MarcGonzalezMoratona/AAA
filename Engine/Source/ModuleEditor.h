#ifndef __ModuleEditor_H__
#define __ModuleEditor_H__

#include "Module.h"
#include "DirectXTex.h"
#include "SDL/include/SDL.h"
#include <GL/glew.h>

using namespace DirectX;

class ModuleEditor : public Module
{
public:

	ModuleEditor();
	virtual ~ModuleEditor();
	bool Init();
	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

private:
};

#endif // __ModuleEditor_H__