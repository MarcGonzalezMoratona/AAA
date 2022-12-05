#pragma once
#include "Module.h"
#include "Globals.h"

class ModuleProgram : public Module
{
public:

	ModuleProgram();
	~ModuleProgram();

	bool Init();
	bool Start();
	update_status Update();

	bool CleanUp();
	void CreateProgram();
	unsigned GetProgram();

private:
	char* LoadShaderSource(const char* shader_file_name);
	unsigned CompileShader(unsigned type, const char* source);
	unsigned vertexShader, fragmentShader, program;

};

