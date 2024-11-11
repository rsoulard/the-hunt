#pragma once
#include <serviceprovider.h>

typedef struct ServiceCollection* serviceCollection_t;

serviceCollection_t ServiceCollection_New();
void ServiceCollection_Destroy(serviceCollection_t this);
void ServiceCollection_AddSingleton(serviceCollection_t this, const char* key, void* (*factory)(serviceProvider_t), void (*cleaner)(void*));
void ServiceCollection_AddLifeCycle(serviceCollection_t this, const char* key, void* (*factory)(serviceProvider_t), void (*cleaner)(void*), void(*onStart), void(*onEnd));
serviceProvider_t ServiceCollection_CreateProvider(serviceCollection_t this);