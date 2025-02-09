#include <tetostack.hpp>

template<>
Teto::TetoStack<int>::TetoStack() {
    size = TETO_DEFAULT_STACK_SIZE;
    data = new int[TETO_DEFAULT_STACK_SIZE];
}

template<>
Teto::TetoStack<int>::TetoStack(std::size_t _size) {
    size = _size;
    data = new int[_size];
}

template<>
Teto::TetoStack<int>::~TetoStack() {
    delete[] data;
}

template<>
int Teto::TetoStack<int>::pop() {
    if (index <= 0) {
        lcl::printErrorMsg(ANSI_COLOR_BRIGHT_RED "TetoStack Error! Pop called for empty stack!" ANSI_COLOR_RESET);
        exit(1);
    }
    return data[--index];
}

template<>
void Teto::TetoStack<int>::push(int value) {
    if (index >= size) {
        lcl::printErrorMsg(ANSI_COLOR_BRIGHT_RED "TetoStack Error! Stack overflow!" ANSI_COLOR_RESET);
        exit(1);
    }
    data[index++] = value;
}

template<>
bool Teto::TetoStack<int>::isEmpty() {
    return index == 0;
}

template<>
std::size_t Teto::TetoStack<int>::getSize() {
    return size;
}

template<>
std::size_t Teto::TetoStack<int>::getElementCount() {
    return index;
}