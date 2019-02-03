#ifndef VEC_HPP
#define VEC_HPP

#include <cstring>
#include <cassert>
#include <initializer_list>
#include "util.hpp"

template<size_t size, typename T>
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
	
	void operator+=(const Vec &v)
	{
		for (size_t i{0}; i < size; ++i)
		{
			data[i] += v.data[i];
		}
	}

	void operator-=(const Vec &v)
	{
		for (size_t i{0}; i < size; ++i)
		{
			data[i] -= v.data[i];
		}
	}

	void operator*=(const T &scalar)
	{
		for (size_t i{0}; i < size; ++i)
		{
			data[i] *= scalar;
		}
	}
};

template<size_t size, typename T>
Vec<size, T> operator+(const Vec<size, T> &v0, const Vec<size, T> &v1)
{
	Vec<size, T> temp{v0};
	temp += v1;
	return temp;
}

template<size_t size, typename T>
Vec<size, T> operator-(const Vec<size, T> &v0, const Vec<size, T> &v1)
{
	Vec<size, T> temp{v0};
	temp += v1;
	return temp;
}

template<size_t size, typename T>
Vec<size, T> operator*(const Vec<size, T> &v, const T &scalar)
{
	Vec<size, T> temp{v};
	temp *= scalar;
	return temp;
}

template<size_t size, typename T>
Vec<size, T> operator*(const T &scalar, const Vec<size, T> &v)
{
	return v * scalar;
}

template<size_t size, typename T>
T dot(const Vec<size, T> &v0, const Vec<size, T> &v1)
{
	T product{};
	for (size_t i{0}; i < size; ++i)
		product += v0[i] * v1[i];
	return product;
}

template<typename T>
Vec<3, T> cross(const Vec<3, T> &v0, const Vec<3, T> &v1)
{
	return {v0[1] * v1[2] - v0[2] * v1[1],
			v0[2] * v1[0] - v0[0] * v1[2],
			v0[0] * v1[1] - v0[1] * v0[0]};
}

template<size_t size>
Vec<size, float> normalize(const Vec<size, float> &v)
{
	return v * fInvSqrt(dot(v, v));
}

using Vec3f = Vec<3, float>;

#endif
