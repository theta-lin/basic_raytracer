#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include "vec.hpp"

void render()
{
	const size_t width{1024};
	const size_t height{768};
	const std::string filename{"out.ppm"};
	
	std::vector<Vec3f> buffer(width * height);
	for (size_t i{0}; i < height; ++i)
	{
		for (size_t j{0}; j < width; ++j)
		{
			buffer[i * width + j] = {static_cast<float>(i) / height, static_cast<float>(j) / width, 0.f};
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
