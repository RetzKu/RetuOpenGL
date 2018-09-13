#pragma once

// T‰‰ perkele ei toimi sit ku winukalla et t‰h‰n pit‰‰ sit teh‰ oma android #define :&
#include <Windows.h>

namespace Engine {

	class Timer
	{
	private:
		LARGE_INTEGER _start;
		double _frequency;
	public:
		Timer()
		{
			LARGE_INTEGER frequency;
			QueryPerformanceFrequency(&frequency);
			_frequency = 1.0f / frequency.QuadPart;
			QueryPerformanceCounter(&_start);
		}

		void reset()
		{
			QueryPerformanceCounter(&_start);
		}

		float elapsed()
		{
			LARGE_INTEGER current;
			QueryPerformanceCounter(&current);
			unsigned __int64 cycles = current.QuadPart - _start.QuadPart;
			return (float)(cycles * _frequency);
		}

	};
}