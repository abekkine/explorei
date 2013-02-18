#include <stdio.h>

#include <timer.h>

Timer::Timer()
{
//DEBUG
    puts("Timer::Timer()");
//END
    initVars();
    Reset();
}

Timer::~Timer()
{
//DEBUG
    puts("Timer::~Timer()");
//END
}

void Timer::initVars()
{
    _currentTime = 0.0;
    _startTime = 0.0;
}

double Timer::CurrentTime()
{
    _currentTime = omp_get_wtime();

    return _currentTime;
}

void Timer::Reset()
{
    _startTime = CurrentTime();
}

double Timer::GetElapsed()
{
    return CurrentTime() - _startTime;
}
