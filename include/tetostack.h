#pragma once

#include <logiccalclib.h>

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

struct TETOSTACKSTRUCT
{
    size_t elementSize;
    unsigned long size;
    void* data;
    unsigned long index;
};

typedef struct TETOSTACKSTRUCT TetoStack;
typedef unsigned char TetoBool;

void createStack(TetoStack* stack, unsigned int size, unsigned int element_size);

void destroyStack(TetoStack* stack);

TetoBool isEmpty(TetoStack* stack);

void* popStack(TetoStack* stack);

void* popStackN(TetoStack* stack, unsigned long count);

void pushStack(TetoStack* stack, void* data);

void pushStackN(TetoStack* stack, unsigned long count, void* data);