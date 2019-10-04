#include "time.h"
#include <stdlib.h>

TIME_DLL tick_t TIME_DECL time_tick(void)
{
	tick_t d;
	__asm__ __volatile__ ("rdtsc" : "=A" (d) );
	return d;
}