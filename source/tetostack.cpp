#include <tetostack.hpp>
#include <colors.hpp>

Teto::TetoStack::TetoStack() {
    size = TETO_DEFAULT_STACK_SIZE;
    pData = new Teto::TetoElement[TETO_DEFAULT_STACK_SIZE];
}

Teto::TetoStack::TetoStack(std::size_t _size) {
    size = _size;
    pData = new Teto::TetoElement[_size];
}

Teto::TetoStack::~TetoStack() {
    delete[] pData;
}

Teto::TetoElement Teto::TetoStack::pop() {
    if (index <= 0) {
        std::cout << ANSI_COLOR_BRIGHT_RED "TetoStack Error! Pop called for empty stack!" ANSI_COLOR_RESET << std::endl;
        // exit(1);
        throw std::runtime_error("");
    }
    return pData[--index];
}

Teto::TetoElement Teto::TetoStack::getTop() {
    if (index <= 0) {
        std::cout << ANSI_COLOR_BRIGHT_RED "TetoStack Error! GetTop called for empty stack!" ANSI_COLOR_RESET << std::endl;
        // exit(1);
        throw std::runtime_error("");
    }
    return pData[index - 1];
}

void Teto::TetoStack::push(TetoElement value) {
    if (index >= size) {
        std::cout << ANSI_COLOR_BRIGHT_RED "TetoStack Error! Stack overflow!" ANSI_COLOR_RESET << std::endl;
        // exit(1);
        throw std::runtime_error("");
    }
    pData[index++] = value;
}

bool Teto::TetoStack::isEmpty() {
    return index == 0;
}

std::size_t Teto::TetoStack::getSize() {
    return size;
}

std::size_t Teto::TetoStack::getElementCount() {
    return index;
}

Teto::TetoElement* Teto::TetoStack::data() {
    return pData;
}