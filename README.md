# 模块自动初始化

- 在底层驱动和模块开发中，为了将业务和驱动分开，通常会设计一层接口
- 应用层通过接口访问底层硬件，而不需要关心底层如何实现，底层硬件发生变化时只需要适配接口而不必更改业务逻辑。
- 为了将底层驱动注册到接口中进行实例化，驱动层必须提供一个函数用于获取驱动，以便完成接口的初始化。
- 但是这样存在明显的缺点，底层通过函数传递信息时会将应用层和底层耦合在一起，降低了程序灵活性。

# 无自动初始化机制时的驱动

- 独立看门狗的接口

```c
#pragma once
typedef void iwdg_inface_t;

typedef struct iwdg_drv
{
    void (*init)(iwdg_inface_t *obj);
    void (*reload)(iwdg_inface_t *obj);
    void *user_data;
} iwdg_drv_t;

void iwdg_init(iwdg_inface_t* obj);
void iwdg_reload(iwdg_inface_t* obj);
```

```c
#include "iwdg_inface.h"

void iwdg_init(iwdg_inface_t *p)
{
    ((iwdg_drv_t *)p)->init(p);
}

void iwdg_reload(iwdg_inface_t *p)
{
    ((iwdg_drv_t *)p)->reload(p);
}
```

- 独立看门狗的驱动

```c
#pragma once

#include "iwdg_inface.h"

iwdg_inface_t *bsp_iwdg_inface_get(void);
```

```c
#include "iwdg_drv.h"

static void prv_iwdg_init(iwdg_inface_t *obj)
{
    printf("iwdg init\r\n");
}

static void prv_iwdg_reload(iwdg_inface_t *obj)
{
    printf("iwdg reload\r\n");
}

iwdg_inface_t *prv_iwdg_inface_get(void)
{
    static iwdg_drv_t iwdg_drv = {
        .init = prv_iwdg_init,
        .reload = prv_iwdg_reload};
    return &iwdg_drv;
}
```

- 业务层获取驱动实例

```c
#include "iwdg_drv.h"

static iwdg_inface_t *prv_handle = {0};

int main(void)
{
    prv_handle = bsp_iwdg_inface_get();
    iwdg_init(prv_handle);

    for(;;)
    {
        iwdg_reload(prv_handle);
        sleep(1);
    }
}

```
- 从上面的例子中可以看出，应用层为了获取驱动必须包含底层驱动的头文件，或者将bsp_iwdg_inface_get在应用层进行声明，否则无法获取到该实例。

# 添加自动初始化机制的驱动

- 为了能够让业务层直接获取到实例，可将需要自动注册的函数指针放入一个专用的段中，在段前后放置两个变量，系统初始化时将两个变量中间的函数读出并进行调用，被调用函数中包含了设备注册功能，从而自动将设备注册到设备管理器中，应用层通过设备管理器查找对应的设备并返回实例地址，通过该实例可对硬件进行访问。

- 此时独立看门狗的接口不变
- 独立看门狗的驱动利用自动初始化机制将实例注册到设备管理器中
```c
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
```

- 业务层通过设备管理器获取驱动实例
```c
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
```