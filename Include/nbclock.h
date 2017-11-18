

#ifndef __NB_CLOCK_HPP_INCLUDED__
#define __NB_CLOCK_HPP_INCLUDED__

//获取CPU时间
#include <stdint.h>

class nbclock
{
public:

	nbclock ();
	~nbclock ();
	static uint64_t rdtsc ();
	static uint64_t now_us ();
	uint64_t now_ms ();

private:
	uint64_t last_tsc;
	uint64_t last_time;

	nbclock (const nbclock&);
	const nbclock &operator = (const nbclock&);
};

#endif
