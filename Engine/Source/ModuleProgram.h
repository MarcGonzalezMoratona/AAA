#pragma once
#include "Module.h"
#include "Globals.h"

class ModuleProgram : public Module
{
public:

	ModuleProgram();
	~ModuleProgram();

	bool Init() override;
	bool Start() override;
	update_status Update() override;
	bool CleanUp() override;

	void CreateProgram();

	inline unsigned GetProgram()
	{
		return program;
	}

private:
	char* LoadShaderSource(const char* shader_file_name);
	unsigned CompileShader(unsigned type, const char* source);
	unsigned vertexShader, fragmentShader, program;

};

