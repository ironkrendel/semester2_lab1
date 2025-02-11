#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <optional>
#include <vector>

#include <tetostack.hpp>
#include <colors.hpp>

namespace lcl {
    namespace SYMS {
        enum : unsigned char {
            SYM_TRUE =           'T',
            SYM_FALSE =          'F',
            SYM_OP_LESS =        '<',  // 91
            SYM_OP_LESS_EQUAL =  '[',  // 62
            SYM_OP_MORE =        '>',  // 93
            SYM_OP_MORE_EQUAL =  ']',  // 61
            SYM_OP_EQUAL =       '=',  // 78
            SYM_OP_NOT_EQUAL =   'N',  // 38
            SYM_OP_AND =         '&',  // 124
            SYM_OP_OR =          '|',  // 94
            SYM_OP_XOR =         '^',  // 33
            SYM_OP_IMPLICATION = 'I',  // 73
            SYM_OP_NOT =         '!',  // 33
            SYM_BRACKET_OPEN =   '(',
            SYM_BRACKET_CLOSE =  ')',
        };
    };

    namespace SYMS_ID {
        enum : unsigned char {
            SYM_TRUE,
            SYM_FALSE,
            SYM_OP_LESS,
            SYM_OP_LESS_EQUAL,
            SYM_OP_MORE,
            SYM_OP_MORE_EQUAL,
            SYM_OP_EQUAL,
            SYM_OP_NOT_EQUAL,
            SYM_OP_AND,
            SYM_OP_OR,
            SYM_OP_XOR,
            SYM_OP_IMPLICATION,
            SYM_OP_NOT,
            SYM_DIGIT,
            SYM_BRACKET_OPEN,
            SYM_BRACKET_CLOSE,
        };
    };

    void printErrorMsg(const char* message);

    void printErrorMsg(std::string message);

    void printErrorPlace(std::string message, std::size_t offset);

    void printErrorPlace(std::string message, std::vector<std::size_t> offsets);

    unsigned char symCharToId(unsigned char sym);

    unsigned char symIdToChar(unsigned char id);

    Teto::TetoStack convertToPostfix(std::string str);

    int calculatePostfix(Teto::TetoStack& postfix);

    void checkString(std::string str);

    void populateOpPriorities(char* priorities);
};
// #define SYM_TRUE           'T'
// #define SYM_FALSE          'F'
// #define SYM_OP_LESS        '<'  // 91
// #define SYM_OP_LESS_EQUAL  '['  // 62
// #define SYM_OP_MORE        '>'  // 93
// #define SYM_OP_MORE_EQUAL  ']'  // 61
// #define SYM_OP_EQUAL       '='  // 78
// #define SYM_OP_NOT_EQUAL   'N'  // 38
// #define SYM_OP_AND         '&'  // 124
// #define SYM_OP_OR          '|'  // 94
// #define SYM_OP_XOR         '^'  // 33
// #define SYM_OP_NOT         '!'  // 33
// #define SYM_OP_IMPLICATION 'I'  // 73

// #define ANSI_COLOR_RED            "\x1b[31m"
// #define ANSI_COLOR_GREEN          "\x1b[32m"
// #define ANSI_COLOR_YELLOW         "\x1b[33m"
// #define ANSI_COLOR_BLUE           "\x1b[34m"
// #define ANSI_COLOR_MAGENTA        "\x1b[35m"
// #define ANSI_COLOR_CYAN           "\x1b[36m"
// #define ANSI_COLOR_BRIGHT_RED     "\x1b[91m"
// #define ANSI_COLOR_BRIGHT_GREEN   "\x1b[92m"
// #define ANSI_COLOR_BRIGHT_YELLOW  "\x1b[93m"
// #define ANSI_COLOR_BRIGHT_BLUE    "\x1b[94m"
// #define ANSI_COLOR_BRIGHT_MAGENTA "\x1b[95m"
// #define ANSI_COLOR_BRIGHT_CYAN    "\x1b[96m"
// #define ANSI_COLOR_RESET          "\x1b[0m"