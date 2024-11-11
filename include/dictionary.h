#pragma once
#include <stdint.h>

typedef struct Dictionary* dictionary_t;

dictionary_t Dictionary_New(unsigned long (*keyHashFunction)(const void*),  size_t valueSize);
void Dictionary_Destroy(dictionary_t this);
void* Dictionary_GetByKey(dictionary_t this, const void* key);
void* Dictionary_GetByIndex(dictionary_t this, int index);
extern inline int Dictionary_GetCount(dictionary_t this);
void Dictionary_Insert(dictionary_t this, const void* key, const void* value);