#include "vec.hpp"

Vec3f reflect(const Vec3f &incident, const Vec3f &normal)
{
	return incident - 2.f * normal * dot(incident, normal);
}

Vec3f refract(const Vec3f &incident, const Vec3f &normal, const float refrativeIdex)
{
	float cosi{-std::max(-1.f, std::min(1.f, dot(normal, incident)))};
	float etai{1.f}, etat{refrativeIdex};
	Vec3f n{normal};
	if (cosi < 0)
	{
		cosi = -cosi;
		std::swap(etai, etat);
		n = -n;
	}

	float eta{etai / etat};
	float k{1 - eta * eta * (1 - cosi * cosi)};
	const Vec3f noRefract{epsilon, epsilon, epsilon};

	return k < 0 ? noRefract : incident * eta + normal * (eta * cosi - std::sqrtf(k));
}
