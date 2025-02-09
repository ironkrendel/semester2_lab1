#include <logiccalclib.hpp>

void lcl::printErrorMsg(std::string msg) {
    std::cout << ANSI_COLOR_BRIGHT_RED << msg << ANSI_COLOR_RESET << std::endl;
}

void lcl::printErrorMsg(const char* msg) {
    std::cout << ANSI_COLOR_BRIGHT_RED << msg << ANSI_COLOR_RESET << std::endl;
}

std::string lcl::prepareString(std::string string) {
    std::size_t string_length = string.length();
    std::string newString = std::string();
    newString.resize(string_length);
    std::size_t index = 0;
    
    for (unsigned long i = 0;i < string_length;i++) {
        if (string[i] == ' ') continue;
        else if (string[i] == 'T' || string[i] == 't') {
            if (i + 4 <= string_length) {
                char* string_slice = new char[5];
                memcpy(string_slice, &string[i], sizeof(char) * 4);
                string_slice[4] = '\0';
                if (strcasecmp(string_slice, "true") == 0) {
                    i += 3;
                }
                delete[] string_slice;
            }
            newString[index] = lcl::SYMS::SYM_TRUE;
        }
        else if (string[i] == 'F' || string[i] == 'f') {
            if (i + 5 <= string_length) {
                char* string_slice = new char[5];
                memcpy(string_slice, &string[i], sizeof(char) * 5);
                if (strcasecmp(string_slice, "false") == 0) {
                    i += 4;
                }
                delete[] string_slice;
            }
            newString[index] = lcl::SYMS::SYM_FALSE;
        }
        else if (string[i] == '<') {
            if (i + 1 < string_length) {
                if (string[i + 1] == '=') {
                    newString[index] = lcl::SYMS::SYM_OP_LESS_EQUAL;
                    i++;
                }
                else {
                    newString[index] = lcl::SYMS::SYM_OP_LESS;
                }
            }
            else {
                newString[index] = lcl::SYMS::SYM_OP_LESS;
            }
        }
        else if (string[i] == '>') {
            if (i + 1 < string_length) {
                if (string[i + 1] == '=') {
                    newString[index] = lcl::SYMS::SYM_OP_MORE_EQUAL;
                    i++;
                }
                else {
                    newString[index] = lcl::SYMS::SYM_OP_MORE;
                }
            }
            else {
                newString[index] = lcl::SYMS::SYM_OP_MORE;
            }
        }
        else if (string[i] == '=' && i + 1 <= string_length && string[i + 1] == '=') {
            newString[index] = lcl::SYMS::SYM_OP_EQUAL;
            i++;
        }
        else if (string[i] == '!') {
            if (i + 1 < string_length) {
                if (string[i + 1] == '=') {
                    newString[index] = lcl::SYMS::SYM_OP_NOT_EQUAL;
                    i++;
                }
                else {
                    newString[index] = lcl::SYMS::SYM_OP_NOT;
                }
            }
            else {
                newString[index] = lcl::SYMS::SYM_OP_NOT;
            }
        }
        else if (string[i] == '&' && i + 1 <= string_length && string[i + 1] == '&') {
            newString[index] = lcl::SYMS::SYM_OP_AND;
            i++;
        }
        else if (string[i] == '|' && i + 1 <= string_length && string[i + 1] == '|') {
            newString[index] = lcl::SYMS::SYM_OP_OR;
            i++;
        }
        else if (string[i] == '^') {
            newString[index] = lcl::SYMS::SYM_OP_XOR;
        }
        else if (string[i] == '-' && i + 1 <= string_length && string[i + 1] == '>') {
            newString[index] = lcl::SYMS::SYM_OP_IMPLICATION;
            i++;
        }
        else if (string[i] == '(' || string[i] == ')' || isdigit(string[i])) {
            newString[index] = string[i];
        }
        else {
            printErrorMsg("Unknown operator encountered!");
            for (unsigned int _ = 0;_ < string_length;_++) std::cout << "-";
            std::cout << std::endl << string << std::endl;
            for (unsigned int _ = 0;_ < i;_++) std::cout << " ";
            std::cout << ANSI_COLOR_BRIGHT_RED << "^" << ANSI_COLOR_RESET << std::endl;
            for (unsigned int _ = 0;_ < string_length;_++) std::cout << "-";
            std::cout << ANSI_COLOR_RESET << std::endl;
            exit(1);
        }
        index++;
    }
    newString[index] = '\0';

    newString.resize(strlen(newString.data()));

    return newString;
}

unsigned char lcl::symCharToId(unsigned char sym) {
    if (sym == lcl::SYMS::SYM_TRUE) return lcl::SYMS_ID::SYM_TRUE;
    if (sym == lcl::SYMS::SYM_FALSE) return lcl::SYMS_ID::SYM_FALSE;
    if (sym == lcl::SYMS::SYM_OP_LESS) return lcl::SYMS_ID::SYM_OP_LESS;
    if (sym == lcl::SYMS::SYM_OP_LESS_EQUAL) return lcl::SYMS_ID::SYM_OP_LESS_EQUAL;
    if (sym == lcl::SYMS::SYM_OP_MORE) return lcl::SYMS_ID::SYM_OP_MORE;
    if (sym == lcl::SYMS::SYM_OP_MORE_EQUAL) return lcl::SYMS_ID::SYM_OP_MORE_EQUAL;
    if (sym == lcl::SYMS::SYM_OP_EQUAL) return lcl::SYMS_ID::SYM_OP_EQUAL;
    if (sym == lcl::SYMS::SYM_OP_NOT_EQUAL) return lcl::SYMS_ID::SYM_OP_NOT_EQUAL;
    if (sym == lcl::SYMS::SYM_OP_AND) return lcl::SYMS_ID::SYM_OP_AND;
    if (sym == lcl::SYMS::SYM_OP_OR) return lcl::SYMS_ID::SYM_OP_OR;
    if (sym == lcl::SYMS::SYM_OP_XOR) return lcl::SYMS_ID::SYM_OP_XOR;
    if (sym == lcl::SYMS::SYM_OP_NOT) return lcl::SYMS_ID::SYM_OP_NOT;
    if (sym == lcl::SYMS::SYM_OP_IMPLICATION) return lcl::SYMS_ID::SYM_OP_IMPLICATION;
    if (isdigit(sym)) return lcl::SYMS_ID::SYM_DIGIT;
    lcl::printErrorMsg("Unknown character passed into symCharToId - " + sym);
    exit(1);
}

std::string lcl::pretifyString(std::string string) {
    string = padOperators(string);
    std::string newString;
    for (std::size_t i = 0;i < string.length();i++) {
        if (string[i] == lcl::SYMS::SYM_OP_LESS_EQUAL) {
            newString.push_back('<');
            newString.push_back('=');
        }
        else if (string[i] == lcl::SYMS::SYM_OP_MORE_EQUAL) {
            newString.push_back('>');
            newString.push_back('=');
        }
        else if (string[i] == lcl::SYMS::SYM_OP_EQUAL) {
            newString.push_back('=');
            newString.push_back('=');
        }
        else if (string[i] == lcl::SYMS::SYM_OP_NOT_EQUAL) {
            newString.push_back('!');
            newString.push_back('=');
        }
        else if (string[i] == lcl::SYMS::SYM_OP_AND) {
            newString.push_back('&');
            newString.push_back('&');
        }
        else if (string[i] == lcl::SYMS::SYM_OP_OR) {
            newString.push_back('|');
            newString.push_back('|');
        }
        else if (string[i] == lcl::SYMS::SYM_OP_IMPLICATION) {
            newString.push_back('-');
            newString.push_back('>');
        }
        else {
            newString.push_back(string[i]);
        }
    }
    return newString;
}

void lcl::checkString(std::string string) {
    for (std::size_t i = 1;i < string.length();i++) {
        unsigned char lsym = symCharToId(string[i - 1]);
        unsigned char rsym = symCharToId(string[i]);

        bool lbool = (lsym <= 1);
        bool lcomp = (lsym >= 2) && (lsym <= 7);
        bool lop = (lsym >= 8) && (lsym <= 10);
        bool lnot = (lsym == 12);
        bool ldigit = (lsym == 13);

        bool rbool = (rsym <= 1);
        bool rcomp = (rsym >= 2) && (rsym <= 7);
        bool rop = (rsym >= 8) && (rsym <= 10);
        bool rnot = (rsym == 12);
        bool rdigit = (rsym == 13);

        if (lcomp && rcomp) {
            printErrorMsg("Bad input encountered!");
            std::string pString = pretifyString(string);
            for (unsigned int _ = 0;_ < pString.length();_++) std::cout << "-";
            std::cout << std::endl << pString << std::endl;

            std::size_t offset = 0;
            for (int j = 0;j < i;j++) {
                if (((symCharToId(string[j]) >= 2 && symCharToId(string[j]) <= 9) || (symCharToId(string[j]) == 11)) && symCharToId(string[j]) != 2 && symCharToId(string[j]) != 4) {
                    offset += 3;
                }
                else {
                    offset += 2;
                }
            }
            for (unsigned int _ = 0;_ < offset;_++) std::cout << " ";
            std::cout << ANSI_COLOR_BRIGHT_RED << "^" << ANSI_COLOR_RESET << std::endl;

            for (unsigned int _ = 0;_ < pString.length();_++) std::cout << "-";
            std::cout << ANSI_COLOR_RESET << std::endl;
            exit(1);
        }
    }
}

std::string lcl::padOperators(std::string string) {
    std::size_t string_length = string.length();
    unsigned int newLen = string.length() + 1;
    for (unsigned int i = 0;i < string_length;i++) {
        if (isdigit(string[i])) continue;
        newLen += 2;
    }
    char* newString = new char[newLen];
    int index = 0;
    for (unsigned int i = 0;i < string_length;i++) {
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

void lcl::populateOpPriorities(char* priorities) {
    priorities[lcl::SYMS::SYM_OP_LESS] = 1;
    priorities[lcl::SYMS::SYM_OP_LESS_EQUAL] = 1;
    priorities[lcl::SYMS::SYM_OP_MORE] = 1;
    priorities[lcl::SYMS::SYM_OP_MORE_EQUAL] = 1;
    priorities[lcl::SYMS::SYM_OP_EQUAL] = 1;
    priorities[lcl::SYMS::SYM_OP_NOT_EQUAL] = 1;
    priorities[lcl::SYMS::SYM_OP_AND] = 9;
    priorities[lcl::SYMS::SYM_OP_OR] = 8;
    priorities[lcl::SYMS::SYM_OP_XOR] = 8;
    priorities[lcl::SYMS::SYM_OP_NOT] = 10;
    priorities[lcl::SYMS::SYM_OP_IMPLICATION] = 7;
}