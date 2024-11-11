#pragma once
#include <stdbool.h>

typedef struct ApplicationLifeCycle* applicationLifeCycle_t;

applicationLifeCycle_t ApplicationLifeCycle_New();
void ApplicationLifeCycle_Destroy(applicationLifeCycle_t this);
void ApplicationLifeCycle_Stop(applicationLifeCycle_t this, int exitCode);
extern inline bool ApplicationLifeCycle_IsRunning(applicationLifeCycle_t this);