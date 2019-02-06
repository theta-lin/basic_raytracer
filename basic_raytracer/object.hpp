#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <cmath>
#include <cassert>
#include <initializer_list>
#include "vec.hpp"

class Material
{
public:
	Vec4f albedo;
	Vec3f diffuse;
	float specularExp;
	float refractiveIdx;
	Material();
	Material(const Vec4f &newAlbedo, const Vec3f &newDiffuse, const float newSpecularExp,
		const float refractiveIdx);
};

class Object
{
public:
	Material material;

public:
	Object(const Material &newMaterial);
	virtual bool intersect(const Vec3f &origin, const Vec3f &dir, float &t0, Vec3f &hit) const = 0;
	virtual Vec3f normal(const Vec3f &point) const = 0;
};

class Sphere : public Object
{
private:
	Vec3f center;
	float radius;

public:
	Sphere(const Vec3f &newCenter, const float newRadius, const Material &newMaterial);
	bool intersect(const Vec3f &origin, const Vec3f &dir, float &t0, Vec3f &hit) const override;
	Vec3f normal(const Vec3f &point) const override;
};

class Triangle: public Object
{
private:
	Vec3f vertices[3];

public:
	Triangle (const std::initializer_list<Vec3f> newVertices, const Material &newMaterial);
	bool intersect(const Vec3f &origin, const Vec3f &dir, float &t0, Vec3f &hit) const override;
	Vec3f normal([[maybe_unused]] const Vec3f &point) const override;
};

class Light
{
public:
	Vec3f position;
	float intensity;
	Light(const Vec3f &newPosition, const float newIntersity);
};

#endif
