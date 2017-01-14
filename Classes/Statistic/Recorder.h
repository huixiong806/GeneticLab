#ifndef RECORDER_H
#define RECORDER_H
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>
class Recorder
{
private:
	int frequency;
	std::ofstream outputStream;
public:
	Recorder();
	void setFrequency(int freq)
	{
		frequency = freq;
	}
	void tick(std::vector<unsigned long long> datas);
};
#endif
