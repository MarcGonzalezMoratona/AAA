#ifndef __ModuleEditor_H__
#define __ModuleEditor_H__

#include "Module.h"
#include "DirectXTex.h"
#include "SDL/include/SDL.h"
#include <GL/glew.h>
#include <list>

using namespace DirectX;

class Panel;
class PanelConsole;
class PanelConfiguration;

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
	void AddLog(const char* log);

	std::vector<const char*> logs;

private:
	std::list<Panel*> panels;
	PanelConsole* console = nullptr;
	PanelConfiguration* configuration = nullptr;
};

#endif // __ModuleEditor_H__