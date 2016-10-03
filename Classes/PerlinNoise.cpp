#include"PerlinNoise.h"
/************************************************
������:Noise
����:�����������
��ע:δ��������
************************************************/
double PerlinNoise::Noise(unsigned long long x)
{
	x = (x << 13) ^ x;
	return 1.0 - ((x * (x * x * seed + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0 + 1;
}
/************************************************
������:smoothedNoise
����:ƽ������(ȡƽ��ֵ)
��ע:��
************************************************/
double PerlinNoise::smoothedNoise(double x)
{
	return Noise(x) / 2 + Noise(x - 1) / 4 + Noise(x + 1) / 4;
}
/************************************************
������:interpolate
����:���Բ�ֵ����
��ע:��
************************************************/
double PerlinNoise::interpolate(double a, double b, double x)
{
	return a*(1 - x) + b*x;
}
/************************************************
������:interpolatedNoise
����:��ֵ����
��ע:��
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
������:perlin_noise
����:���պ���,����x���ض�Ӧ��y
��ע:��
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