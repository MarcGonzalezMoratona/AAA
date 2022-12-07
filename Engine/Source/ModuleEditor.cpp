#include "ModuleEditor.h"
#include "imgui.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleCamera.h"
#include "ModuleInput.h"
#include "PanelConsole.h"
#include "PanelConfiguration.h"
#include "Application.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include <string>


ModuleEditor::ModuleEditor()
{
	panels.push_back(console = new PanelConsole("Console"));
	panels.push_back(configuration = new PanelConfiguration("Configuration"));
}

ModuleEditor::~ModuleEditor()
{
}

bool ModuleEditor::Init()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	ImGui::StyleColorsDark();
	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer);
	ImGui_ImplOpenGL3_Init("#version 440");
	return true;
}

bool ModuleEditor::Start()
{
	return true;
}

update_status ModuleEditor::PreUpdate()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	ImGui::NewFrame();

	return UPDATE_CONTINUE;
}


update_status ModuleEditor::Update()
{
	ImGui::ShowDemoWindow();

	if (console->IsVisible()) console->Draw();
	if (configuration->IsVisible()) configuration->Draw();
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			//ImGui::MenuItem("New Scene");
			//ImGui::MenuItem("Load Scene");
			if (ImGui::MenuItem("Exit")) return UPDATE_STOP;
			ImGui::EndMenu();
		}
		//if (ImGui::BeginMenu("Edit")) {
			//ImGui::MenuItem("Undo");
			//ImGui::MenuItem("Redo");
			//ImGui::EndMenu();
		//}
		static bool bConsole = console->IsVisible();
		static bool bConfiguration = configuration->IsVisible();
		if (ImGui::BeginMenu("View")) {
			if (ImGui::Checkbox("Console", &bConsole)) console->ToggleVisibility();
			if (ImGui::Checkbox("Configuration", &bConfiguration)) configuration->ToggleVisibility();
			ImGui::EndMenu();
		}
		//if (ImGui::BeginMenu("Help")) {
			//ImGui::MenuItem("Dummy");
			//ImGui::EndMenu();
		//}
		if (ImGui::BeginMenu("About")) {
			if (ImGui::MenuItem("GitHub repository")) ShellExecuteA(NULL, "open", "https://github.com/marcelinus99/AAA/tree/master/Engine", NULL, NULL, SW_SHOWNORMAL);
			if (ImGui::MenuItem("Engine Docs")) ShellExecuteA(NULL, "open", "https://github.com/marcelinus99/AAA/wiki", NULL, NULL, SW_SHOWNORMAL);
			if (ImGui::MenuItem("Latest releases")) ShellExecuteA(NULL, "open", "https://github.com/marcelinus99/AAA/releases", NULL, NULL, SW_SHOWNORMAL);
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	return UPDATE_CONTINUE;
}


update_status ModuleEditor::PostUpdate() 
{
	ImGui::UpdatePlatformWindows();
	ImGui::RenderPlatformWindowsDefault();
	SDL_GL_MakeCurrent(App->window->window, App->renderer->context);
	return UPDATE_CONTINUE;
}

bool ModuleEditor::CleanUp()
{
	AddLog("Destroying ModuleEditor");
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_Quit();
	return true;
}

void ModuleEditor::AddLog(const char* log)
{
	logs.push_back(log);
}


