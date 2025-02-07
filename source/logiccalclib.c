#include <logiccalclib.h>

void printErrorMsg(char* msg) {
    printf(ANSI_COLOR_BRIGHT_RED "%s" ANSI_COLOR_RESET "\n", msg);
}

char* prepareString(char* string) {
    char* newString = malloc((strlen(string) + 1) * sizeof(char));
    unsigned long index = 0;

    unsigned long string_length = strlen(string);
    for (unsigned long i = 0;i < string_length;i++) {
        if (string[i] == ' ') continue;
        else if (string[i] == 'T' || string[i] == 't') {
            if (i + 4 <= string_length) {
                char* string_slice = malloc(sizeof(char) * 5);
                memcpy(string_slice, &string[i], sizeof(char) * 4);
                string_slice[4] = '\0';
                if (strcasecmp(string_slice, "true") == 0) {
                    i += 3;
                }
                free(string_slice);
            }
            newString[index] = SYM_TRUE;
        }
        else if (string[i] == 'F' || string[i] == 'f') {
            if (i + 5 <= string_length) {
                char* string_slice = malloc(sizeof(char) * 5);
                memcpy(string_slice, &string[i], sizeof(char) * 5);
                if (strcasecmp(string_slice, "false") == 0) {
                    i += 4;
                }
                free(string_slice);
            }
            newString[index] = SYM_FALSE;
        }
        else if (string[i] == '<') {
            if (i + 1 < string_length) {
                if (string[i + 1] == '=') {
                    newString[index] = SYM_OP_LESS_EQUAL;
                    i++;
                }
                else {
                    newString[index] = SYM_OP_LESS;
                }
            }
            else {
                newString[index] = SYM_OP_LESS;
            }
        }
        else if (string[i] == '>') {
            if (i + 1 < string_length) {
                if (string[i + 1] == '=') {
                    newString[index] = SYM_OP_MORE_EQUAL;
                    i++;
                }
                else {
                    newString[index] = SYM_OP_MORE;
                }
            }
            else {
                newString[index] = SYM_OP_MORE;
            }
        }
        else if (string[i] == '=' && i + 1 <= string_length && string[i + 1] == '=') {
            newString[index] = SYM_OP_EQUAL;
            i++;
        }
        else if (string[i] == '!') {
            if (i + 1 < string_length) {
                if (string[i + 1] == '=') {
                    newString[index] = SYM_OP_NOT_EQUAL;
                    i++;
                }
                else {
                    newString[index] = SYM_OP_NOT;
                }
            }
            else {
                newString[index] = SYM_OP_NOT;
            }
        }
        else if (string[i] == '&' && i + 1 <= string_length && string[i + 1] == '&') {
            newString[index] = SYM_OP_AND;
            i++;
        }
        else if (string[i] == '|' && i + 1 <= string_length && string[i + 1] == '|') {
            newString[index] = SYM_OP_OR;
            i++;
        }
        else if (string[i] == '^') {
            newString[index] = SYM_OP_XOR;
        }
        else if (string[i] == '-' && i + 1 <= string_length && string[i + 1] == '>') {
            newString[index] = SYM_OP_IMPLICATION;
            i++;
        }
        else if (string[i] == '(' || string[i] == ')' || isdigit(string[i])) {
            newString[index] = string[i];
        }
        else {
            printErrorMsg("Unknown operator encountered!");
            for (unsigned int _ = 0;_ < string_length;_++) printf("-");
            printf("\n");
            printf("%s\n", string);
            for (unsigned int _ = 0;_ < i;_++) printf(" ");
            printf(ANSI_COLOR_BRIGHT_RED "^" ANSI_COLOR_RESET "\n");
            for (unsigned int _ = 0;_ < string_length;_++) printf("-");
            printf(ANSI_COLOR_RESET "\n");
            exit(1);
        }
        index++;
    }
    newString[index] = '\0';

    newString = realloc(newString, (strlen(newString) + 1) * sizeof(char));

    return newString;
}

char* padOperators(char* string) {
    unsigned int newLen = strlen(string) + 1;
    for (unsigned int i = 0;i < strlen(string);i++) {
        if (isdigit(string[i])) continue;
        newLen += 2;
    }
    char* newString = malloc(sizeof(char) * newLen);
    int index = 0;
    for (unsigned int i = 0;i < strlen(string);i++) {
        if (isdigit(string[i])) {
            newString[index++] = string[i];
        }
        else {
            if (index != 0 && newString[index - 1] != ' ')
                newString[index++] = ' ';
            newString[index++] = string[i];
            newString[index++] = ' ';
        }
    }
    if (newString[index - 1] == ' ') {
        index--;
    }
    newString[index] = '\0';

    return newString;
}