#pragma once

// #include <logiccalclib.hpp>

#include <iostream>

#define TETO_DEFAULT_STACK_SIZE 10000

namespace Teto {
    struct TetoElement {
        bool isOp;
        union {
            unsigned char op;
            int value;
        } data;
    };

    class TetoStack {
    private:
        TetoElement* pData;
        std::size_t size;
        std::size_t index = 0;
    public:
        TetoStack();
        TetoStack(std::size_t stack_size);
        ~TetoStack();
        TetoElement pop();
        TetoElement getTop();
        void push(TetoElement value);
        bool isEmpty();
        std::size_t getSize();
        std::size_t getElementCount();
        TetoElement* data();
    };
};