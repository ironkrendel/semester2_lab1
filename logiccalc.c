#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include <tetostack.h>
#include <logiccalclib.h>

int main(int argc, char** argv) {
    if (argc <= 1) {
        printf("Help message\n");

        return 0;
    }

    char* str = prepareString(argv[1]);

    printf("%s\n", str);

    str = padOperators(str);

    printf("%s\n", str);

    return 0;
}