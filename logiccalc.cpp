#include <tetostack.hpp>
#include <logiccalclib.hpp>

#include <iostream>

Teto::TetoStack<int> stack;

int main(int argc, char** argv) {
    if (argc <= 1) {
        printf("Help message\n");

        return 0;
    }

    std::string str = lcl::prepareString(argv[1]);

    std::cout << str << std::endl;

    lcl::checkString(str);

    str = lcl::padOperators(str);

    std::cout << str << std::endl;

    str = lcl::convertToPostfix(str);

    std::cout << str << std::endl;

    bool result = lcl::calculatePostfix(str);

    if (result) {
        std::cout << "true" << std::endl;
    }
    else {
        std::cout << "false" << std::endl;
    }

    return 0;
}