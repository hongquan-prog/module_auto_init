#pragma once

typedef int (*init_fn_t)(void);

#define MOD_SECTION(x)   __attribute__((section(x)))
#define MOD_USED         __attribute__((used))

#define MOD_DEBUG_INIT 0

#if MOD_DEBUG_INIT
struct mod_init_desc
{
    const char *fn_name;
    const init_fn_t fn;
};

#define MOD_INIT_EXPORT(fn, level)                                                                \
    const char __mod_init_##fn##_name[] = #fn;                                                    \
    MOD_USED const struct mod_init_desc __mod_init_desc_##fn MOD_SECTION(".mod_init_fn." level) = \
        {__mod_init_##fn##_name, fn};

#else
#define MOD_INIT_EXPORT(fn, level) \
    MOD_USED const init_fn_t __mod_init_##fn MOD_SECTION(".mod_init_fn."level) = fn
#endif

#define INIT_MOD_LEVEL1(fn)       MOD_INIT_EXPORT(fn, "1")
#define INIT_MOD_LEVEL2(fn)       MOD_INIT_EXPORT(fn, "2")
#define INIT_MOD_LEVEL3(fn)       MOD_INIT_EXPORT(fn, "3")
#define INIT_MOD_LEVEL4(fn)       MOD_INIT_EXPORT(fn, "4")
#define INIT_MOD_LEVEL5(fn)       MOD_INIT_EXPORT(fn, "5")
#define INIT_MOD_LEVEL6(fn)       MOD_INIT_EXPORT(fn, "6")
#define INIT_MOD_LEVEL7(fn)       MOD_INIT_EXPORT(fn, "7")

void mod_init(void);