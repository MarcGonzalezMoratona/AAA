#pragma once

class Panel
{
public:
	Panel(const char* name);
	virtual ~Panel();

	void ToggleVisibility();
	bool IsVisible();
	const char* GetName();

private:
	bool visible = true;
	char* name;
};

