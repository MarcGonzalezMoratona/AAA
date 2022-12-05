#include <stdlib.h>
#include "Application.h"
#include "ModuleRender.h"
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

			DEBUGLOG("Application Creation --------------");
			App = new Application();
			state = MAIN_INIT;
			break;

		case MAIN_INIT:

			DEBUGLOG("Application Init --------------");
			if (App->Init() == false)
			{
				DEBUGLOG("Application Init exits with error -----");
				state = MAIN_EXIT;
			}
			else
			{
				state = MAIN_START;
				DEBUGLOG("Application Update --------------");
			}

			break;

		case MAIN_START:

			DEBUGLOG("Application Init --------------");
			if (App->Start() == false)
			{
				DEBUGLOG("Application Start exits with error -----");
				state = MAIN_EXIT;
			}
			else
			{
				state = MAIN_UPDATE;
				DEBUGLOG("Application Update --------------");
			}

			break;

		case MAIN_UPDATE:
		{
			int update_return = App->Update();

			if (update_return == UPDATE_ERROR)
			{
				DEBUGLOG("Application Update exits with error -----");
				state = MAIN_EXIT;
			}

			if (update_return == UPDATE_STOP)
				state = MAIN_FINISH;
		}
		break;

		case MAIN_FINISH:

			DEBUGLOG("Application CleanUp --------------");
			if (App->CleanUp() == false)
			{
				DEBUGLOG("Application CleanUp exits with error -----");
			}
			else
				main_return = EXIT_SUCCESS;

			state = MAIN_EXIT;

			break;

		}

	}

	delete App;
	DEBUGLOG("Bye :)\n");
	return main_return;
}
