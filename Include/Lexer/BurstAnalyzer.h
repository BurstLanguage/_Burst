//
// Burst
// Include/Lexer/BurstAnalyzer.h
//
#ifndef __BURST_ANALYZER_H__
#define __BURST_ANALYZER_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BurstErrorCodes.h"
#include "BurstErrorMessages.h"

#include "Token/BurstToken.h"

struct burstAnalyzer;
struct burstAnalyzer
{
    BurstTokenArray *pInputTokens;
    BurstTokenArray *pOutputTokens;
};
typedef struct burstAnalyzer BurstAnalyzer;

int analyzer_create
(
    BurstTokenArray *pInputTokens, // IN
    BurstAnalyzer **ppAnalyzer     // OUT
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