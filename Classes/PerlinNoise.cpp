#include"PerlinNoise.h"
/************************************************
函数名:Noise
功能:随机数发生器
备注:未经过处理
************************************************/
double PerlinNoise::Noise(unsigned long long x)
{
	x = (x << 13) ^ x;
	return 1.0 - ((x * (x * x * seed + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0 + 1;
}
/************************************************
函数名:smoothedNoise
功能:平滑噪声(取平均值)
备注:无
************************************************/
double PerlinNoise::smoothedNoise(double x)
{
	return Noise(x) / 2 + Noise(x - 1) / 4 + Noise(x + 1) / 4;
}
/************************************************
函数名:interpolate
功能:线性插值函数
备注:无
************************************************/
double PerlinNoise::interpolate(double a, double b, double x)
{
	return a*(1 - x) + b*x;
}
/************************************************
函数名:interpolatedNoise
功能:插值噪声
备注:无
************************************************/
double PerlinNoise::interpolatedNoise(double x)
{
	int int_x = int(x);
	double fractional_x = x - int_x;
	double v1 = smoothedNoise(int_x);
	double v2 = smoothedNoise(int_x + 1);
	return interpolate(v1, v2, fractional_x);
}
/************************************************
函数名:perlin_noise
功能:最终函数,传入x返回对应的y
备注:无
************************************************/
double PerlinNoise::perlin_noise(double x)
{
	double total = 0;
	double freq = frequency;
	double ampl = amplitude;
	for (int i = 0; i <= 4; i++)
	{
		total += interpolatedNoise(x*freq)*ampl;
		freq *= 2; ampl /= 2.0;
	}
	return int(total * 5);
}