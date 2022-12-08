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
	~ModuleTimer();

	bool Init() override;
	bool Start() override;
	update_status Update() override;
	bool CleanUp() override;

	inline void SetMaxFPS(int fps)
	{
		maxFPS = fps;
	}

	inline int GetMaxFPS()
	{
		return maxFPS;
	}

	inline int GetFPS()
	{
		return fps;
	}

	inline float GetDeltaTime() 
	{
		return deltaTime;
	}

private:
	float deltaTime = 0.0f;
	bool running;
	Uint32 lastTime;
	float fps = 60.0f; 
	int maxFPS = 60;
};

#endif // __ModuleTimer_H__