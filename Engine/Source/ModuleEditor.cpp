#include "ModuleEditor.h"
#include "imgui.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "Application.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"

using namespace ImGui;

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
	CreateContext();
	ImGuiIO& io = GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	StyleColorsDark();
	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderExercise);
	ImGui_ImplOpenGL3_Init("#version 440");
	return true;
}

bool ModuleEditor::Start()
{

	return true;
}

// Called every draw update
update_status ModuleEditor::PreUpdate() 
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	NewFrame();

	return UPDATE_CONTINUE;
}

update_status ModuleEditor::Update()
{
	ShowDemoWindow();
	Begin(TITLE);
	static char buf[128] = TITLE;
	static int max_fps = MAX_FPS;
	if (CollapsingHeader("Application")) {
		//Text("Engine name");
		InputText("Engine name", buf, IM_ARRAYSIZE(buf));
		SliderInt("Max FPS", &max_fps, 10, 60);
	}
	End();
	if (BeginMainMenuBar()) {
		if (BeginMenu("File")) {
			MenuItem("New Scene");
			MenuItem("Load Scene");
			ImGui::EndMenu();
		}
		if (BeginMenu("Edit")) {
			MenuItem("Undo");
			MenuItem("Redo");
			ImGui::EndMenu();

		}
		if (BeginMenu("View")) {
			MenuItem("Dummy");
			ImGui::EndMenu();
		}
		if (BeginMenu("Help")) {
			MenuItem("Dummy");
			ImGui::EndMenu();
		}
		EndMainMenuBar();
	}
	Render();
	ImGui_ImplOpenGL3_RenderDrawData(GetDrawData());
	return UPDATE_CONTINUE;
}

update_status ModuleEditor::PostUpdate() 
{

	UpdatePlatformWindows();
	RenderPlatformWindowsDefault();
	SDL_GL_MakeCurrent(App->window->window, App->renderer->context);
	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModuleEditor::CleanUp()
{
	DEBUGLOG("Destroying ModuleEditor");
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	DestroyContext();

	SDL_Quit();
	return true;
	return true;
}

