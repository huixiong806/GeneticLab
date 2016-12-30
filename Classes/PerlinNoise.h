#ifndef PERLINNOISE_H
#define PERLINNOISE_H
#include <random>
#include <array>
//PerlinNoise模板来源于
//http://blog.kazade.co.uk/2014/05/a-public-domain-c11-1d2d3d-perlin-noise.html
/************************************************
类名:PerlinNoise
功能:产生柏林噪声
备注:无
************************************************/
class PerlinNoise 
{
public:
	PerlinNoise(uint32_t seed = 0);

	double noise(double x) const { return noise(x, 0, 0); }
	double noise(double x, double y) const { return noise(x, y, 0); }
	double noise(double x, double y, double z) const;

private:
	std::array<int, 512> p;
};

class PerlinOctave 
{
public:
	PerlinOctave(int octaves, uint32_t seed = 0);
	double noise(double x) const { return noise(x, 0, 0); }
	double noise(double x, double y) const { return noise(x, y, 0); }
	double noise(double x, double y, double z) const;
private:
	PerlinNoise perlin_;
	int octaves_;
};
#endif