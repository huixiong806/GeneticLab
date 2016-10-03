#ifndef PERLINNOISE_H
#define PERLINNOISE_H
/************************************************
����:perlin noise
����:������������
��ע:��
************************************************/
class PerlinNoise
{
public:
	double frequency;
	double amplitude;//���ȣ��ɸģ�Խ����θ߶ȱ仯Խ��
	unsigned long long seed;
	//�����������(δ��������)
	double Noise(unsigned long long x);
	//ƽ������(ȡƽ��ֵ)
	double smoothedNoise(double x);
	//���Բ�ֵ����
	double interpolate(double a, double b, double x);
	//��ֵ����
	double interpolatedNoise(double x);
	//���պ���,����x���ض�Ӧ��y
	double perlin_noise(double x);
};
#endif