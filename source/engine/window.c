#include <assert.h>
#include <stdlib.h>
#include <windows.h>

#include "window.h"

struct Window
{
    HWND systemWindow;
	applicationLifeCycle_t applicationLifeCycle;
};

window_t Window_New(applicationLifeCycle_t applicationLifeCycle)
{
    window_t this = malloc(sizeof *this);

    assert(this);

    this->systemWindow = NULL;
	this->applicationLifeCycle = applicationLifeCycle;

    return this;
}

void Window_Destroy(window_t this)
{
    free(this);
}

static LRESULT CALLBACK WindowProcess(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
	window_t test = GetWindowLongPtrA(window, GWLP_USERDATA);

	switch (message)
	{
		case WM_CLOSE:
			DestroyWindow(window);
			break;
		case WM_DESTROY:
			assert(test);
			PostQuitMessage(0);
			ApplicationLifeCycle_Stop(test->applicationLifeCycle, 0);
			break;
		default:
			return DefWindowProc(window, message, wParam, lParam);
			break;
	}

	return 0;
}

void Window_OnStart(window_t this)
{
    HBRUSH backgroundBrush = CreateSolidBrush(RGB(0, 0, 0));
	WNDCLASSEX windowClass = { 0 };
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

    this->systemWindow = CreateWindowEx(
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

	SetWindowLongPtrA(this->systemWindow, GWLP_USERDATA, this);
}

void Window_Process(window_t this)
{
    MSG message = { 0 };
    while (PeekMessage(&message, this->systemWindow, 0, 0, PM_REMOVE))
    {
        DispatchMessage(&message);
    }

    UpdateWindow(this->systemWindow);
}

void Window_OnEnd(window_t this)
{

}