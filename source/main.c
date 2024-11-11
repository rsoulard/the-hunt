#ifdef _MSC_VER
#	pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#include <application.h>
#include <applicationbuilder.h>
#include <servicecollection.h>
#include <serviceprovider.h>
#include <framebuffer.h>
#include <window.h>

void* FrameBufferFactory(serviceProvider_t serviceProvider)
{
	return FrameBuffer_New();
}

void FrameBufferCleaner(void* instance)
{
	FrameBuffer_Destroy(instance);
}

void WindowFactory(serviceProvider_t serviceProvider)
{
	applicationLifeCycle_t applicationLifeCycle = ServiceProvider_ResolveService(serviceProvider, "applicationLifeCycle");
	return Window_New(applicationLifeCycle);
}

void WindowCleaner(void* instance)
{
	Window_Destroy(instance);
}

int main()
{
	applicationBuilder_t applicationBuilder = ApplicationBuilder_New();

	serviceCollection_t serviceCollection = ApplicationBuilder_GetServiceCollection(applicationBuilder);

	ServiceCollection_AddLifeCycle(serviceCollection, "window", WindowFactory, WindowCleaner, Window_OnStart, Window_OnEnd);
	ServiceCollection_AddSingleton(serviceCollection, "frameBuffer", FrameBufferFactory, FrameBufferCleaner);

	application_t application = ApplicationBuilder_Build(applicationBuilder);
	ApplicationBuilder_Destroy(applicationBuilder);

	int returnValue = Application_Run(application);

	Application_Destroy(application);
	return returnValue;
}
