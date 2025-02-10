#include <logiccalclib.hpp>
#include <tetostack.hpp>

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
    if (sym == '(') return lcl::SYMS_ID::SYM_BRACKET_OPEN;
    if (sym == ')') return lcl::SYMS_ID::SYM_BRACKET_CLOSE;
    lcl::printErrorMsg("Unknown character passed into symCharToId - " + sym);
    exit(1);
}

unsigned char lcl::symIdToChar(unsigned char id) {
    if (id == lcl::SYMS_ID::SYM_TRUE) return lcl::SYMS::SYM_TRUE;
    if (id == lcl::SYMS_ID::SYM_FALSE) return lcl::SYMS::SYM_FALSE;
    if (id == lcl::SYMS_ID::SYM_OP_LESS) return lcl::SYMS::SYM_OP_LESS;
    if (id == lcl::SYMS_ID::SYM_OP_LESS_EQUAL) return lcl::SYMS::SYM_OP_LESS_EQUAL;
    if (id == lcl::SYMS_ID::SYM_OP_MORE) return lcl::SYMS::SYM_OP_MORE;
    if (id == lcl::SYMS_ID::SYM_OP_MORE_EQUAL) return lcl::SYMS::SYM_OP_MORE_EQUAL;
    if (id == lcl::SYMS_ID::SYM_OP_EQUAL) return lcl::SYMS::SYM_OP_EQUAL;
    if (id == lcl::SYMS_ID::SYM_OP_NOT_EQUAL) return lcl::SYMS::SYM_OP_NOT_EQUAL;
    if (id == lcl::SYMS_ID::SYM_OP_AND) return lcl::SYMS::SYM_OP_AND;
    if (id == lcl::SYMS_ID::SYM_OP_OR) return lcl::SYMS::SYM_OP_OR;
    if (id == lcl::SYMS_ID::SYM_OP_XOR) return lcl::SYMS::SYM_OP_XOR;
    if (id == lcl::SYMS_ID::SYM_OP_NOT) return lcl::SYMS::SYM_OP_NOT;
    if (id == lcl::SYMS_ID::SYM_OP_IMPLICATION) return lcl::SYMS::SYM_OP_IMPLICATION;
    if (id == lcl::SYMS_ID::SYM_BRACKET_OPEN) return '(';
    if (id == lcl::SYMS_ID::SYM_BRACKET_CLOSE) return ')';
    lcl::printErrorMsg("Unknown id passed into symIdToSym - " + id);
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
    int bracket_balance = 0;
    if (string[0] == '(') bracket_balance++;
    if (string[0] == ')') {
        printErrorMsg("Bad input encountered!");
        std::string pString = pretifyString(string);
        for (unsigned int _ = 0;_ < pString.length();_++) std::cout << "-";
        std::cout << std::endl << pString << std::endl;
        std::cout << ANSI_COLOR_BRIGHT_RED << "^" << ANSI_COLOR_RESET << std::endl;
        for (unsigned int _ = 0;_ < pString.length();_++) std::cout << "-";
        std::cout << ANSI_COLOR_RESET << std::endl;
        exit(1);
    }

    for (std::size_t i = 1;i < string.length();i++) {
        unsigned char lsym = symCharToId(string[i - 1]);
        unsigned char rsym = symCharToId(string[i]);

        if (string[i] == '(') bracket_balance++;
        if (string[i] == ')') bracket_balance--;

        bool lbool = (lsym <= lcl::SYMS_ID::SYM_FALSE);
        bool lcomp = (lsym >= lcl::SYMS_ID::SYM_OP_LESS) && (lsym <= lcl::SYMS_ID::SYM_OP_NOT_EQUAL);
        bool lop = (lsym >= lcl::SYMS_ID::SYM_OP_AND) && (lsym <= lcl::SYMS_ID::SYM_OP_IMPLICATION);
        bool lnot = (lsym == lcl::SYMS_ID::SYM_OP_NOT);
        bool ldigit = (lsym == lcl::SYMS_ID::SYM_DIGIT);
        bool lbracketopen = (lsym == lcl::SYMS_ID::SYM_BRACKET_OPEN);
        bool lbracketclose = (lsym == lcl::SYMS_ID::SYM_BRACKET_CLOSE);

        bool rbool = (rsym <= lcl::SYMS_ID::SYM_FALSE);
        bool rcomp = (rsym >= lcl::SYMS_ID::SYM_OP_LESS) && (rsym <= lcl::SYMS_ID::SYM_OP_NOT_EQUAL);
        bool rop = (rsym >= lcl::SYMS_ID::SYM_OP_AND) && (rsym <= lcl::SYMS_ID::SYM_OP_IMPLICATION);
        bool rnot = (rsym == lcl::SYMS_ID::SYM_OP_NOT);
        bool rdigit = (rsym == lcl::SYMS_ID::SYM_DIGIT);
        bool rbracketopen = (rsym == lcl::SYMS_ID::SYM_BRACKET_OPEN);
        bool rbracketclose = (rsym == lcl::SYMS_ID::SYM_BRACKET_CLOSE);

        if ((lcomp && rcomp) || (ldigit && rnot) || (bracket_balance < 0) || (ldigit && rbracketopen) || (lbracketclose && rdigit) || ((lop || lcomp || lnot) && rbracketclose)) {
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

    if (bracket_balance != 0) {
        printErrorMsg("Reached the end of string, but not all brackets were closed!");
        std::string pString = pretifyString(string);
        for (unsigned int _ = 0;_ < pString.length();_++) std::cout << "-";
        std::cout << std::endl << pString << std::endl;

        std::size_t offset = pString.length() - 1;
        for (unsigned int _ = 0;_ < offset;_++) std::cout << " ";
        std::cout << ANSI_COLOR_BRIGHT_RED << "^" << ANSI_COLOR_RESET << std::endl;

        for (unsigned int _ = 0;_ < pString.length();_++) std::cout << "-";
        std::cout << ANSI_COLOR_RESET << std::endl;
        exit(1);
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

std::string lcl::convertToPostfix(std::string string) {
    std::string result;
    Teto::TetoStack<int> stack;
    char OP_PRIORITIES[lcl::SYMS_ID::SYM_DIGIT];

    populateOpPriorities(OP_PRIORITIES);

    int digitBuffer = 0;
    for (std::size_t i = 0;i < string.length();i++) {
        if (string[i] == ' ') {
            if (digitBuffer != 0) {
                result.append(std::to_string(digitBuffer));
                digitBuffer = 0;
                result.push_back(' ');
            }

            continue;
        }

        unsigned char symId = symCharToId(string[i]);

        bool sbool = (symId <= lcl::SYMS_ID::SYM_FALSE);
        bool scomp = (symId >= lcl::SYMS_ID::SYM_OP_LESS) && (symId <= lcl::SYMS_ID::SYM_OP_NOT_EQUAL);
        bool sop = (symId >= lcl::SYMS_ID::SYM_OP_AND) && (symId <= lcl::SYMS_ID::SYM_OP_IMPLICATION);
        bool snot = (symId == lcl::SYMS_ID::SYM_OP_NOT);
        bool sdigit = (symId == lcl::SYMS_ID::SYM_DIGIT);
        bool sbracketopen = (symId == lcl::SYMS_ID::SYM_BRACKET_OPEN);
        bool sbracketclose = (symId == lcl::SYMS_ID::SYM_BRACKET_CLOSE);

        if (sdigit) {
            digitBuffer *= 10;
            digitBuffer += string[i] - '0';
        }
        else if (scomp || sop) {
            while (!stack.isEmpty() && OP_PRIORITIES[stack.getTop()] > OP_PRIORITIES[symId]) {
                result.push_back(symIdToChar(stack.pop()));
                result.push_back(' ');
            }
            stack.push(symId);
        }
        else if (sbracketopen) {
            stack.push(symId);
        }
        else if (sbracketclose) {
            while (!stack.isEmpty() && stack.getTop() != lcl::SYMS_ID::SYM_BRACKET_OPEN) {
                result.push_back(symIdToChar(stack.pop()));
                result.push_back(' ');
            }
            stack.pop();
        }
        else if (sbool) {
            if (symId == lcl::SYMS_ID::SYM_TRUE) {
                result.push_back('T');
                result.push_back(' ');
            }
            else if (symId == lcl::SYMS_ID::SYM_FALSE) {
                result.push_back('F');
                result.push_back(' ');
            }
        }
    }

    if (digitBuffer != 0) {
        result.append(std::to_string(digitBuffer));
        digitBuffer = 0;
        result.push_back(' ');
    }

    while (!stack.isEmpty()) {
        result.push_back(symIdToChar(stack.pop()));
        result.push_back(' ');
    }

    return result;
}

bool lcl::calculatePostfix(std::string string) {
    Teto::TetoStack<int> stack;
    char OP_PRIORITIES[lcl::SYMS_ID::SYM_DIGIT];

    populateOpPriorities(OP_PRIORITIES);

    int digitBuffer = 0;
    for (std::size_t i = 0;i < string.length();i++) {
        if (string[i] == ' ') {
            if (digitBuffer != 0) {
                stack.push(digitBuffer);
                digitBuffer = 0;
            }

            continue;
        }

        unsigned char symId = symCharToId(string[i]);

        bool sbool = (symId <= lcl::SYMS_ID::SYM_FALSE);
        bool scomp = (symId >= lcl::SYMS_ID::SYM_OP_LESS) && (symId <= lcl::SYMS_ID::SYM_OP_NOT_EQUAL);
        bool sop = (symId >= lcl::SYMS_ID::SYM_OP_AND) && (symId <= lcl::SYMS_ID::SYM_OP_IMPLICATION);
        bool snot = (symId == lcl::SYMS_ID::SYM_OP_NOT);
        bool sdigit = (symId == lcl::SYMS_ID::SYM_DIGIT);
        bool sbracketopen = (symId == lcl::SYMS_ID::SYM_BRACKET_OPEN);
        bool sbracketclose = (symId == lcl::SYMS_ID::SYM_BRACKET_CLOSE);

        if (sdigit) {
            digitBuffer *= 10;
            digitBuffer += string[i] - '0';
        }
        else if (sbool) {
            if (symId == lcl::SYMS_ID::SYM_TRUE) {
                stack.push(1);
            }
            else if (symId == lcl::SYMS_ID::SYM_FALSE) {
                stack.push(0);
            }
        }
        else {
            int right = stack.pop();
            int left = stack.pop();
            int result = 0;

            stack.push(result);
        }
    }

    int result = stack.pop();

    std::cout << result << std::endl;;

    return static_cast<bool>(result);
}

void lcl::populateOpPriorities(char* priorities) {
    priorities[lcl::SYMS_ID::SYM_OP_LESS] = 11;
    priorities[lcl::SYMS_ID::SYM_OP_LESS_EQUAL] = 11;
    priorities[lcl::SYMS_ID::SYM_OP_MORE] = 11;
    priorities[lcl::SYMS_ID::SYM_OP_MORE_EQUAL] = 11;
    priorities[lcl::SYMS_ID::SYM_OP_EQUAL] = 11;
    priorities[lcl::SYMS_ID::SYM_OP_NOT_EQUAL] = 11;
    priorities[lcl::SYMS_ID::SYM_OP_AND] = 9;
    priorities[lcl::SYMS_ID::SYM_OP_OR] = 8;
    priorities[lcl::SYMS_ID::SYM_OP_XOR] = 8;
    priorities[lcl::SYMS_ID::SYM_OP_NOT] = 10;
    priorities[lcl::SYMS_ID::SYM_OP_IMPLICATION] = 7;
}