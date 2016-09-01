//
// Burst
// Include/Frontend/Lexer/BurstLexer.h
//
#ifndef __BURST_LEXER_H__
#define __BURST_LEXER_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "BurstErrorCodes.h"
#include "BurstErrorMessages.h"

#include "Token/BurstToken.h"
#include "Token/BurstTokenRegistry.h"

#include "BurstTokenizer.h"
#include "BurstAnalyzer.h"

struct burstLexer;
typedef struct burstLexer
{
    FILE *pFile;
    const char *pFilePath;
    
    BurstTokenizer *pTokenizer;
    BurstAnalyzer *pAnalyzer;
} BurstLexer;

int lexer_create
(
    const char *pFilePath, // IN
    BurstLexer **ppLexer   // OUT
);

int lexer_prepare
(
    BurstLexer *pLexer // IN
);

int lexer_run
(
    BurstLexer *pLexer // IN
);

int lexer_destroy
(
    BurstLexer *pLexer // IN
);

#endif