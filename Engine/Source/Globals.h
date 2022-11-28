#pragma once
#include <windows.h>
#include <stdio.h>

#define DEBUGLOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

void log(const char file[], int line, const char* format, ...);

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

// Constants -----------
#define DEGTORAD 0.01745329251f
#define RADTODEG 1.0f / DEGTORAD
#define MAX_FPS 60
#define MIN_FPS 10

// Configuration -----------
#define GLSL_VERSION "#version 440"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define FULLSCREEN false
#define BORDERLESS false
#define RESIZABLE true
#define VSYNC true
#define MAX_FPS 60
#define TITLE "LEGO Engine"