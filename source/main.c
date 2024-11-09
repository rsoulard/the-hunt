#ifdef _MSC_VER
#	pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#include <application.h>
#include <softwarerenderer.h>

int main()
{
	application_t application = Application_New();

	softwareRenderer_t softwareRenderer = SoftwareRenderer_New(1);
	Application_RegisterService(application, "softwareRenderer", &softwareRenderer);

	softwareRenderer_t test = *(softwareRenderer_t*)Application_ResolveService(application, "softwareRenderer");
	SoftwareRenderer_Test(test, 20);

	int returnValue = Application_Run(application);
	SoftwareRenderer_Destroy(softwareRenderer);
	Application_Destroy(application);
	return returnValue;
}
