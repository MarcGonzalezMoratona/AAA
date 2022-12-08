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
	bool Init() override;
	bool Start() override;
	update_status PreUpdate() override;
	update_status Update() override;
	update_status PostUpdate() override;
	bool CleanUp() override;

	inline void AddLog(const char* log) {
		logs.push_back(log);
	}

	std::vector<const char*> logs;

private:
	std::list<Panel*> panels;
	PanelConsole* console = nullptr;
	PanelConfiguration* configuration = nullptr;
	bool exit = false;
	void ShowMenu();

};

#endif // __ModuleEditor_H__