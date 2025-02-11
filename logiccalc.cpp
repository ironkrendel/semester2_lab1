#include <tetostack.hpp>
#include <logiccalclib.hpp>

#include <iostream>

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

            std::string str = argv[i];

            lcl::checkString(str);

            Teto::TetoStack postfix = lcl::convertToPostfix(str);

            Teto::TetoStack copy = postfix;

            while (!copy.isEmpty()) {
                if (copy.getTop().isOp) {
                    std::cout << copy.pop().data.op << " ";
                }
                else {
                    std::cout << copy.pop().data.value << " ";
                }
            }
            std::cout << std::endl;

            int result = lcl::calculatePostfix(postfix);

            if (result) {
                std::cout << ANSI_COLOR_BRIGHT_GREEN "true" ANSI_COLOR_RESET << std::endl;
            }
            else {
                std::cout << ANSI_COLOR_BRIGHT_RED "false" ANSI_COLOR_RESET << std::endl;
            }
        }
        catch (std::exception& e) {
            continue;
        }
    }

    return 0;
}