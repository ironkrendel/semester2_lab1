#include <tetostack.h>

void createStack(TetoStack* stack, unsigned int size, unsigned int element_size) {
    if (size <= 0) {
        printErrorMsg("Trying to create stack without specified size!");
        exit(1);
    }
    stack->elementSize = element_size;
    stack->size = size;
    stack->index = 0;
    stack->data = malloc(element_size * size);
}

void destroyStack(TetoStack* stack) {
    if (stack->data == NULL) {
        printErrorMsg("Trying to destroy uninitialized stack!");
        exit(1);
    }
    free(stack->data);
    stack->data = NULL;
    stack->elementSize = 0;
    stack->size = 0;
    stack->index = 0;
}

TetoBool isEmpty(TetoStack* stack) {
    if (stack->data == NULL) {
        return 1;
    }
    return stack->index == 0;
}

void* popStack(TetoStack* stack) {
    if (stack->data == NULL) {
        printErrorMsg("Trying to pop from uninitialized stack!");
        exit(1);
    }
    if (stack->index == 0) {
        printErrorMsg("Pop from empty stack!");
        exit(1);
    }

    void* data = malloc(stack->elementSize);
    memcpy(data, stack->data + stack->elementSize * (stack->index - 1), stack->elementSize);
    stack->index--;

    return data;
}

void* popStackN(TetoStack* stack, unsigned long count) {
    if (stack->data == NULL) {
        printErrorMsg("Trying to pop from uninitialized stack!");
        exit(1);
    }
    if (count > stack->index) {
        printf(ANSI_COLOR_BRIGHT_RED "Pop from empty stack! Trying to pop %ld elements, but stack has only %ld!" ANSI_COLOR_RESET "\n", count, stack->index);
        exit(1);
    }

    void* data = malloc(stack->elementSize * count);
    memcpy(data, stack->data + stack->elementSize * (stack->index - count), stack->elementSize * count);
    stack->index -= count;

    return data;
}

void pushStack(TetoStack* stack, void* data) {
    if (stack->data == NULL) {
        printErrorMsg("Trying to push to uninitialized stack!");
        exit(1);
    }
    if (stack->index >= stack->size) {
        printErrorMsg("Stack overflow!");
        exit(1);
    }

    memcpy(stack->data + stack->elementSize * stack->index, data, stack->elementSize);
    stack->index++;
}

void pushStackN(TetoStack* stack, unsigned long count, void* data) {
    if (stack->data == NULL) {
        printErrorMsg("Trying to push to uninitialized stack!");
        exit(1);
    }
    if ((stack->index + count) > stack->size) {
        printErrorMsg("Stack overflow!");
        exit(1);
    }

    memcpy(stack->data + stack->elementSize * stack->index, data, count * stack->elementSize);
    stack->index += count;
}