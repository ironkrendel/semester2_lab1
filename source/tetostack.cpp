#include <tetostack.hpp>
#include <colors.hpp>

Teto::TetoStack::TetoStack() {
    size = TETO_DEFAULT_STACK_SIZE;
    pData = new Teto::TetoElement[TETO_DEFAULT_STACK_SIZE];
    // std::cout << "C " << pData << " " << size << std::endl;
}

Teto::TetoStack::TetoStack(std::size_t _size) {
    size = _size;
    pData = new Teto::TetoElement[_size];
    // std::cout << "C " << pData << " " << size << std::endl;
}

Teto::TetoStack::TetoStack(const Teto::TetoStack& src) {
    if (this == &src) return;

    // if (pData != nullptr) {
    //     delete[] pData;
    // }
    index = src.index;
    size = src.size;
    pData = new Teto::TetoElement[size];
    // std::cout << pData << " - " << src.pData << " " << size << std::endl;
    // std::cout << pData << std::endl;
    // std::memcpy(pData, src.pData, size * sizeof(TetoElement));
    std::copy(src.pData, src.pData + size - 1, pData);
    // std::cout << pData[0].data.value << std::endl;
}

Teto::TetoStack::~TetoStack() {
    // std::cout << pData << " " << size << std::endl;
    if (pData != nullptr) {
        delete[] pData;
    }
    pData = nullptr;
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

Teto::TetoStack& Teto::TetoStack::operator=(const Teto::TetoStack& src) noexcept {
    if (this == &src) return *this;

    std::cout << pData << " " << src.pData << std::endl;
    if (pData != nullptr) {
        delete[] pData;
    }
    index = src.index;
    size = src.size;
    pData = new Teto::TetoElement[size];
    // std::cout << pData << std::endl;
    std::copy(src.pData, src.pData + size - 1, pData);
    // std::cout << pData[0].data.value << std::endl;
    return *this;
}