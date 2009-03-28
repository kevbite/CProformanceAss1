#pragma once
#include <windows.h>
#include "Singleton.h"

/*	MethodTimer Times how long it has
	taken to get from start to end
*/
class MethodTimer :
	public Singleton<MethodTimer> //Makes class a singleton
{
private:
	//declare some large ints
	LARGE_INTEGER f, t1, t2;

public:
	MethodTimer()
	{}
	/*	Starts the timer	*/
	void start()
	{
		//get the counter now
		QueryPerformanceCounter(&t1);
		
	}
	/*	Ends the timer */
	void end()
	{
		//get couters afterwards
		QueryPerformanceCounter(&t2);
		QueryPerformanceFrequency(&f);

	}
	/*	calcs the time taken between start and end	*/
	void displayTimeTaken()
	{
		//display time
		std::cout << std::endl << "End, time = "
					<< ((t2.QuadPart - t1.QuadPart) / (double)f.QuadPart)
					<< " seconds" << std::endl << std::endl;		
	}

};
