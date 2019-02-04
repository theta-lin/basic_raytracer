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

Vec3f sceneIntersect(const Vec3f &origin, const Vec3f &dir,
	const std::vector<std::unique_ptr<Object> > &objects)
{
	const float maxDist{2048.f};
	float dist{std::numeric_limits<float>::max()};
	Material material{};
	
	for (const std::unique_ptr<Object> &object : objects)
	{
		float newDist;
		if (object->intersect(origin, dir, newDist) && newDist < dist)
		{
			dist = newDist;
			material = object->material;
		}
	}

	if (dist > maxDist)
		return {0.2f, 0.2f, 0.2f};
	else
		return material.diffuse;
}

void render(const std::vector<std::unique_ptr<Object> > &objects)
{
	const size_t width{1024};
	const size_t height{768};
	const std::string filename{"out.ppm"};
	const float fov{1.6f};
	
	std::vector<Vec3f> buffer(width * height);
	for (size_t i{0}; i < height; ++i)
	{
		for (size_t j{0}; j < width; ++j)
		{
			// set the camera at the origin
			// screen at z = 1
			float x{2.f * (j + 0.5f) / static_cast<float>(width) * tan(fov * 0.5f)};
			float y{2.f * (i + 0.5f) / static_cast<float>(height) * tan(fov * 0.5f)
				    * height / static_cast<float>(width)};
			Vec3f dir{x, y, 1};
			buffer[i * width + j] = sceneIntersect({0, 0, 0}, normalize(dir), objects);
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
	const Material orange{{0.9f, 0.7f, 0.f}};
	const Material lapis{{0.f, 0.4f, 1.f}};
	std::vector<std::unique_ptr<Object> > objects;
	objects.push_back(std::make_unique<Sphere>(Vec3f{70.f, 40.f, 120.f}, 20.f, orange));
	objects.push_back(std::make_unique<Sphere>(Vec3f{300.f, 200.f, 200.f}, 20.f, orange));
	objects.push_back(std::make_unique<Sphere>(Vec3f{12.f, 20.f, 20.f}, 4.f, lapis));
	render(objects);
	return 0;
}
