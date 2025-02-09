#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include <tetostack.hpp>
#include <logiccalclib.hpp>

char OP_PRIORITIES[125];

Teto::TetoStack<int> stack;

int main(int argc, char** argv) {
    if (argc <= 1) {
        printf("Help message\n");

        return 0;
    }

    lcl::populateOpPriorities(OP_PRIORITIES);

    std::string str = lcl::prepareString(argv[1]);

    std::cout << str << std::endl;

    lcl::checkString(str);

    str = lcl::padOperators(str);

    std::cout << str << std::endl;

    return 0;
}