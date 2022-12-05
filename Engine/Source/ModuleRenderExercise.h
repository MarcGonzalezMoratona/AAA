#pragma once
#include "Module.h"
#include "Model.h"

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
	Model* model;

private:
	unsigned vbo = 0, tbo = 0, ebo = 0, vao = 0;
};

