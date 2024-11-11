#include<assert.h>
#include<stdlib.h>
#include<string.h>

#include"dictionary.h"

const size_t DEFAULT_CAPACITY = 16;
const unsigned int RESIZE_FACTOR = 2;

struct Dictionary
{
    size_t keySize;
    unsigned long (*keyHashFunction)(const void*);
    size_t valueSize;
    size_t count;
    size_t capacity;

    void* keyHashBuffer;
    void* valueBuffer;
};

dictionary_t Dictionary_New(unsigned long (*keyHashFunction)(const void*),  size_t valueSize)
{
    dictionary_t this = malloc(sizeof *this);

    assert(this);

    this->keyHashFunction = keyHashFunction;
    this->valueSize = valueSize;
    this->capacity = DEFAULT_CAPACITY;
    this->count = 0;

    void* keyHashBuffer = malloc(sizeof(unsigned long) * this->capacity);
    void* valueBuffer = malloc(this->valueSize * this->capacity);

    assert(keyHashBuffer);
    assert(valueBuffer);

    this->keyHashBuffer = keyHashBuffer;
    this->valueBuffer = valueBuffer;

    return this;
}

void Dictionary_Destroy(dictionary_t this)
{
    free(this->keyHashBuffer);
    free(this->valueBuffer);

    free(this);
}


static void EnsureCapacity(dictionary_t this, size_t desiredCapacity)
{
    if (desiredCapacity < this->capacity)
    {
        return;
    }

    this->capacity *= RESIZE_FACTOR;
    void* keyHashBuffer = realloc(this->keyHashBuffer, sizeof(unsigned long) * this->capacity);
    void* valueBuffer = realloc(this->valueBuffer, this->valueSize * this->capacity);

    assert(keyHashBuffer);
    assert(valueBuffer);

    this->keyHashBuffer = keyHashBuffer;
    this->valueBuffer = valueBuffer;
}

static unsigned long* GetPointerToKeyHashAtIndex(dictionary_t this, size_t index)
{
    uintptr_t keyHashLocation = (uintptr_t)this->keyHashBuffer + (sizeof(unsigned long) * index);
    return (void*)keyHashLocation;
}

static void* GetPointerToValueAtIndex(dictionary_t this, size_t index)
{
    uintptr_t valueLocation = (uintptr_t)this->valueBuffer + (this->valueSize * index);
    return (void*)valueLocation;
}

int GetIndexOfKeyHash(dictionary_t this, unsigned long hash)
{
    for(int index = 0; index < this->count; index++)
    {
        long hashAtIndex = *GetPointerToKeyHashAtIndex(this, index);

        if (hash == hashAtIndex)
        {
            return index;
        }
    }

    return -1;
}

void* Dictionary_GetByKey(dictionary_t this, const void* key)
{
    unsigned long hash = this->keyHashFunction(key);
    int keyIndex = GetIndexOfKeyHash(this, hash);

    if (keyIndex >= 0)
    {
        return GetPointerToValueAtIndex(this, keyIndex);
    }

    return NULL;
}

void* Dictionary_GetByIndex(dictionary_t this, int index)
{
	if (index >= 0 && index < this->count)
	{
		return GetPointerToValueAtIndex(this, index);
	}

	return NULL;
}

inline Dictionary_GetCount(dictionary_t this)
{
	return this->count;
}

void Dictionary_Insert(dictionary_t this, const void* key, const void* value)
{
    EnsureCapacity(this, this->count + 1);

    unsigned long hash = this->keyHashFunction(key);
    int keyIndex = GetIndexOfKeyHash(this, hash);
    if (keyIndex >= 0)
    {
        return;
    }

    long* nextKeyHashLocation = GetPointerToKeyHashAtIndex(this, this->count);
    void* nextValueLocation = GetPointerToValueAtIndex(this, this->count);

    *nextKeyHashLocation = hash;

    memcpy((void*)nextValueLocation, value, this->valueSize);
    this->count++;
}
