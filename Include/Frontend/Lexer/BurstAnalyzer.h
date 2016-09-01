//
// Burst
// Include/Frontend/Lexer/BurstAnalyzer.h
//
#ifndef __BURST_ANALYZER_H__
#define __BURST_ANALYZER_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BurstErrorCodes.h"
#include "BurstErrorMessages.h"

#include "Token/BurstToken.h"
#include "Token/BurstTokenRegistry.h"

struct burstAnalyzer;
typedef struct burstAnalyzer
{
    BurstTokenArray *pInputTokens;
    BurstTokenArray *pOutputTokens;
    
    BurstTokenRegistry *pKeywordRegistry;
} BurstAnalyzer;

int analyzer_create
(
    BurstTokenArray *pInputTokens, // IN
    BurstAnalyzer **ppAnalyzer     // OUT
);

int analyzer_setup
(
    BurstAnalyzer *pAnalyzer // IN
);

int analyzer_run
(
    BurstAnalyzer *pAnalyzer // IN
);

int analyzer_destroy
(
    BurstAnalyzer *pAnalyzer // IN
);

#endif