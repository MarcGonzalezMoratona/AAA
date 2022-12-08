#pragma once

class Panel
{
public:
	Panel(const char* name) {
	}

	~Panel() {
	}

	void ToggleVisibility() {
		visible = !visible;
	}

	virtual void Draw() {}
	
	bool IsVisible()
	{
		return visible;
	}

	const char* GetName()
	{
		return name;
	}

private:
	bool visible = true;
	char* name;
};

