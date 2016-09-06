//
// Burst
// Include/Frontend/Lexer/BurstTokenizer.h
//
#ifndef __BURST_TOKENIZER_H__
#define __BURST_TOKENIZER_H__

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "BurstCommons.h"
#include "BurstErrorCodes.h"
#include "BurstErrorMessages.h"

#include "Token/BurstToken.h"
#include "Token/BurstTokenRegistry.h"

struct burstTokenizerFlags;
typedef struct burstTokenizerFlags
{
    bool bInComment;
} BurstTokenizerFlags;

struct burstTokenizer;
typedef struct burstTokenizer
{
    FILE *pFile;
    
    BurstTokenArray *pTokens;
    BurstTokenRegistry *pTokenRegistry;
    
    BurstTokenizerFlags *pFlags;
} BurstTokenizer;

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