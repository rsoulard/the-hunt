#pragma once
#include <application.h>
#include <servicecollection.h>

typedef struct ApplicationBuilder* applicationBuilder_t;

applicationBuilder_t ApplicationBuilder_New();
void ApplicationBuilder_Destroy(applicationBuilder_t this);
serviceCollection_t ApplicationBuilder_GetServiceCollection(applicationBuilder_t this);
application_t ApplicationBuilder_Build(applicationBuilder_t this);
