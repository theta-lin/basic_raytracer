#ifndef UTIL_HPP
#define UTIL_HPP

#include <cstdint>
#include <cmath>

// same fast inverse square root algorithm used in Quake engine
// has a fallback if float size is not 4 bytes
float fInvSqrt(float number);

#endif
