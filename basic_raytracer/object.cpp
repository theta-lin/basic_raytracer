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

bool Sphere::intersect(const Vec3f &origin, const Vec3f &dir, float &t0, Vec3f &hit) const
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

	hit = origin + t0 * dir;
	return true;
}

Vec3f Sphere::normal(const Vec3f &point) const
{
	return (point - center).normalize();
}

Triangle::Triangle(const std::initializer_list<Vec3f> newVertices, const Material &newMaterial)
	: Object{newMaterial}
{
	assert(newVertices.size() == 3);
	size_t i{0};
	for (const Vec3f &element : newVertices)
	{
		vertices[i] = element;
		++i;
	}
}

bool Triangle::intersect(const Vec3f &origin, const Vec3f &dir, float &t0, Vec3f &hit) const
{
	Vec3f tempPoint;
	Vec3f n{normal(tempPoint)};
	float d{-dot(n, vertices[0])};

	float denom{dot(n, dir)};
	if (std::abs(denom) < epsilon)
		return false;
	t0 = -(dot(n, origin) + d) / denom;
	if (t0 < 0.f)
		return false;
	
	hit = origin + t0 * dir;

	Vec3f v0v1{vertices[1] - vertices[0]};
	Vec3f v0Hit{hit - vertices[0]};
	if (dot(n, cross(v0v1, v0Hit)) < 0)
		return false;

	Vec3f v1v2{vertices[2] - vertices[1]};
	Vec3f v1Hit{hit - vertices[1]};
	if (dot(n, cross(v1v2, v1Hit)) < 0)
		return false;

	Vec3f v2v0{vertices[0] - vertices[2]};
	Vec3f v2Hit{hit - vertices[2]};
	if (dot(n, cross(v2v0, v2Hit)) < 0)
		return false;

	return true;
}

Vec3f Triangle::normal([[maybe_unused]] const Vec3f &point) const
{
	Vec3f v0v1{vertices[1] - vertices[0]};
	Vec3f v0v2{vertices[2] - vertices[0]};
	return cross(v0v1, v0v2).normalize();
}

Light::Light(const Vec3f &newPosition, const float newIntersity)
	: position{newPosition}, intensity{newIntersity}
{
}
