#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <limits>
#include "vec.hpp"
#include "object.hpp"

Vec3f trace(const Vec3f &origin, const Vec3f &dir, const Sphere &sphere)
{
	float dist{std::numeric_limits<float>::max()};
	if (sphere.intersect(origin, dir, dist))
		return {0.9f, 0.7f, 0.f};
	else
		return {0.2f, 0.2f, 0.2f};
}

void render()
{
	const size_t width{1024};
	const size_t height{768};
	const std::string filename{"out.ppm"};
	const float fov{1.6f};
	
	std::vector<Vec3f> buffer(width * height);
	Sphere sphere{{70.f, -40.f, 120.f}, 20.f};
	for (size_t i{0}; i < height; ++i)
	{
		for (size_t j{0}; j < width; ++j)
		{
			// set the camera at the origin
			// screen at z = 1
			float x{2.f * (j + 0.5f) / static_cast<float>(width) * tan(fov * 0.5f)};
			float y{-2.f * (i + 0.5f) / static_cast<float>(height) * tan(fov * 0.5f)
				    * height / static_cast<float>(width)};
			Vec3f dir{x, y, 1};
			buffer[i * width + j] = trace({0, 0, 0}, normalize(dir), sphere);
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
	render();
	return 0;
}
