#ifdef _MSC_VER
#	pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#include <application.h>
#include <applicationbuilder.h>
#include <servicecollection.h>
#include <serviceprovider.h>
#include <framebuffer.h>

void* FrameBufferFactory(serviceProvider_t serviceProvider)
{
	return FrameBuffer_New();
}

void FrameBufferCleaner(void* instance)
{
	FrameBuffer_Destroy(instance);
}

int main()
{
	applicationBuilder_t applicationBuilder = ApplicationBuilder_New();

	serviceCollection_t serviceCollection = ApplicationBuilder_GetServiceCollection(applicationBuilder);

	ServiceCollection_AddService(serviceCollection, "frameBuffer", FrameBufferFactory, FrameBufferCleaner);

	application_t application = ApplicationBuilder_Build(applicationBuilder);
	ApplicationBuilder_Destroy(applicationBuilder);

	int returnValue = Application_Run(application);

	Application_Destroy(application);
	return returnValue;
}
