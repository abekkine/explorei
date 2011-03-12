#ifndef TIMER_H
#define TIMER_H

#include <omp.h>

class Timer
{
    public:
        Timer();
        ~Timer();
        void Reset();
        double GetElapsed();

    private:
        // Methods
		void initVars();
		double CurrentTime();

    private:
        // Members
		double _currentTime;
		double _startTime;
};

#endif

