#pragma once
#include "Panel.h"

class PanelConfiguration : public Panel
{
public:
    PanelConfiguration(const char* title);
    ~PanelConfiguration();

    void Draw() override;

private:
    const static int GRAPH_ARRAY_SIZE = 100;
    float fpsLog[GRAPH_ARRAY_SIZE];
};