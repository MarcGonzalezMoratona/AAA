#include "PanelConsole.h"
#include "ModuleEditor.h"
#include "Application.h"
#include "imgui.h"

PanelConsole::PanelConsole(const char* name) : Panel(name)
{
}

PanelConsole::~PanelConsole()
{
}

void PanelConsole::Draw()
{
	ImGui::Begin("Console");
	if (ImGui::SmallButton("Clear")) App->editor->logs.clear();
	ImGui::SameLine();
	if (ImGui::SmallButton("Scroll to bottom")) scrollToBottom = true;
	for (int i = 0; i < App->editor->logs.size(); i++) ImGui::TextUnformatted(App->editor->logs[i]);
	if (scrollToBottom) {
		ImGui::SetScrollHereY();
		scrollToBottom = false;
	}
	ImGui::End();
}