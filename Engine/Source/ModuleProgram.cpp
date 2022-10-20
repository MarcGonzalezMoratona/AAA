#include "Globals.h"
#include "Application.h"
#include "ModuleProgram.h"
#include "SDL/include/SDL.h"

ModuleProgram::ModuleProgram()
{}

// Destructor
ModuleProgram::~ModuleProgram()
{}

// Called before render is available
bool ModuleProgram::Init()
{
    //LOG("Init SDL input event system");
    bool ret = true;
    //SDL_Init(0);

    //if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
    //{
    //    LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
    //    ret = false;
    //}

    return ret;
}

// Called every draw update
update_status ModuleProgram::Update()
{
    //SDL_Event sdlEvent;

    //while (SDL_PollEvent(&sdlEvent) != 0)
    //{
    //    switch (sdlEvent.type)
    //    {
    //    case SDL_QUIT:
    //        return UPDATE_STOP;
    //    case SDL_WINDOWEVENT:
    //        if (sdlEvent.window.event == SDL_WINDOWEVENT_RESIZED || sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
    //            App->renderer->WindowResized(sdlEvent.window.data1, sdlEvent.window.data2);
    //        break;
    //    }
    //}

    //keyboard = SDL_GetKeyboardState(NULL);

    return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleProgram::CleanUp()
{
    //LOG("Quitting SDL input event subsystem");
    //SDL_QuitSubSystem(SDL_INIT_EVENTS);
    return true;
}
