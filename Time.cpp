#include "Time.h"

using namespace std;
using namespace std::chrono;

void Time::start()
{
    beginning_time = high_resolution_clock::now();
}

void Time::stop()
{
    end_time = high_resolution_clock::now();
}

long Time::executionTime()
{
    return duration_cast<nanoseconds>(Time::end_time - Time::beginning_time).count();
}
