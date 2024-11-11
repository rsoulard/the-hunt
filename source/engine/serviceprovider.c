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

    return this;
}

void ServiceProvider_Destroy(serviceProvider_t this)
{
    Dictionary_Destroy(this->serviceDictionary);

    free(this);
}