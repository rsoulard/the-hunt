#include <assert.h>
#include <window.h>
#include <stdbool.h>
#include <stdlib.h>
#include <serviceprovider.h>
#include <Windows.h>

#include "application.h"

struct Application
{
	serviceProvider_t serviceProvider;
};

application_t Application_New(serviceProvider_t serviceProvider)
{
	application_t this = malloc(sizeof  *this);

	assert(this);

	this->serviceProvider = serviceProvider;

	return this;
}

void Application_Destroy(application_t this)
{
	ServiceProvider_Destroy(this->serviceProvider);

	free(this);
}

static bool quit = false;

int Application_Run(application_t this)
{
	ServiceProvider_Start(this->serviceProvider);

	window_t window = ServiceProvider_ResolveService(this->serviceProvider, "window");

	while (!quit)
	{
		Window_Process(window);
	}

	ServiceProvider_End(this->serviceProvider);
	return 0;
}