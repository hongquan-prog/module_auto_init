#include "mod_init.h"
#include <stddef.h>
#include <stdio.h>

extern int _mod_init_fn_start;
extern int _mod_init_fn_end;

void mod_init(void)
{
#if MOD_DEBUG_INIT
    const struct mod_init_desc *desc = NULL;

    for (desc = (struct mod_init_desc *)&_mod_init_fn_start; desc < (struct mod_init_desc *)&_mod_init_fn_end; desc ++)
    {
        printf("initialize %s:%d done\n", desc->fn_name, desc->fn());
    }
#else
    const init_fn_t *func = NULL;
    
    for (func = (init_fn_t *)&_mod_init_fn_start; func < (init_fn_t *)&_mod_init_fn_end; func ++)
    {
        printf("%p\r\n", *func);
        (*func)();
    }
#endif
}