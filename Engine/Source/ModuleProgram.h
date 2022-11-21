#pragma once
#include "Module.h"
#include "Globals.h"

class ModuleProgram : public Module
{
public:

	ModuleProgram();
	~ModuleProgram();

	bool Init();
	update_status Update();

	bool CleanUp();
	unsigned CompileShader(unsigned type, const char* source);
	unsigned CreateProgram(unsigned vtx_shader, unsigned frg_shader);
	char* LoadShaderSource(const char* shader_file_name);

	unsigned vertexShader;
	unsigned fragmentShader;

private:

};

