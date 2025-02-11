// #include <tetostack.hpp>

#include <logiccalclib.hpp>

// #define DEBUG

typedef Teto::TetoElement Elem;

void lcl::printErrorMsg(std::string msg) {
    std::cout << ANSI_COLOR_BRIGHT_RED << msg << ANSI_COLOR_RESET << std::endl;
}

void lcl::printErrorMsg(const char* msg) {
    std::cout << ANSI_COLOR_BRIGHT_RED << msg << ANSI_COLOR_RESET << std::endl;
}

void lcl::printErrorPlace(std::string message, std::size_t offset) {
    for (std::size_t _ = 0;_ < message.size();_++) std::cout << '-';
    std::cout << std::endl;
    std::cout << message << std::endl;
    for (std::size_t _ = 0;_ < offset;_++) std::cout << ' ';
    std::cout << ANSI_COLOR_RED "^" ANSI_COLOR_RESET << std::endl;
    for (std::size_t _ = 0;_ < message.size();_++) std::cout << '-';
    std::cout << std::endl;
}

void lcl::printErrorPlace(std::string message, std::vector<std::size_t> offsets) {
    for (std::size_t _ = 0;_ < message.size();_++) std::cout << '-';
    std::cout << std::endl;
    std::cout << message << std::endl;
    
    std::size_t index = 0;
    for (std::size_t i = 0;i < message.size() && index < offsets.size();i++) {
        if (i == offsets[index]) {
            std::cout << ANSI_COLOR_RED "^" ANSI_COLOR_RESET;
            index++;
        }
        else {
            std::cout << ' ';
        }
    }
    std::cout << std::endl;

    for (std::size_t _ = 0;_ < message.size();_++) std::cout << '-';
    std::cout << std::endl;
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
    // exit(1);
    throw std::runtime_error("");
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
    // exit(1);
    throw std::runtime_error("");
}

Teto::TetoStack lcl::convertToPostfix(std::string str) {
    Teto::TetoStack opStack;
    Teto::TetoStack result;
    std::optional<int> digitBuffer;
    int digitBufferModifier = 1;
    int OP_PRIORITIES[1000];
    populateOpPriorities(OP_PRIORITIES);

    for (std::size_t i = 0;i < str.length();i++) {
        #ifdef DEBUG
        DEBUG_CONVERSION_STACK_PRINT(result, opStack);
        #endif

        if (str[i] == '-' && str[i + 1] != '>') {
            digitBufferModifier = -1;
        }
        else if (isdigit(str[i])) {
            if (digitBuffer.has_value()) {
                digitBuffer = digitBuffer.value() * 10;
                digitBuffer = digitBuffer.value() + (str[i] - '0');
            }
            else {
                digitBuffer = str[i] - '0';
            }
        }
        else {
            if (digitBuffer.has_value()) {
                Elem pushVal;
                pushVal.isOp = false;
                pushVal.data.value = digitBuffer.value() * digitBufferModifier;
                digitBufferModifier = 1;
                digitBuffer.reset();
                result.push(pushVal);
            }

            #ifdef DEBUG
            DEBUG_CONVERSION_STACK_PRINT(result, opStack);
            #endif
            
            Elem pushVal;
            pushVal.isOp = true;
            std::optional<unsigned char> op;
            if (i + 4 < str.length()) 
            {
                char strSlice[5];
                memcpy(strSlice, str.data() + i * sizeof(char), sizeof(char) * 5);
                if (strcasecmp(strSlice, "false") == 0) {
                    Elem _pushVal;
                    _pushVal.isOp = false;
                    if (digitBufferModifier == -1) {
                        _pushVal.data.value = 1;
                    }
                    else {
                        _pushVal.data.value = 0;
                    }
                    digitBufferModifier = 1;
                    result.push(_pushVal);
                    i += 4;
                    continue;
                }
            }
            if (i + 3 < str.length()) {
                char strSlice[4];
                memcpy(strSlice, str.data() + i * sizeof(char), sizeof(char) * 4);
                if (strcasecmp(strSlice, "true") == 0) {
                    Elem _pushVal;
                    _pushVal.isOp = false;
                    if (digitBufferModifier == -1) {
                        _pushVal.data.value = 0;
                    }
                    else {
                        _pushVal.data.value = 1;
                    }
                    digitBufferModifier = 1;
                    result.push(_pushVal);
                    i += 3;
                    continue;
                }
            }
            if (i + 1 < str.length()) {
                if (str[i] == '<' && str[i + 1] == '=') {
                    // pushVal.data.op = lcl::SYMS::SYM_OP_LESS_EQUAL;
                    op = lcl::SYMS::SYM_OP_LESS_EQUAL;
                    i++;
                }
                if (str[i] == '>' && str[i + 1] == '=') {
                    pushVal.data.op = lcl::SYMS::SYM_OP_MORE_EQUAL;
                    // op = lcl::SYMS::SYM_OP_MORE_EQUAL;
                    i++;
                }
                if (str[i] == '=' && str[i + 1] == '=') {
                    // pushVal.data.op = lcl::SYMS::SYM_OP_EQUAL;
                    op = lcl::SYMS::SYM_OP_EQUAL;
                    i++;
                }
                if (str[i] == '!' && str[i + 1] == '=') {
                    // pushVal.data.op = lcl::SYMS::SYM_OP_EQUAL;
                    op = lcl::SYMS::SYM_OP_NOT_EQUAL;
                    i++;
                }
                if (str[i] == '&' && str[i + 1] == '&') {
                    // pushVal.data.op = lcl::SYMS::SYM_OP_AND;
                    op = lcl::SYMS::SYM_OP_AND;
                    i++;
                }
                if (str[i] == '|' && str[i + 1] == '|') {
                    // pushVal.data.op = lcl::SYMS::SYM_OP_OR;
                    op = lcl::SYMS::SYM_OP_OR;
                    i++;
                }
                if (str[i] == '-' && str[i + 1] == '>') {
                    // pushVal.data.op = lcl::SYMS::SYM_OP_IMPLICATION;
                    op = lcl::SYMS::SYM_OP_IMPLICATION;
                    i++;
                }
            }
            if (str[i] == 'T' || str[i] == 't') {
                Elem _pushVal;
                _pushVal.isOp = false;
                if (digitBufferModifier == -1) {
                    _pushVal.data.value = 0;
                }
                else {
                    _pushVal.data.value = 1;
                }
                digitBufferModifier = 1;
                result.push(_pushVal);
                continue;
            }
            else if (str[i] == 'F' || str[i] == 'f') {
                Elem _pushVal;
                _pushVal.isOp = false;
                _pushVal.data.value = 0;
                if (digitBufferModifier == -1) {
                    _pushVal.data.value = 1;
                }
                else {
                    _pushVal.data.value = 0;
                }
                digitBufferModifier = 1;
                result.push(_pushVal);
                continue;
            }
            else if (str[i] == '<') {
                // pushVal.data.op = lcl::SYMS::SYM_OP_LESS;
                op = lcl::SYMS::SYM_OP_LESS;
            }
            else if (str[i] == '>' && !op.has_value()) {
                // pushVal.data.op = lcl::SYMS::SYM_OP_MORE;
                op = lcl::SYMS::SYM_OP_MORE;
            }
            else if (str[i] == '^') {
                // pushVal.data.op = lcl::SYMS::SYM_OP_XOR;
                op = lcl::SYMS::SYM_OP_XOR;
            }
            else if (str[i] == '!') {
                // pushVal.data.op = lcl::SYMS::SYM_OP_XOR;
                op = lcl::SYMS::SYM_OP_NOT;
            }
            else if (str[i] == '(') {
                // pushVal.data.op = lcl::SYMS::SYM_OP_XOR;
                op = lcl::SYMS::SYM_BRACKET_OPEN;
            }
            else if (str[i] == ')') {
                // pushVal.data.op = lcl::SYMS::SYM_OP_XOR;
                // op = lcl::SYMS::SYM_BRACKET_CLOSE;
                while (opStack.getTop().data.op != '(') {
                    result.push(opStack.pop());
                }
                opStack.pop();
            }
            if (op.has_value()) {
                pushVal.data.op = op.value();
                while (!opStack.isEmpty() && (OP_PRIORITIES[opStack.getTop().data.op] > OP_PRIORITIES[op.value()])) {
                    if (op == lcl::SYMS::SYM_BRACKET_OPEN) break;
                    #ifdef DEBUG
                        std::cout << opStack.getTop().data.op << " " << op.value() << std::endl;
                        std::cout << OP_PRIORITIES[opStack.getTop().data.op] << " " << OP_PRIORITIES[op.value()] << std::endl;
                    #endif
                    result.push(opStack.pop());
                }
                opStack.push(pushVal);
            }
        }
    }

    if (digitBuffer.has_value()) {
        Elem pushVal;
        pushVal.isOp = false;
        pushVal.data.value = digitBuffer.value() * digitBufferModifier;
        result.push(pushVal);
    }

    while (!opStack.isEmpty()) {
        result.push(opStack.pop());
    }

    #ifdef DEBUG
    DEBUG_CONVERSION_STACK_PRINT(result, opStack);
    #endif

    return result;
}

int lcl::calculatePostfix(Teto::TetoStack& postfix) {
    Teto::TetoStack reversedPostfix;
    Teto::TetoStack result;

    std::size_t index = 0;

    while (!postfix.isEmpty()) {
        reversedPostfix.push(postfix.pop());
    }

    while (!reversedPostfix.isEmpty()) {
        Elem e = reversedPostfix.pop();
        if (e.isOp) {
            index+=2;
            unsigned char op = e.data.op;

            if (op == lcl::SYMS::SYM_OP_NOT) {
                Elem pushVal;
                pushVal.isOp = false;
                pushVal.data.value = !static_cast<bool>(result.pop().data.value);
                result.push(pushVal);
            }
            else {
                if (result.getElementCount() < 2) {
                    // for (std::size_t _ = 0;_ < index - 2;_++) std::cout << ' ';
                    // std::cout << ANSI_COLOR_RED "^" ANSI_COLOR_RESET << std::endl;
                    printErrorMsg("Error! Not enough arguments were provided for given operation!");
                    throw std::runtime_error("");
                }

                int right = result.pop().data.value;
                int left = result.pop().data.value;

                Elem pushVal;
                pushVal.isOp = false;

                if (op == lcl::SYMS::SYM_OP_LESS) {
                    pushVal.data.value = static_cast<int>(left < right);
                }
                else if (op == lcl::SYMS::SYM_OP_LESS_EQUAL) {
                    pushVal.data.value = static_cast<int>(left <= right);
                }
                else if (op == lcl::SYMS::SYM_OP_MORE) {
                    pushVal.data.value = static_cast<int>(left > right);
                }
                else if (op == lcl::SYMS::SYM_OP_MORE_EQUAL) {
                    pushVal.data.value = static_cast<int>(left >= right);
                }
                else if (op == lcl::SYMS::SYM_OP_EQUAL) {
                    pushVal.data.value = static_cast<int>(left == right);
                }
                else if (op == lcl::SYMS::SYM_OP_NOT_EQUAL) {
                    pushVal.data.value = static_cast<int>(left != right);
                }
                else if (op == lcl::SYMS::SYM_OP_AND) {
                    pushVal.data.value = static_cast<int>(static_cast<bool>(left) && static_cast<bool>(right));
                }
                else if (op == lcl::SYMS::SYM_OP_OR) {
                    pushVal.data.value = static_cast<int>(static_cast<bool>(left) || static_cast<bool>(right));
                }
                else if (op == lcl::SYMS::SYM_OP_XOR) {
                    pushVal.data.value = static_cast<int>(static_cast<bool>(left) != static_cast<bool>(right));
                }
                else if (op == lcl::SYMS::SYM_OP_IMPLICATION) {
                    pushVal.data.value = static_cast<int>(!static_cast<bool>(left) || static_cast<bool>(right));
                }

                result.push(pushVal);
            }
        }
        else {
            index += std::to_string(e.data.value).length() + 1;
            result.push(e);
        }
    }

    return result.pop().data.value;
}

void lcl::checkString(std::string str) {
    int bracketVal = 0;
    std::vector<std::size_t> bracketOpenings;
    for (std::size_t i = 0;i < str.length();i++) {
        if (str[i] == '(') {
            bracketVal++;
            bracketOpenings.push_back(i);
        }
        if (str[i] == ')') {
            bracketVal--;
            bracketOpenings.pop_back();
        }
        if (bracketVal < 0) {
            printErrorMsg("Stray bracket!");
            printErrorPlace(str, i);
            throw std::runtime_error("");
        }
    }
    if (bracketVal != 0) {
        printErrorMsg(std::to_string(bracketVal) + " bracket(s) was(were) unclosed!");
        printErrorPlace(str, bracketOpenings);
        throw std::runtime_error("");
    }
}

void lcl::populateOpPriorities(int* priorities) {
    priorities[lcl::SYMS::SYM_OP_LESS] = 11;
    priorities[lcl::SYMS::SYM_OP_LESS_EQUAL] = 11;
    priorities[lcl::SYMS::SYM_OP_MORE] = 11;
    priorities[lcl::SYMS::SYM_OP_MORE_EQUAL] = 11;
    priorities[lcl::SYMS::SYM_OP_EQUAL] = 11;
    priorities[lcl::SYMS::SYM_OP_NOT_EQUAL] = 11;
    priorities[lcl::SYMS::SYM_OP_AND] = 9;
    priorities[lcl::SYMS::SYM_OP_OR] = 8;
    priorities[lcl::SYMS::SYM_OP_XOR] = 8;
    priorities[lcl::SYMS::SYM_OP_NOT] = 12;
    priorities[lcl::SYMS::SYM_OP_IMPLICATION] = 7;
    priorities[lcl::SYMS::SYM_BRACKET_OPEN] = 0;
}