#ifndef VEC_HPP
#define VEC_HPP

#include <cstring>
#include <cassert>
#include <initializer_list>

template <size_t size, typename T>
class Vec
{
private:
	T data[size];

public:
	Vec()
	{
		memset(data, 0, sizeof(data));
	}

	Vec(const std::initializer_list<T> init)
	{
		assert(init.size() == size);
		size_t i{0};
		for (const T &element : init)
		{
			data[i] = element;
			++i;
		}
	}

	T& operator[](const size_t index) { return data[index]; }
	const T& operator[](const size_t index) const { return data[index]; }
};

using Vec3f = Vec<3, float>;

#endif
