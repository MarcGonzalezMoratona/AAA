#pragma once
#include "Panel.h"
#include <vector>

class PanelConsole : public Panel
{
public:
    PanelConsole(const char* title);
    virtual ~PanelConsole();
    void Draw();

private:
    bool scrollToBottom = false;
};