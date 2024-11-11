#include <application.h>
#include <applicationlifecycle.h>
#include <assert.h>
#include <servicecollection.h>
#include <serviceprovider.h>
#include <stdlib.h>

#include "applicationbuilder.h"

struct ApplicationBuilder
{
    serviceCollection_t serviceCollection;
};

void* ApplicationLifeCycleFactory(serviceProvider_t serviceProvider)
{
	return ApplicationLifeCycle_New();
}

void ApplicationLifeCycleCleaner(void* instance)
{
	ApplicationLifeCycle_Destroy(instance);
}

applicationBuilder_t ApplicationBuilder_New()
{
    applicationBuilder_t this = malloc(sizeof *this);

    assert(this);

    this->serviceCollection = ServiceCollection_New();

	ServiceCollection_AddSingleton(this->serviceCollection, "applicationLifeCycle", ApplicationLifeCycleFactory, ApplicationLifeCycleCleaner);

    return this;
}

void ApplicationBuilder_Destroy(applicationBuilder_t this)
{
    ServiceCollection_Destroy(this->serviceCollection);

    free(this);
}

inline serviceCollection_t ApplicationBuilder_GetServiceCollection(applicationBuilder_t this)
{
	return this->serviceCollection;
}

application_t ApplicationBuilder_Build(applicationBuilder_t this)
{
    serviceProvider_t serviceProvider = ServiceCollection_CreateProvider(this->serviceCollection);

    return Application_New(serviceProvider);
}
