#pragma once
#include "Module.h"
#include "Globals.h"
#include "ModuleEditor.h"
#include "Application.h"

class ModuleDummy : public Module
{
	bool Init()
	{
		App->editor->AddLog("Dummy Init!");
		return true;
	}

	bool CleanUp()
	{
		App->editor->AddLog("Dummy CleanUp!");
		return true;
	}
};