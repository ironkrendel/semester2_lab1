#include <tetostack.hpp>
#include <logiccalclib.hpp>

#include <iostream>

// #define DEBUG

int main(int argc, char** argv) {
    if (argc <= 1) {
        lcl::printErrorMsg("No arguments passed! Exiting.");

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

            #ifdef DEBUG
                Teto::TetoStack copy = postfix;
                Teto::TetoStack reversedCopy;

                while (!copy.isEmpty()) {
                    reversedCopy.push(copy.pop());
                }

                while (!reversedCopy.isEmpty()) {
                    if (reversedCopy.getTop().isOp) {
                        std::cout << reversedCopy.pop().data.op << " ";
                    }
                    else {
                        std::cout << reversedCopy.pop().data.value << " ";
                    }
                }
                std::cout << std::endl;
            #endif

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