#ifndef PERLINNOISE_H
#define PERLINNOISE_H
/************************************************
类名:perlin noise
功能:产生柏林噪声
备注:无
************************************************/
class PerlinNoise
{
public:
	double frequency;
	double amplitude;//幅度，可改，越大地形高度变化越大
	unsigned long long seed;
	//随机数发生器(未经过处理)
	double Noise(unsigned long long x);
	//平滑噪声(取平均值)
	double smoothedNoise(double x);
	//线性插值函数
	double interpolate(double a, double b, double x);
	//插值噪声
	double interpolatedNoise(double x);
	//最终函数,传入x返回对应的y
	double perlin_noise(double x);
};
#endif