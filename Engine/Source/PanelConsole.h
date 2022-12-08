#pragma once
#include "Panel.h"
#include <vector>

class PanelConsole : public Panel
{
public:
    PanelConsole(const char* title);
    virtual ~PanelConsole();
    void Draw() override;

private:
    bool scrollToBottom = false;
};