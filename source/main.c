#ifdef _MSC_VER
#	pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#include <applicationBuilder.h>
#include <framebuffer.h>

int main()
{
	applicationBuilder_t applicationBuilder = ApplicationBuilder_New();

	application_t application = ApplicationBuilder_Build(applicationBuilder);
	ApplicationBuilder_Destroy(applicationBuilder);

	int returnValue = Application_Run(application);

	Application_Destroy(application);
	return returnValue;
}
