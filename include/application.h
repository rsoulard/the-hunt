
typedef struct Application* application_t;

application_t Application_New();

void Application_Destroy(application_t this);
int Application_Run(application_t this);
void Application_RegisterService(application_t this, const char* serviceKey, const void* service);
void* Application_ResolveService(application_t this, const char* serviceKey);