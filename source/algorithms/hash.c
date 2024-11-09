#include "hash.h"

unsigned long StringHash(const char* string)
{
    unsigned long hash = 5381;
    int character;

    while (character = *string++)
        hash = ((hash << 5) + hash) + character;

    return hash;
}