//
// Burst
// Include/Lexer/BurstLexer.h
//
#ifndef __BURST_LEXER_H__
#define __BURST_LEXER_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "BurstErrorCodes.h"
#include "BurstErrorMessages.h"

struct burstLexer;
struct burstLexer
{
    FILE *pFile;
    const char *pFilePath;
};
typedef struct burstLexer BurstLexer;

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