#include <assert.h>
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

static void Quit()
{
	quit = true;
	PostQuitMessage(0);
}

static LRESULT CALLBACK WindowProcess(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_CLOSE:
			DestroyWindow(window);
			break;
		case WM_DESTROY:
		case WM_QUIT:
			Quit();
			break;
		default:
			return DefWindowProc(window, message, wParam, lParam);
			break;
	}

	return 0;
}

int Application_Run(application_t this)
{
	HBRUSH backgroundBrush = CreateSolidBrush(RGB(0, 0, 0));
	WNDCLASSEX windowClass;
	HINSTANCE instance = GetModuleHandle(NULL);

	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = 0;
	windowClass.lpfnWndProc = WindowProcess;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = instance;
	windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground = backgroundBrush;
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = "theHuntWindowClass";
	windowClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&windowClass);

	HWND window = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		windowClass.lpszClassName,
		"The Hunt",
		(WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME) | WS_VISIBLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		640,
		480,
		NULL,
		NULL,
		instance,
		NULL
	);

	MSG message = { 0 };

	while (!quit)
	{
		while (PeekMessage(&message, window, 0, 0, PM_REMOVE))
		{
			DispatchMessage(&message);
		}

		UpdateWindow(window);
	}

	return message.wParam;
}