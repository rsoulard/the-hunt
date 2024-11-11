#include <assert.h>
#include <dictionary.h>
#include <stdlib.h>

#include "serviceprovider.h"

struct ServiceProvider
{
    dictionary_t serviceDictionary;
};

serviceProvider_t ServiceProvider_New(dictionary_t serviceDictionary)
{
    serviceProvider_t this = malloc(sizeof *this);

    assert(this);

    this->serviceDictionary = serviceDictionary;

	int serviceDictionaryCount = Dictionary_GetCount(this->serviceDictionary);
	for (int index = 0; index < serviceDictionaryCount; index++)
	{
		struct ServiceEntry* entry = (struct ServiceEntry*)Dictionary_GetByIndex(this->serviceDictionary, index);
		entry->instance = entry->factory(this);
	}

    return this;
}

void ServiceProvider_Destroy(serviceProvider_t this)
{
	int serviceDictionaryCount = Dictionary_GetCount(this->serviceDictionary);
	for (int index = 0; index < serviceDictionaryCount; index++)
	{
		struct ServiceEntry* entry = (struct ServiceEntry*)Dictionary_GetByIndex(this->serviceDictionary, index);
		entry->cleaner(entry->instance);
	}

    Dictionary_Destroy(this->serviceDictionary);

    free(this);
}

void* ServiceProvider_ResolveService(serviceProvider_t this, const char* key)
{
	struct ServiceEntry entry = *(struct ServiceEntry*)Dictionary_GetByKey(this->serviceDictionary, key);

	return entry.instance;
}

void ServiceProvider_Start(serviceProvider_t this) // TODO: Some sort of LINQ like ability to return an enumerator over entries, provider should not be concerned with start and end.
{
	int serviceDictionaryCount = Dictionary_GetCount(this->serviceDictionary);
	for (int index = 0; index < serviceDictionaryCount; index++)
	{
		struct ServiceEntry* entry = (struct ServiceEntry*)Dictionary_GetByIndex(this->serviceDictionary, index);
		
		if (entry->type == LIFECYCLE)
		{
			entry->lifeCycle.onStart(entry->instance);
		}
	}
}

void ServiceProvider_End(serviceProvider_t this) // TODO: Some sort of LINQ like ability to return an enumerator over entries, provider should not be concerned with start and end.
{
	int serviceDictionaryCount = Dictionary_GetCount(this->serviceDictionary);
	for (int index = 0; index < serviceDictionaryCount; index++)
	{
		struct ServiceEntry* entry = (struct ServiceEntry*)Dictionary_GetByIndex(this->serviceDictionary, index);

		if (entry->type == LIFECYCLE)
		{
			entry->lifeCycle.onEnd(entry->instance);
		}
	}
}