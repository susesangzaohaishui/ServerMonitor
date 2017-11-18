#include "nbclock.h"
#include "windowshelp.hpp"
#include <stddef.h>
#include <intrin.h>



nbclock::nbclock () :
    last_tsc (rdtsc ()),
    last_time (now_us () / 1000)
{
}

nbclock::~nbclock ()
{
}

uint64_t nbclock::now_us ()
{
    LARGE_INTEGER ticksPerSecond;
    QueryPerformanceFrequency (&ticksPerSecond);

    LARGE_INTEGER tick;
    QueryPerformanceCounter (&tick);

    double ticks_div = (double) (ticksPerSecond.QuadPart / 1000000);     
    return (uint64_t) (tick.QuadPart / ticks_div);
}

uint64_t nbclock::now_ms ()
{
    uint64_t tsc = rdtsc ();

    if (!tsc)
		return now_us () / 1000;


    if ((tsc - last_tsc <= (1000000 / 2) && tsc >= last_tsc))
        return last_time;

    last_tsc = tsc;
    last_time = now_us () / 1000;
    return last_time;
}

uint64_t nbclock::rdtsc ()
{
    return __rdtsc ();

}
