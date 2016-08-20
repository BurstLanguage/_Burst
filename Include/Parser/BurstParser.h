//
// Burst
// Include/Parser/BurstParser.h
//
#ifndef __BURST_PARSER_H__
#define __BURST_PARSER_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <assert.h>

#include "BurstErrorCodes.h"
#include "BurstErrorMessages.h"

#include "Lexer/Token/BurstToken.h"

struct burstParser;
struct burstParser
{
    int currentTokenIndex;
    
    BurstTokenArray *pTokens;
};
typedef struct burstParser BurstParser;

int parser_create
(
    BurstTokenArray *pTokens, // IN
    BurstParser **ppParser    // OUT
);

int parser_run
(
    BurstParser *pParser // IN
);

int parser_destroy
(
    BurstParser *pParser // IN
);

#endif