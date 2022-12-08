#pragma once
#include "Panel.h"

#define GRAPH_ARRAY_SIZE 100

class PanelConfiguration : public Panel
{
public:
    PanelConfiguration(const char* title);
    ~PanelConfiguration();

    void Draw() override;

private:
    float fpsLog[GRAPH_ARRAY_SIZE];
};