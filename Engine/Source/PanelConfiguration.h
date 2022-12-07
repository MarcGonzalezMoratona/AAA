#pragma once
#include "Panel.h"

#define GRAPH_ARRAY_SIZE 100

class PanelConfiguration : public Panel
{
public:
    PanelConfiguration(const char* title);
    virtual ~PanelConfiguration();
    void Draw();

private:
    float fpsLog[GRAPH_ARRAY_SIZE];
};