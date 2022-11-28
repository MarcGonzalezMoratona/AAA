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
	void CreateProgram();
	unsigned program=0;

private:
	char* LoadShaderSource(const char* shader_file_name);
	unsigned CompileShader(unsigned type, const char* source);
	unsigned vertexShader;
	unsigned fragmentShader;

};

