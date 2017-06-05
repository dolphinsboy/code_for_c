#ifndef TRACE_H
#define TRACE_H

#include <stdio.h>

void __cyg_profile_func_enter(void *this_fn, void *call_site)
                              __attribute__((no_instrument_function));

void __cyg_profile_func_exit(void *this_fn, void *call_site)
                             __attribute__((no_instrument_function));
#endif
