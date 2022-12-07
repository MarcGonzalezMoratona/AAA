#include "Panel.h"

Panel::Panel(const char* name){

}

Panel::~Panel(){

}

void Panel::ToggleVisibility() {
	visible = !visible;
}

bool Panel::IsVisible() {
	return visible;
}

const char* Panel::GetName() {
	return name;
}