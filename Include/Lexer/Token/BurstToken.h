//
// Burst
// Include/Lexer/Token/BurstToken.h
//
#ifndef __BURST_TOKEN_H__
#define __BURST_TOKEN_H__

#include <stdio.h>
#include <stdlib.h>

#include "BurstErrorCodes.h"
#include "BurstErrorMessages.h"

#define BURST_UNKNOWN_TOKEN     0x00
#define BURST_WHITESPACE_TOKEN  0x01
#define BURST_LETTER_TOKEN      0x02
#define BURST_NUMBER_TOKEN      0x03
#define BURST_PUNCTUATION_TOKEN 0x04

struct burstToken;
struct burstToken
{
    int type;
    
    // TODO (Giga): Wrap these in a union to save space?
    char charValue;
    char *pStringValue;
};
typedef struct burstToken BurstToken;

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
struct burstTokenArray
{
    int tokenCount;
    BurstToken **ppTokens;
};
typedef struct burstTokenArray BurstTokenArray;

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