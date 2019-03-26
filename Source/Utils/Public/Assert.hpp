#pragma once

#ifdef SPY_DEBUG
#include <assert.h>
#define SPY_ASSERT(expression) assert(expression)
#else
#define SPY_ASSERT(expression)
#endif
