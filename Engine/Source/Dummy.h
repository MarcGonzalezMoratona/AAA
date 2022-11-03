#pragma once
#include "Module.h"
#include "Globals.h"

class ModuleDummy : public Module
{
	bool Init()
	{
		DEBUGLOG("Dummy Init!");
		return true;
	}

	bool CleanUp()
	{
		DEBUGLOG("Dummy CleanUp!");
		return true;
	}
};