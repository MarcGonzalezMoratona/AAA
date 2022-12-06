#ifndef __ModuleEditor_H__
#define __ModuleEditor_H__

#include "Module.h"
#include "DirectXTex.h"
#include "SDL/include/SDL.h"
#include <GL/glew.h>

using namespace DirectX;

#define GRAPH_ARRAY_SIZE 100

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
	void ShowConsole(bool b);
	void ShowConfiguration(bool b);
	void AddLog(const char* log);
	bool CleanUp();

private:
	float fps_log[GRAPH_ARRAY_SIZE];
	std::vector<const char*> items;
	bool scrollToBottom = false;
	bool console = false, configuration = false, exit = false;
};

#endif // __ModuleEditor_H__