#include<assert.h>
#include <stdlib.h>

#include "softwarerenderer.h"

struct SoftwareRenderer
{
    int temp;
};

softwareRenderer_t SoftwareRenderer_New(int temp)
{
    softwareRenderer_t this = malloc(sizeof *this);

    assert(this);

    this->temp = temp;

    return this;
}

void SoftwareRenderer_Destroy(softwareRenderer_t this)
{
    free(this);
}

void SoftwareRenderer_Test(softwareRenderer_t this, int new)
{
    this->temp = new;
}
