#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <limits>
#include <memory>
#include "vec.hpp"
#include "object.hpp"

bool sceneIntersect(const Vec3f &origin, const Vec3f &dir,
	const std::vector<std::unique_ptr<Object> > &objects,
	Material &material, Vec3f &hit, Vec3f &normal)
{
	const float maxDist{2048.f};
	float dist{std::numeric_limits<float>::max()};
	
	for (const auto &object : objects)
	{
		float newDist;
		if (object->intersect(origin, dir, newDist) && newDist < dist)
		{
			dist = newDist;
			material = object->material;
			hit = origin + dir * dist;
			normal = object->normal(hit);
		}
	}
	
	return dist < maxDist;
}

Vec3f castRay(const Vec3f &origin, const Vec3f &dir,
	const std::vector<std::unique_ptr<Object> > &objects,
	const std::vector<std::unique_ptr<Light> > &lights)
{
	const float epsilon{1e-3f};

	Material material;
	Vec3f hit;
	Vec3f normal;

	if (sceneIntersect(origin, dir, objects, material, hit, normal))
	{
		float diffuseIntensity{0.f}, specularIntensity{0.f};
		for (const auto &light : lights)
		{
			Vec3f lightDir{(light->position - hit).normalize()};
			float lightDist{(light->position - hit).norm()};

			Vec3f shadowOrigin{dot(normal, lightDir) < 0 ? hit - normal * epsilon : hit + normal * epsilon};
			Vec3f shadowHit, shadowNormal;
			Material tempMaterial;

			if (!  (sceneIntersect(shadowOrigin, lightDir, objects, tempMaterial, shadowHit, shadowNormal)
				&& (shadowHit - shadowOrigin).norm() < lightDist))
			{
				diffuseIntensity += light->intensity * std::max(0.f, dot(normal, lightDir));
				specularIntensity += std::powf(std::max(0.f, dot(reflect(lightDir, normal), dir)),
					                 material.specularExp) * light->intensity;
			}
		}

		return material.diffuse * diffuseIntensity * material.albedo[0]
			+ Vec3f{1.f, 1.f, 1.f} * specularIntensity * material.albedo[1];
	}
	else
	{
		return {0.2f, 0.2f, 0.2f};
	}
}

void render(const std::vector<std::unique_ptr<Object> > &objects,
	const std::vector<std::unique_ptr<Light> > &lights)
{
	const size_t width{1024};
	const size_t height{768};
	const std::string filename{"out.ppm"};
	const float fov{1.7f};
	
	std::vector<Vec3f> buffer(width * height);
	for (size_t i{0}; i < height; ++i)
	{
		for (size_t j{0}; j < width; ++j)
		{
			// set the camera at the origin
			// screen at z = 1
			float x{(2.f * (j + 0.5f) / static_cast<float>(width) - 1.f) * tan(fov * 0.5f)};
			float y{(2.f * (i + 0.5f) / static_cast<float>(height) - 1.f) * tan(fov * 0.5f)
				    * height / static_cast<float>(width)};
			Vec3f dir{x, y, 1};
			buffer[i * width + j] = castRay({0, 0, 0}, dir.normalize(), objects, lights);
		}
	}

	std::ofstream file{filename};
	file << "P3 " << width << " " << height << " 255\n";
	for (size_t i{0}; i < buffer.size(); ++i)
	{
		for (size_t j{0}; j < 3; ++j)
		{
			file << static_cast<int>(255.f * std::max(0.f, std::min(1.f, buffer[i][j]))) << ' ';
		}
	}
}

int main()
{
	const Material orange{{0.9f, 0.1f}, {0.4f, 0.25f, 0.f}, 10.f};
	const Material lapis{{0.4f, 0.5f}, {0.f, 0.15f, 0.4f}, 50.f};
	std::vector<std::unique_ptr<Object> > objects;
	objects.push_back(std::make_unique<Sphere>(Vec3f{0.f, 0.f, 32.f}, 10.f, orange));
	objects.push_back(std::make_unique<Sphere>(Vec3f{-3.f, 5.f, 20.f}, 5.f, lapis));
	objects.push_back(std::make_unique<Sphere>(Vec3f{-15.f, -15.f, 30.f}, 7.f, orange));
	objects.push_back(std::make_unique<Sphere>(Vec3f{10.f, 6.f, 23.f}, 4.f, lapis));

	std::vector<std::unique_ptr<Light> > lights;
	lights.push_back(std::make_unique<Light>(Vec3f{15.f, 5.f, -20.f}, 1.f));
	lights.push_back(std::make_unique<Light>(Vec3f{-3.f, 5.f, 10.f}, 2.5f));

	render(objects, lights);
	return 0;
}
