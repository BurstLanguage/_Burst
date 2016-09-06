//
// Burst
// Include/Frontend/Lexer/Token/BurstToken.h
//
#ifndef __BURST_TOKEN_H__
#define __BURST_TOKEN_H__

#include <stdio.h>
#include <stdlib.h>

#include "BurstCommons.h"
#include "BurstErrorCodes.h"
#include "BurstErrorMessages.h"

#define BURST_UNKNOWN_TOKEN     0x00
#define BURST_WHITESPACE_TOKEN  0x01
#define BURST_LETTER_TOKEN      0x02
#define BURST_NUMBER_TOKEN      0x03
#define BURST_KEYWORD_TOKEN     0x04
#define BURST_IDENTIFIER_TOKEN  0x05
#define BURST_EQUALS_TOKEN      0x06
#define BURST_SEMICOLON_TOKEN   0x07
#define BURST_ADD_TOKEN         0x08
#define BURST_SUBTRACT_TOKEN    0x09
#define BURST_MULTIPLY_TOKEN    0x0A
#define BURST_DIVIDE_TOKEN      0x0B
#define BURST_LBRACKET_TOKEN    0x0C
#define BURST_RBRACKET_TOKEN    0x0D
#define BURST_COMMENT_TOKEN     0x0E
#define BURST_COMMA_TOKEN       0x0F
#define BURST_LPAREN_TOKEN      0x10
#define BURST_RPAREN_TOKEN      0x11
#define BURST_LBRACE_TOKEN      0x12
#define BURST_RBRACE_TOKEN      0x13
#define BURST_TYPE_TOKEN        0x14
#define BURST_COLON_TOKEN       0x15

struct burstToken;
typedef struct burstToken
{
    int type;
    
    // TODO (Giga): Wrap these in a union to save space?
    char charValue;
    char *pStringValue;
} BurstToken;

int token_create
(
    int type,            // IN
    BurstToken **ppToken // OUT
);

int token_create_c
(
    char value,          // IN
    int type,            // IN
    BurstToken **ppToken // OUT
);

int token_create_s
(
    char *pValue,        // IN
    int type,            // IN
    BurstToken **ppToken // OUT
);

int token_destroy
(
    BurstToken *pToken // IN
);

struct burstTokenArray;
typedef struct burstTokenArray
{
    int tokenCount;
    BurstToken **ppTokens;
} BurstTokenArray;

int token_array_create
(
    BurstTokenArray **ppTokenArray // OUT
);

int token_array_add
(
    BurstToken *pToken,          // IN
    BurstTokenArray *pTokenArray // IN
);

BurstToken *token_array_at
(
    int index,                   // IN
    BurstTokenArray *pTokenArray // IN
);

int token_array_destroy
(
    BurstTokenArray *pTokenArray // IN
);

#endif