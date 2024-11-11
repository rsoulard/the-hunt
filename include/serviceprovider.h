#pragma once
#include <dictionary.h>

typedef struct ServiceProvider* serviceProvider_t;

struct ServiceEntry
{
    void* (*factory)(serviceProvider_t);
    void (*cleaner);
    
    void* instance;
};

serviceProvider_t ServiceProvider_New(dictionary_t serviceDictionary);
void ServiceProvider_Destroy(serviceProvider_t this);
