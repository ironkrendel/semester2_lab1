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

            std::cout << str << std::endl;

            Teto::TetoStack postfix = lcl::convertToPostfix(str);

            // std::cout << " " << postfix.getElementCount() << std::endl;
            while (!postfix.isEmpty()) {
                Teto::TetoElement elem = postfix.pop();
                if (elem.isOp) {
                    std::cout << elem.data.op << std::endl;
                }
                else {
                    std::cout << elem.data.value << std::endl;
                }
            }

            // if (result) {
            //     std::cout << ANSI_COLOR_BRIGHT_GREEN << "true" << ANSI_COLOR_RESET << std::endl;
            // }
            // else {
            //     std::cout << ANSI_COLOR_RED << "false" << ANSI_COLOR_RESET << std::endl;
            // }
        }
        catch (std::exception& e) {
            continue;
        }
    }

    return 0;
}