//
// Burst
// Include/Frontend/Lexer/Token/BurstTokenRegistry.h
//
#ifndef __BURST_TOKEN_REGISTRY_H__
#define __BURST_TOKEN_REGISTRY_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BurstCommons.h"
#include "BurstErrorCodes.h"
#include "BurstErrorMessages.h"

#include "BurstToken.h"

struct burstTokenRegistry;
typedef struct burstTokenRegistry
{
    BurstTokenArray *pRegisteredTokens;
} BurstTokenRegistry;

int token_registry_create
(
    BurstTokenRegistry **ppTokenRegistry // OUT
);

int token_registry_add_c
(
    char tokenValue,                   // IN
    int tokenType,                     // IN
    BurstTokenRegistry *pTokenRegistry // IN
);

int token_registry_add_s
(
    char *pTokenValue,                 // IN
    int tokenType,                     // IN
    BurstTokenRegistry *pTokenRegistry // IN
);

BurstToken *token_registry_get_c
(
    char tokenValue,                   // IN
    BurstTokenRegistry *pTokenRegistry // IN
);

BurstToken *token_registry_get_s
(
    char *pTokenValue,                 // IN
    BurstTokenRegistry *pTokenRegistry // IN
);

int token_registry_destroy
(
    BurstTokenRegistry *pTokenRegistry // IN
);

#endif