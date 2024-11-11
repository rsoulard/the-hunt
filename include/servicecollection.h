#pragma once
#include <serviceprovider.h>

typedef struct ServiceCollection* serviceCollection_t;

serviceCollection_t ServiceCollection_New();
void ServiceCollection_Destroy(serviceCollection_t this);
serviceProvider_t ServiceCollection_CreateProvider(serviceCollection_t this);