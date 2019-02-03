#include "util.hpp"

float fInvSqrt(float number)
{
	if (sizeof(float) == 4)
	{
		float x2{number * 0.5f};
		uint32_t i{reinterpret_cast<uint32_t &>(number)};
		i = 0x5f3759df - (i >> 1);
		float y{reinterpret_cast<float &>(i)};
		y = y * (1.5f - (x2 * y * y));

		return y;
	}
	else
	{
		return 1 / sqrtf(number);
	}
}
