#include "ModuleEditor.h"
#include "imgui.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleCamera.h"
#include "ModuleTimer.h"
#include "ModuleInput.h"
#include "Application.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include <string>


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

// Called every draw update
update_status ModuleEditor::PreUpdate()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	ImGui::NewFrame();

	return UPDATE_CONTINUE;
}

void ModuleEditor::AddLog(const char* log)
{
	items.push_back(log);
	scrollToBottom = true;
}

update_status ModuleEditor::Update()
{
	ImGui::ShowDemoWindow();

	if (console) {
		ImGui::Begin("Console");
		if (ImGui::SmallButton("Clear")) items.clear();
		ImGui::SameLine();
		if (ImGui::SmallButton("Scroll to bottom")) scrollToBottom = true;
		for (int i = 0; i < items.size(); i++) ImGui::TextUnformatted(items[i]);
		if (scrollToBottom) {
			ImGui::SetScrollHereY();
			scrollToBottom = false;
		}
		ImGui::End();
	}

	if (configuration) {
		ImGui::Begin("Configuration");
		static int max_fps = App->timer->GetMaxFPS();
		static int screen_height = App->window->GetHeight();
		static int screen_width = App->window->GetWidth();
		static bool fullscreen = App->window->IsFullscreen();
		static bool resizable = App->window->IsResizable();
		static bool borderless = App->window->IsBorderless();
		static bool fullscreenDesktop = App->window->IsFullscreenDesktop();
		static float brightness = App->window->GetBrightness();

		if (ImGui::CollapsingHeader("Application")) {
			if (ImGui::InputText("Engine name", App->engineName, IM_ARRAYSIZE(App->engineName))) App->window->SetTitle(App->engineName);
			ImGui::TextWrapped("Organization: UPC School");
			if (ImGui::SliderInt("Max FPS", &max_fps, 1, 120)) App->timer->SetMaxFPS(max_fps);
			ImGui::Text("Limit framerate: %f", App->timer->fps);
			fpsLog[GRAPH_ARRAY_SIZE - 1] = App->timer->fps;
			for (int i = 0; i < GRAPH_ARRAY_SIZE - 1; ++i) fpsLog[i] = fpsLog[i + 1];

			char fps_title[25];
			sprintf_s(fps_title, 25, "Framerate %.1f", fpsLog[GRAPH_ARRAY_SIZE - 1]);
			ImGui::PlotHistogram("", &fpsLog[0], GRAPH_ARRAY_SIZE, 0, fps_title, 0.0f, 120.0f, ImVec2(300, 100));
		}
		if (ImGui::CollapsingHeader("Window")) {
			if (ImGui::SliderFloat("Brightness", &brightness, 0.0f, 1.0f)) App->window->SetBrightness(brightness);
			if (ImGui::SliderInt("Width", &screen_width, 0, 3840) || ImGui::SliderInt("Height", &screen_height, 0, 3840)) App->window->SetSizes(screen_width, screen_height);
			if (ImGui::Checkbox("Fullscreen", &fullscreen)) App->window->SetFullscreen(fullscreen);
			if (ImGui::Checkbox("Resizable", &resizable)) App->window->SetResizable(resizable);
			if (ImGui::Checkbox("Borderless", &borderless)) App->window->SetBorderless(borderless);
			if (ImGui::Checkbox("Full desktop", &fullscreenDesktop)) App->window->SetFullscreenDesktop(fullscreenDesktop);
		}
		if (ImGui::CollapsingHeader("Camera")) {
			static float cameraX = App->camera->GetPos().x;
			static float cameraY = App->camera->GetPos().y;
			static float cameraZ = App->camera->GetPos().z;
			ImGui::TextWrapped("Camera position");
			if (ImGui::InputFloat("X", &cameraX, 0.01f, 1.0f, "%.3f")) App->camera->SetPos(float3(cameraX, cameraY, cameraZ));
			if (ImGui::InputFloat("Y", &cameraY, 0.01f, 1.0f, "%.3f")) App->camera->SetPos(float3(cameraX, cameraY, cameraZ));
			if (ImGui::InputFloat("Z", &cameraZ, 0.01f, 1.0f, "%.3f")) App->camera->SetPos(float3(cameraX, cameraY, cameraZ));
			ImGui::TextWrapped("Camera rotation");
			//if (ImGui::InputFloat("X", &cameraX, 0.01f, 1.0f, "%.3f")) App->camera->SetPos(float3(cameraX, cameraY, cameraZ));
			//if (ImGui::InputFloat("Y", &cameraY, 0.01f, 1.0f, "%.3f")) App->camera->SetPos(float3(cameraX, cameraY, cameraZ));
			//if (ImGui::InputFloat("Z", &cameraZ, 0.01f, 1.0f, "%.3f")) App->camera->SetPos(float3(cameraX, cameraY, cameraZ));
		}
		if (ImGui::CollapsingHeader("Model")) {
			static float modelX = App->camera->GetPos().x;
			static float modelY = App->camera->GetPos().y;
			static float modelZ = App->camera->GetPos().z;
			//ImGui::TextWrapped("Model position");
			//if (ImGui::InputFloat("X", &modelX, 0.01f, 1.0f, "%.3f")) App->camera->SetPos(float3(modelX, modelY, modelZ));
			//if (ImGui::InputFloat("Y", &modelY, 0.01f, 1.0f, "%.3f")) App->camera->SetPos(float3(modelX, modelY, modelZ));
			//if (ImGui::InputFloat("Z", &modelZ, 0.01f, 1.0f, "%.3f")) App->camera->SetPos(float3(modelX, modelY, modelZ));
			//ImGui::TextWrapped("Model rotation");
			//if (ImGui::InputFloat("X", &modelX, 0.01f, 1.0f, "%.3f")) App->camera->SetPos(float3(modelX, modelY, modelZ));
			//if (ImGui::InputFloat("Y", &modelY, 0.01f, 1.0f, "%.3f")) App->camera->SetPos(float3(modelX, modelY, modelZ));
			//if (ImGui::InputFloat("Z", &modelZ, 0.01f, 1.0f, "%.3f")) App->camera->SetPos(float3(modelX, modelY, modelZ));
			//ImGui::TextWrapped("Model scale");
			//if (ImGui::InputFloat("X", &modelX, 0.01f, 1.0f, "%.3f")) App->camera->SetPos(float3(modelX, modelY, modelZ));
			//if (ImGui::InputFloat("Y", &modelY, 0.01f, 1.0f, "%.3f")) App->camera->SetPos(float3(modelX, modelY, modelZ));
			//if (ImGui::InputFloat("Z", &modelZ, 0.01f, 1.0f, "%.3f")) App->camera->SetPos(float3(modelX, modelY, modelZ));
			ImGui::Text("Triangle count: %i", 0);
			ImGui::Text("Texture size: %i %i", 0, 0);
		}

		if (ImGui::CollapsingHeader("Input")) {
			static int mouseX, mouseY, mouseMotionX, mouseMotionY, wheel;
			App->input->GetMousePosition(mouseX, mouseY);
			App->input->GetMouseMotion(mouseMotionX, mouseMotionY);
			App->input->GetWheel(wheel);
			ImGui::Text("Mouse X: %i", mouseX);
			ImGui::Text("Mouse Y: %i", mouseY);
			ImGui::Text("Mouse motion X: %i", mouseMotionX);
			ImGui::Text("Mouse motion Y: %i", mouseMotionY);
			ImGui::Text("Mouse Wheel: %i", wheel);
		}

		if (ImGui::CollapsingHeader("Hardware")) {
			float RAM = (float)SDL_GetSystemRAM() / 1024.f;
			GLint totalMemory = 0, reservedMemory = 0, usedMemory = 0, availableMemory = 0;
			glGetIntegerv(GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX, &totalMemory);
			glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &availableMemory);
			glGetIntegerv(GL_GPU_MEMORY_INFO_DEDICATED_VIDMEM_NVX, &reservedMemory);
			usedMemory = totalMemory - availableMemory;

			SDL_version currentSDLVersion;
			SDL_VERSION(&currentSDLVersion)
				ImGui::Text("SDL Version: %d.%d.%d", currentSDLVersion.major, currentSDLVersion.minor, currentSDLVersion.patch);
			ImGui::Separator();
			ImGui::Text("CPUs: %i (Cache: %i kb)", SDL_GetCPUCount(), SDL_GetCPUCacheLineSize());
			ImGui::Text("System RAM: %.1f %s", RAM, "Gb");
			ImGui::Text("Caps:");
			ImGui::SameLine();
			if (SDL_HasAVX()) ImGui::Text("%s", "AVX");
			ImGui::SameLine();
			if (SDL_HasRDTSC()) ImGui::Text("%s", "RDTSC");
			ImGui::SameLine();
			if (SDL_HasMMX()) ImGui::Text("%s", "MMX");
			ImGui::SameLine();
			if (SDL_HasSSE()) ImGui::Text("%s", "SSE");
			ImGui::SameLine();
			if (SDL_HasSSE2()) ImGui::Text("%s", "SSE2");
			ImGui::SameLine();
			if (SDL_HasSSE3()) ImGui::Text("%s", "SSE3");
			ImGui::SameLine();
			if (SDL_HasSSE41()) ImGui::Text("%s", "SSE41");
			ImGui::SameLine();
			if (SDL_HasSSE42()) ImGui::Text("%s", "SSE42");
			ImGui::Separator();
			ImGui::Text("GPU: %s", glGetString(GL_RENDERER));
			ImGui::Text("Brand: %s", glGetString(GL_VENDOR));
			ImGui::Text("VRAM Budget: %.1f %s", (float)totalMemory / 1024.f, "Mb");
			ImGui::Text("VRAM Usage: %.1f %s", (float)usedMemory / 1024.f, "Mb");
			ImGui::Text("VRAM Available: %.1f %s", (float)availableMemory / 1024.f, "Mb");
			ImGui::Text("VRAM Reserved: %.1f %s", (float)reservedMemory / 1024.f, "Mb");
		}
		ImGui::End();
	}
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
		if (ImGui::BeginMenu("View")) {
			if (ImGui::Checkbox("Console", &console)) ShowConsole(console);
			if (ImGui::Checkbox("Configuration", &configuration)) ShowConfiguration(configuration);
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


void ModuleEditor::ShowConfiguration(bool b) {
	configuration = b;
}

void ModuleEditor::ShowConsole(bool b) {
	console = b;
}

update_status ModuleEditor::PostUpdate() 
{
	ImGui::UpdatePlatformWindows();
	ImGui::RenderPlatformWindowsDefault();
	SDL_GL_MakeCurrent(App->window->window, App->renderer->context);
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEditor::CleanUp()
{
	AddLog("Destroying ModuleEditor");
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_Quit();
	return true;
}

