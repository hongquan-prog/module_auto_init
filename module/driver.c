#include <stdio.h>
#include "mod_init.h"

#define TAG "driver"

static int level1_init()
{
    printf("%s finish\r\n", __FUNCTION__);
    return 0;
}

static int level2_init()
{
    printf("%s finish\r\n", __FUNCTION__);
    return 0;
}

static int level3_init()
{
    printf("%s finish\r\n", __FUNCTION__);
    return 0;
}

static int level4_init()
{
    printf("%s finish\r\n", __FUNCTION__);
    return 0;
}

static int level5_init()
{
    printf("%s finish\r\n", __FUNCTION__);
    return 0;
}

static int level6_init()
{
    printf("%s finish\r\n", __FUNCTION__);
    return 0;
}

static int level7_init()
{
    printf("%s finish\r\n", __FUNCTION__);
    return 0;
}

INIT_MOD_LEVEL1(level1_init);
INIT_MOD_LEVEL2(level2_init);
INIT_MOD_LEVEL3(level3_init);
INIT_MOD_LEVEL4(level4_init);
INIT_MOD_LEVEL5(level5_init);
INIT_MOD_LEVEL6(level6_init);
INIT_MOD_LEVEL7(level7_init);

