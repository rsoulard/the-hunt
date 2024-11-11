#pragma once
#include <dictionary.h>

typedef struct ServiceProvider* serviceProvider_t;

enum ServiceType
{
	LIFECYCLE = 0,
	SINGLETON = 1
};

struct LifeCycleEntry
{
	void (*onStart)(void*);
	void (*onEnd)(void*);
};

struct ServiceEntry
{
	enum ServiceType type;
    void* (*factory)(serviceProvider_t);
    void (*cleaner)(void*);
	void* instance;

	union
	{
		struct LifeCycleEntry lifeCycle;
	};
};

serviceProvider_t ServiceProvider_New(dictionary_t serviceDictionary);
void ServiceProvider_Destroy(serviceProvider_t this);
void* ServiceProvider_ResolveService(serviceProvider_t this, const char* key);
void ServiceProvider_Start(serviceProvider_t this);
void ServiceProvider_End(serviceProvider_t this);
