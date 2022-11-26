#include "ModuleEditor.h"

ModuleEditor::ModuleEditor()
{
}

// Destructor
ModuleEditor::~ModuleEditor()
{
}

// Called before render is available
bool ModuleEditor::Init()
{
	return true;
}

// Called every draw update
update_status ModuleEditor::Update()
{
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEditor::CleanUp()
{
	DEBUGLOG("Destroying ModuleTexture");
	return true;
}

