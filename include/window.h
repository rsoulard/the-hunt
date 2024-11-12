#pragma once
#include <applicationlifecycle.h>
#include <framebuffer.h>

typedef struct Window* window_t;

window_t Window_New(applicationLifeCycle_t applicationLifeCycle, frameBuffer_t frameBuffer);
void Window_Destroy(window_t this);
void Window_OnStart(window_t this);
void Window_Process(window_t this);
void Window_OnEnd(window_t this);