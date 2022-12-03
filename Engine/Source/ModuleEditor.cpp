#include "ModuleEditor.h"
#include "imgui.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
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
	Begin("Console");
	End();

	Begin("Configuration");
	//static char buf[128] = App->window->GetTitle();
	static int max_fps = MAX_FPS;
	static int screen_height = App->window->GetHeight();
	static int screen_width = App->window->GetWidth();
	static bool fullscreen = App->window->IsFullscreen();
	static bool resizable = App->window->IsResizable();
	static bool borderless = App->window->IsBorderless();
	static bool fullscreenDesktop = App->window->IsFullscreenDesktop();
	static float brightness = App->window->GetBrightness();

	if (CollapsingHeader("Application")) {
		if (InputText("Engine name", App->engineName, IM_ARRAYSIZE(App->engineName))) {
			App->window->SetTitle(App->engineName);
		}
		/*if (InputText("Organization", App->organization, IM_ARRAYSIZE(App->organization))) {
			App->window->SetOrganization(App->organization);
		}*/
		SliderInt("Max FPS", &max_fps, 0, 60);
		Text("Limit framerate: %i", max_fps);
		//char title[25];
		//sprintf_s(title, 25, "Framerate %.1f", fps_log[fps_log.size() - 1]);
		//ImGui::PlotHistogram("##framerate", &fps_log[0], fps_log.size(), 0, title, 0.0f, 100.0f, ImVec2(310, 100));
		//sprintf_s(title, 25, "Milliseconds %.1f", ms_log[ms_log.size() - 1]);
		//ImGui::PlotHistogram("##framerate", &ms_log[0], ms_log.size(), 0, title, 0.0f, 100.0f, ImVec2(310, 100));
		//Text("Total actual memory:", max_fps);
		//Text("Peak reported memory:", max_fps);
		//Text("Peak actual memory:", max_fps);
		//Text("Accumulated reported memory:", max_fps);
		//Text("Accumulated allocated unit count:", max_fps);
		//Text("Total allocated unit count:", max_fps);
		//Text("Peak allocated unit count:", max_fps);
	}
	if (CollapsingHeader("Window")) {
		if(SliderFloat("Brightness", &brightness, 0.0f, 1.0f)) App->window->SetBrightness(brightness);
		if (SliderInt("Width", &screen_width, 0, 3840) || SliderInt("Height", &screen_height, 0, 3840)) App->window->SetSizes(screen_width, screen_height);
		if (Checkbox("Fullscreen", &fullscreen)) App->window->SetFullscreen(fullscreen);
		if (Checkbox("Resizable", &resizable)) App->window->SetResizable(resizable);
		if (Checkbox("Borderless", &borderless)) App->window->SetBorderless(borderless);
		if (Checkbox("Full desktop", &fullscreenDesktop)) App->window->SetFullscreenDesktop(fullscreenDesktop);
	}
	if (CollapsingHeader("File System")) {
	}
	if (CollapsingHeader("Input")) {
		static int mouseX, mouseY, wheel;
		App->input->GetMouseMotion(mouseX, mouseY);
		App->input->GetWheel(wheel);
		Text("Mouse X: %i", mouseX);
		Text("Mouse Y: %i", mouseY);
		Text("Mouse Wheel: %i", wheel);
	}
	if (CollapsingHeader("Hardware")) {
		//Text("SDL Version: %i", max_fps);
		//Text("CPUs: %i", max_fps);
		//Text("System RAM: %i", max_fps);
		//Text("Caps: %i", max_fps);
		//Text("GPS: %i", max_fps);
		//Text("Brand: %i", max_fps);
		//Text("VRAM Budget: %i", max_fps);
		//Text("VRAM Usage: %i", max_fps);
		//Text("VRAM Available: %i", max_fps);
		//Text("VRAM Reserved: %i", max_fps);
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

