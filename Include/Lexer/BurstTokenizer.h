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

struct burstTokenizer;
struct burstTokenizer
{
    FILE *pFile;
    
    BurstTokenArray *pTokens;
};
typedef struct burstTokenizer BurstTokenizer;

int tokenizer_create
(
    FILE *pFile,                 // IN
    BurstTokenizer **ppTokenizer // OUT
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