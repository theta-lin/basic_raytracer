#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <cmath>
#include "vec.hpp"

class Object
{
public:
	virtual bool intersect(const Vec3f &origin, const Vec3f &dir, float &t0) const = 0;
};

class Sphere : public Object
{
private:
	Vec3f center;
	float radius;

public:
	Sphere(const Vec3f &newCenter, const float newRadius);
	bool intersect(const Vec3f &origin, const Vec3f &dir, float &t0) const override;
};

#endif
