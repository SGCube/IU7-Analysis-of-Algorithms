#ifndef __TIME__H__

#define __TIME__H__

#ifdef TIME_EXPORTS
#define TIME_DLL __declspec(dllexport)
#else
#define TIME_DLL __declspec(dllimport)	
#endif

#define TIME_DECL __cdecl

typedef unsigned long long tick_t;

TIME_DLL tick_t TIME_DECL time_tick(void);

#endif