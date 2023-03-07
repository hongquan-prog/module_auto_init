#include "dev.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dev_node
{
    struct dev_node *next;
    char *name;
    void *user_data;
} dev_node_t;

typedef struct
{
    int length;
    dev_node_t list;
} device_table_t;

static device_table_t prv_table = {0};

bool dev_register(char *id, void *data)
{
    char *name = NULL;
    dev_node_t *temp = NULL;
    dev_node_t *iterator  = NULL;
    
    if(NULL == id)
    {
        printf("%s: device id is empty!", __FUNCTION__);
        return false;
    }

    temp = (dev_node_t *)malloc(sizeof(dev_node_t));
    name = strdup(id);

    if ((NULL == temp) || (NULL == name))
    {
        printf("%s: memory not enough!", __FUNCTION__);
        return false;
    }

    temp->next = NULL;
    temp->name = name;
    temp->user_data = data;
    iterator = &prv_table.list;

    for (int i = 0; i < prv_table.length; i++)
    {
        iterator = iterator->next;
    }

    iterator->next = temp;
    prv_table.length++;
    
    return true;
}

void *dev_find(char *name)
{
    int len = strlen(name);
    dev_node_t *iterator  = &prv_table.list;

    for (int i = 0; i < prv_table.length; i++)
    {
        iterator = iterator->next;

        if (!iterator->name)
        {
            continue;
        }

        if ((strlen(iterator->name) == len) && !strncmp(iterator->name, name, len))
        {
            break;
        }
    }

    if (iterator)
    {
        return iterator->user_data;
    }

    return NULL;
}
