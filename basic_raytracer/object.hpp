#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <cmath>
#include "vec.hpp"

class Material
{
public:
	Vec3f diffuse;
	Material();
	Material(const Vec3f &newDiffuse);
};

class Object
{
public:
	Material material;

public:
	Object(const Material &newMaterial);
	virtual bool intersect(const Vec3f &origin, const Vec3f &dir, float &t0) const = 0;
	virtual Vec3f normal(const Vec3f &point) const = 0;
};

class Sphere : public Object
{
private:
	Vec3f center;
	float radius;

public:
	Sphere(const Vec3f &newCenter, const float newRadius, const Material &newMaterial);
	bool intersect(const Vec3f &origin, const Vec3f &dir, float &t0) const override;
	Vec3f normal(const Vec3f &point) const override;
};

class Light
{
public:
	Vec3f position;
	float intensity;
	Light(const Vec3f &newPosition, const float newIntersity);
};

#endif
