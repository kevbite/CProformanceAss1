#pragma once
#include <windows.h>
#include "Singleton.h"

class MethodTimer : public Singleton<MethodTimer>
{
private:
	//declare some large ints
	LARGE_INTEGER f, t1, t2;

public:
	MethodTimer()
	{}
	void start()
	{
		//get the counter now
		QueryPerformanceCounter(&t1);
		
	}
	void end()
	{
		//get couters afterwards
		QueryPerformanceCounter(&t2);
		QueryPerformanceFrequency(&f);

	}
	void displayTimeTaken()
	{
		//display time
		std::cout << std::endl << "End, time = "
					<< ((t2.QuadPart - t1.QuadPart) / (double)f.QuadPart)
					<< " seconds" << std::endl << std::endl;		
	}

};
