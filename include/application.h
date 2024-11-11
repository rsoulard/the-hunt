#pragma once
#include <serviceprovider.h>

typedef struct Application* application_t;

application_t Application_New(serviceProvider_t serviceProvider);
void Application_Destroy(application_t this);
int Application_Run(application_t this);