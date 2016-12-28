#include "Recorder.h"
#include <Windows.h>
using namespace std;
Recorder::Recorder()
{
	SYSTEMTIME sysTime;
	ZeroMemory(&sysTime, sizeof(sysTime));
	GetLocalTime(&sysTime);
	stringstream filePath;
	filePath << "data\\experiment" << (int)sysTime.wYear << "." << (int)sysTime.wMonth << "." << (int)sysTime.wDay << ".";
	filePath << (int)sysTime.wHour << "_" << (int)sysTime.wMinute << "_" << (int)sysTime.wSecond << ".csv";
	outputStream.open(filePath.str().c_str(), ios::out);
	outputStream << "tick,food,Gloop,Floop,Sloop" << endl;
}
void Recorder::tick(vector<unsigned long long> datas)
{
	static unsigned long long ticks = 0;
	++ticks;
	if (ticks%frequency == 0)
	{
		outputStream << ticks << ",";
		for (auto i : datas)
			outputStream << i << ",";
		outputStream << endl;
	}
}