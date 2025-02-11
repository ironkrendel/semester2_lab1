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
        TetoElement* pData = nullptr;
        std::size_t size = TETO_DEFAULT_STACK_SIZE;
        std::size_t index = 0;
    public:
        TetoStack();
        TetoStack(std::size_t stack_size);
        TetoStack(const Teto::TetoStack& src);
        ~TetoStack();
        TetoElement pop();
        TetoElement getTop();
        void push(TetoElement value);
        bool isEmpty();
        std::size_t getSize();
        std::size_t getElementCount();
        TetoElement* data();
        TetoStack& operator=(const TetoStack& src) noexcept;
        TetoStack& operator=(TetoStack&& src) noexcept;
    };
};