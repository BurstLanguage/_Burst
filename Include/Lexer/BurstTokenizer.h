//
// Burst
// Include/Lexer/BurstTokenizer.h
//
#ifndef __BURST_TOKENIZER_H__
#define __BURST_TOKENIZER_H__

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "BurstErrorCodes.h"
#include "BurstErrorMessages.h"

#include "Token/BurstToken.h"
#include "Token/BurstTokenRegistry.h"

#define BURST_TOKENIZER_OK  0x00
#define BURST_TOKENIZER_ERR 0x01

#define BURST_UNKNOWN_TOKEN     0x00
#define BURST_WHITESPACE_TOKEN  0x01
#define BURST_LETTER_TOKEN      0x02
#define BURST_NUMBER_TOKEN      0x03
#define BURST_EQUALS_TOKEN      0x04
#define BURST_SEMICOLON_TOKEN   0x05
#define BURST_ADD_TOKEN         0x06
#define BURST_SUBTRACT_TOKEN    0x07
#define BURST_MULTIPLY_TOKEN    0x08
#define BURST_DIVIDE_TOKEN      0x09

struct burstTokenizer;
struct burstTokenizer
{
    FILE *pFile;
    
    BurstTokenArray *pTokens;
    BurstTokenRegistry *pTokenRegistry;
};
typedef struct burstTokenizer BurstTokenizer;

int tokenizer_create
(
    FILE *pFile,                 // IN
    BurstTokenizer **ppTokenizer // OUT
);

int tokenizer_setup
(
    BurstTokenizer *pTokenizer // IN
);

BurstToken *tokenizer_getNext
(
    BurstTokenizer *pTokenizer // IN
);

int tokenizer_run
(
    BurstTokenizer *pTokenizer // IN
);

int tokenizer_destroy
(
    BurstTokenizer *pTokenizer // IN
);

#endif