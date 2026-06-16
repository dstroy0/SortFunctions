// Stub Arduino.h for host/desktop testing.
// SortFunctions only includes this header transitively — none of the
// Arduino runtime APIs are actually used by the library code.
#pragma once
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef uint8_t byte;
typedef uint16_t word;

#ifndef F
#define F(str) (str)
#endif
