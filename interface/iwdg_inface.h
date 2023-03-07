#pragma once

#include "dev.h"

typedef void iwdg_inface_t;

typedef struct iwdg_drv
{
    void (*init)(iwdg_inface_t *obj);
    void (*reload)(iwdg_inface_t *obj);
    void *user_data;
} iwdg_drv_t;

void iwdg_init(iwdg_inface_t* obj);
void iwdg_reload(iwdg_inface_t* obj);