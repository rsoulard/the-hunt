#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

#include "applicationlifecycle.h"

struct ApplicationLifeCycle
{
    bool stopRequested;
	int exitCode;
};

applicationLifeCycle_t ApplicationLifeCycle_New()
{
    applicationLifeCycle_t this = malloc(sizeof *this);

    assert(this);

    this->stopRequested = false;
	this->exitCode = 0;

    return this;
}

void ApplicationLifeCycle_Destroy(applicationLifeCycle_t this)
{
    free(this);
}

void ApplicationLifeCycle_Stop(applicationLifeCycle_t this, int exitCode)
{
    this->stopRequested = true;
	this->exitCode = exitCode;
}

inline bool ApplicationLifeCycle_IsRunning(applicationLifeCycle_t this)
{
	return this->stopRequested == false;
}
