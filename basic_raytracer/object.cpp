#include "object.hpp"

Sphere::Sphere(const Vec3f & newCenter, const float newRadius)
	: center{newCenter}, radius{newRadius}
{
}

bool Sphere::intersect(const Vec3f &origin, const Vec3f &dir, float &t0) const
{
	Vec3f l{center - origin};
	float project{dot(l, dir)};
	float dist2{dot(l, l) - project * project};
	if (dist2 > radius * radius)
		return false;

	float halfChord{std::sqrtf(radius * radius - dist2)};
	t0 = project - halfChord;
	float t1{project + halfChord};

	if (t0 < 0)
		t0 = t1;
	if (t0 < 0)
		return false;

	return true;
}