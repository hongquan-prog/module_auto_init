#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>
#include "mod_init.h"
#include "iwdg_inface.h"

static iwdg_inface_t *prv_handle = NULL;

void main()
{
    mod_init();
    prv_handle = dev_find("dev1");

    if (NULL == prv_handle)
    {
        exit(1);
    }
    
    iwdg_init(prv_handle);

    while(1)
    {
        iwdg_reload(prv_handle);
        sleep(1);
    }
}
