#pragma once
#include "Module.h"
#include "Globals.h"

class ModuleRenderExercise : public Module
{
public:
	ModuleRenderExercise();
	~ModuleRenderExercise();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	unsigned CreateProgram(unsigned vtx_shader, unsigned frg_shader);

private:
	char* LoadShaderSource(const char* shader_file_name);

	unsigned vbo = 0;
	unsigned program = 0;

};

