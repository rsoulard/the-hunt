#include <assert.h>
#include <dictionary.h>
#include <hash.h>
#include <serviceprovider.h>
#include <stdlib.h>

#include "servicecollection.h"

struct ServiceCollection
{
    dictionary_t serviceDictionary;
};

serviceCollection_t ServiceCollection_New()
{
    serviceCollection_t this = malloc(sizeof *this);

    assert(this);

    dictionary_t serviceDictionary = Dictionary_New(StringHash, sizeof(struct ServiceEntry));

    this->serviceDictionary = serviceDictionary;

    return this;
}

void ServiceCollection_Destroy(serviceCollection_t this)
{
    free(this);
}

void ServiceCollection_AddSingleton(serviceCollection_t this, const char* key, void* (*factory)(serviceProvider_t), void (*cleaner)(void*))
{
    struct ServiceEntry entry = { 0 };
	entry.type = SINGLETON;
    entry.factory = factory;
    entry.cleaner = cleaner;
	entry.instance = NULL;

    Dictionary_Insert(this->serviceDictionary, key, &entry); 
}

void ServiceCollection_AddLifeCycle(serviceCollection_t this, const char* key, void* (*factory)(serviceProvider_t), void (*cleaner)(void*), void (*onStart), void (*onEnd))
{
	struct ServiceEntry entry = { 0 };
	entry.type = LIFECYCLE;
	entry.factory = factory;
	entry.cleaner = cleaner;
	entry.lifeCycle.onStart = onStart;
	entry.lifeCycle.onEnd = onEnd;
	entry.instance = NULL;

	Dictionary_Insert(this->serviceDictionary, key, &entry);
}

serviceProvider_t ServiceCollection_CreateProvider(serviceCollection_t this)
{
    return ServiceProvider_New(this->serviceDictionary); // TODO: Should probably copy rather than pass...
}