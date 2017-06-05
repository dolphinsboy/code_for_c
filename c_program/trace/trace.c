#include "trace.h"
#include <stdio.h>

void __cyg_profile_func_enter(void *this_fn, void *call_site) {
  printf("ENTER: %p, from %p\n", this_fn, call_site);
} /* __cyg_profile_func_enter */

void __cyg_profile_func_exit(void *this_fn, void *call_site) {
  printf("EXIT:  %p, from %p\n", this_fn, call_site);
} /* __cyg_profile_func_enter */
