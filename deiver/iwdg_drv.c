#include <stdio.h>
#include "iwdg_inface.h"
#include "mod_init.h"

#define DEV_NAME "dev1"

static void prv_iwdg_init(iwdg_inface_t *obj)
{
    printf("iwdg init\r\n");
}

static void prv_iwdg_reload(iwdg_inface_t *obj)
{
    printf("iwdg reload\r\n");
}

static iwdg_drv_t prv_iwdg = {
        .init = prv_iwdg_init,
        .reload = prv_iwdg_reload};

static int prv_iwdg_register()
{
    dev_register(DEV_NAME, &prv_iwdg);
    return 0;
}

INIT_MOD_LEVEL1(prv_iwdg_register);

