#include "object.hpp"

Material::Material()
	: albedo{1, 0, 0, 0}, diffuse{}, specularExp{}, refractiveIdx{}
{
}

Material::Material(const Vec4f &newAlbedo, const Vec3f &newDiffuse, const float newSpecularExp,
	const float newRefractiveIdex)
	: albedo{newAlbedo}, diffuse{newDiffuse}, specularExp{newSpecularExp},
	refractiveIdx{newRefractiveIdex}
{
}

Object::Object(const Material &newMaterial) : material{newMaterial}
{
}

Sphere::Sphere(const Vec3f &newCenter, const float newRadius, const Material &newMaterial)
	: Object{newMaterial}, center{newCenter}, radius{newRadius}
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

Vec3f Sphere::normal(const Vec3f &point) const
{
	return (point - center).normalize();
}

Light::Light(const Vec3f &newPosition, const float newIntersity)
	: position{newPosition}, intensity{newIntersity}
{
}
