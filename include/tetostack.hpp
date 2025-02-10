#pragma once

#include <logiccalclib.hpp>

#include <iostream>

#define TETO_DEFAULT_STACK_SIZE 10000

namespace Teto {
    template<typename T>
    class TetoStack {
    private:
        T* pData;
        std::size_t size;
        std::size_t index = 0;
    public:
        TetoStack();
        TetoStack(std::size_t stack_size);
        ~TetoStack();
        T pop();
        T getTop();
        void push(T value);
        bool isEmpty();
        std::size_t getSize();
        std::size_t getElementCount();
        T* data();
    };
};