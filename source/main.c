#ifdef _MSC_VER
#	pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#include<application.h>

int main()
{
	application_t application = Application_New();
	int returnValue = Application_Run(application);
	Application_Destroy(application);

	return returnValue;
}
