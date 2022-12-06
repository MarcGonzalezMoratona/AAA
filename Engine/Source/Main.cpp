#include <stdlib.h>
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleEditor.h"
#include "Globals.h"

#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/lib/x64/SDL2.lib" )
#pragma comment( lib, "SDL/lib/x64/SDL2main.lib" )

enum main_states
{
	MAIN_CREATION,
	MAIN_INIT,
	MAIN_START,
	MAIN_UPDATE,
	MAIN_FINISH,
	MAIN_EXIT
};

Application* App = NULL;

int main(int argc, char** argv)
{
	int main_return = EXIT_FAILURE;
	main_states state = MAIN_CREATION;

	while (state != MAIN_EXIT)
	{
		switch (state)
		{
		case MAIN_CREATION:

			App = new Application();
			App->editor->AddLog("Application Creation --------------");
			state = MAIN_INIT;
			break;

		case MAIN_INIT:

			App->editor->AddLog("Application Init --------------");
			if (App->Init() == false)
			{
				App->editor->AddLog("Application Init exits with error -----");
				state = MAIN_EXIT;
			}
			else
			{
				state = MAIN_START;
				App->editor->AddLog("Application Update --------------");
			}

			break;

		case MAIN_START:

			App->editor->AddLog("Application Init --------------");
			if (App->Start() == false)
			{
				App->editor->AddLog("Application Start exits with error -----");
				state = MAIN_EXIT;
			}
			else
			{
				state = MAIN_UPDATE;
				App->editor->AddLog("Application Update --------------");
			}

			break;

		case MAIN_UPDATE:
		{
			int update_return = App->Update();

			if (update_return == UPDATE_ERROR)
			{
				App->editor->AddLog("Application Update exits with error -----");
				state = MAIN_EXIT;
			}

			if (update_return == UPDATE_STOP)
				state = MAIN_FINISH;
		}
		break;

		case MAIN_FINISH:

			App->editor->AddLog("Application CleanUp --------------");
			if (App->CleanUp() == false)
			{
				App->editor->AddLog("Application CleanUp exits with error -----");
			}
			else
				main_return = EXIT_SUCCESS;

			state = MAIN_EXIT;

			break;

		}

	}

	delete App;
	App->editor->AddLog("Bye :)\n");
	return main_return;
}
