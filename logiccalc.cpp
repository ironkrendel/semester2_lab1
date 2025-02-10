#include <tetostack.hpp>
#include <logiccalclib.hpp>

#include <iostream>

Teto::TetoStack<int> stack;

int main(int argc, char** argv) {
    if (argc <= 1) {
        printf("Help message\n");

        return 0;
    }

    for (int i = 1;i < argc;i++) {
        try {
            if (strlen(argv[i]) <= 0) {
                lcl::printErrorMsg("Error! String is empty!");
                continue;
            }

            std::string str = lcl::prepareString(argv[i]);

            // std::cout << str << std::endl;

            lcl::checkString(str);

            str = lcl::padOperators(str);

            // std::cout << str << std::endl;

            str = lcl::convertToPostfix(str);

            // std::cout << str << std::endl;

            bool result = lcl::calculatePostfix(str);

            if (result) {
                std::cout << ANSI_COLOR_BRIGHT_GREEN << "true" << ANSI_COLOR_RESET << std::endl;
            }
            else {
                std::cout << ANSI_COLOR_RED << "false" << ANSI_COLOR_RESET << std::endl;
            }
        }
        catch (std::exception& e) {
            continue;
        }
    }

    return 0;
}