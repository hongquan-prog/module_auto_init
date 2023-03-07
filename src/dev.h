#pragma once

#include <stdbool.h>

bool dev_register(char *name, void *data);
void *dev_find(char *name);