#include "iwdg_inface.h"

void iwdg_init(iwdg_inface_t *p)
{
    ((iwdg_drv_t *)p)->init(p);
}

void iwdg_reload(iwdg_inface_t *p)
{
    ((iwdg_drv_t *)p)->reload(p);
}