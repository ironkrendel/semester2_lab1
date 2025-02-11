// #include <tetostack.hpp>

#include <logiccalclib.hpp>

typedef Teto::TetoElement Elem;

void lcl::printErrorMsg(std::string msg) {
    std::cout << ANSI_COLOR_BRIGHT_RED << msg << ANSI_COLOR_RESET << std::endl;
}

void lcl::printErrorMsg(const char* msg) {
    std::cout << ANSI_COLOR_BRIGHT_RED << msg << ANSI_COLOR_RESET << std::endl;
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

    for (int i = 0;i < str.length();i++) {
        if (str[i] == '-' && isdigit(str[i + 1])) {
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
                Elem pushVal{false};
                pushVal.data.value = digitBuffer.value() * digitBufferModifier;
                digitBufferModifier = 1;
                digitBuffer.reset();
                result.push(pushVal);
            }
            
            Elem pushVal{true};
            if (i + 4 < str.length()) {

            }
            if (i + 3 < str.length()) {
                
            }
            if (i + 1 < str.length()) {
                if (str[i] == '<' && str[i + 1] == '=') {
                    pushVal.data.op = lcl::SYMS::SYM_OP_LESS_EQUAL;
                    i++;
                    continue;
                }
                if (str[i] == '>' && str[i + 1] == '=') {
                    pushVal.data.op = lcl::SYMS::SYM_OP_MORE_EQUAL;
                    i++;
                    continue;
                }
                if (str[i] == '=' && str[i + 1] == '=') {
                    pushVal.data.op = lcl::SYMS::SYM_OP_EQUAL;
                    i++;
                    continue;
                }
                if (str[i] == '!' && str[i + 1] == '=') {
                    pushVal.data.op = lcl::SYMS::SYM_OP_EQUAL;
                    i++;
                    continue;
                }
                if (str[i] == '&' && str[i + 1] == '&') {
                    pushVal.data.op = lcl::SYMS::SYM_OP_AND;
                    i++;
                    continue;
                }
                if (str[i] == '|' && str[i + 1] == '|') {
                    pushVal.data.op = lcl::SYMS::SYM_OP_OR;
                    i++;
                    continue;
                }
                if (str[i] == '-' && str[i + 1] == '>') {
                    pushVal.data.op = lcl::SYMS::SYM_OP_IMPLICATION;
                    i++;
                    continue;
                }
            }
            if (str[i] == 'T') {
                Elem _pushVal{false};
                _pushVal.data.value = 1;
                digitBufferModifier = 1;
                result.push(_pushVal);
            }
            else if (str[i] == 'F') {
                Elem _pushVal{false};
                _pushVal.data.value = 0;
                digitBufferModifier = 1;
                result.push(_pushVal);
            }
            else if (str[i] == '<') {
                pushVal.data.op = lcl::SYMS::SYM_OP_LESS;
            }
            else if (str[i] == '>') {
                pushVal.data.op = lcl::SYMS::SYM_OP_MORE;
            }
            opStack.push(pushVal);
        }
    }

    if (digitBuffer.has_value()) {
        Elem pushVal{false};
        pushVal.data.value = digitBuffer.value() * digitBufferModifier;
        result.push(pushVal);
    }

    return result;
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