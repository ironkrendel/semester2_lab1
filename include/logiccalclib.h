#pragma once

#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>

#define SYM_TRUE           'T'
#define SYM_FALSE          'F'
#define SYM_OP_LESS        '<'
#define SYM_OP_LESS_EQUAL  '['
#define SYM_OP_MORE        '>'
#define SYM_OP_MORE_EQUAL  ']'
#define SYM_OP_EQUAL       '='
#define SYM_OP_NOT_EQUAL   'N'
#define SYM_OP_AND         '&'
#define SYM_OP_OR          '|'
#define SYM_OP_XOR         '^'
#define SYM_OP_NOT         '!'
#define SYM_OP_IMPLICATION 'I'

#define ANSI_COLOR_RED            "\x1b[31m"
#define ANSI_COLOR_GREEN          "\x1b[32m"
#define ANSI_COLOR_YELLOW         "\x1b[33m"
#define ANSI_COLOR_BLUE           "\x1b[34m"
#define ANSI_COLOR_MAGENTA        "\x1b[35m"
#define ANSI_COLOR_CYAN           "\x1b[36m"
#define ANSI_COLOR_BRIGHT_RED     "\x1b[91m"
#define ANSI_COLOR_BRIGHT_GREEN   "\x1b[92m"
#define ANSI_COLOR_BRIGHT_YELLOW  "\x1b[93m"
#define ANSI_COLOR_BRIGHT_BLUE    "\x1b[94m"
#define ANSI_COLOR_BRIGHT_MAGENTA "\x1b[95m"
#define ANSI_COLOR_BRIGHT_CYAN    "\x1b[96m"
#define ANSI_COLOR_RESET          "\x1b[0m"

void printErrorMsg(char* msg);

char* prepareString(char* string);

char* padOperators(char* string);