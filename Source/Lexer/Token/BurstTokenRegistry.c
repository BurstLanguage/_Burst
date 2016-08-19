//
// Burst
// Source/Lexer/Token/BurstTokenRegistry.c
//
#include "Lexer/Token/BurstTokenRegistry.h"

int token_registry_create
(
    BurstTokenRegistry **ppTokenRegistry
)
{
    if (NULL != (*ppTokenRegistry))
        return BURST_FAIL;
    
    if (NULL == ((*ppTokenRegistry) = (BurstTokenRegistry *) malloc(sizeof(
        BurstTokenRegistry))))
        return BURST_FAIL;
    
    (*ppTokenRegistry)->pRegisteredTokens = NULL;
    
    token_array_create(&((*ppTokenRegistry)->pRegisteredTokens));
    
    return BURST_SUCCESS;
}

int token_registry_add_c
(
    char tokenValue,
    int tokenType,
    BurstTokenRegistry *pTokenRegistry
)
{
    BurstToken *pToken = NULL;
    
    if (NULL == pTokenRegistry)
        return BURST_FAIL;
    
    if (0x0 == tokenValue)
        return BURST_FAIL;
    
    token_create_c(tokenValue, tokenType, &pToken);
    token_array_add(pToken, pTokenRegistry->pRegisteredTokens);
    
    return BURST_SUCCESS;
}

int token_registry_add_s
(
    char *pTokenValue,
    int tokenType,
    BurstTokenRegistry *pTokenRegistry
)
{
    BurstToken *pToken = NULL;
    
    if (NULL == pTokenRegistry)
        return BURST_FAIL;
    
    if (NULL == pTokenValue)
        return BURST_FAIL;
    
    token_create_s(strdup(pTokenValue), tokenType, &pToken);
    token_array_add(pToken, pTokenRegistry->pRegisteredTokens);
    
    return BURST_SUCCESS;
}

BurstToken *token_registry_get_c
(
    char tokenValue,
    BurstTokenRegistry *pTokenRegistry
)
{
    if (NULL == pTokenRegistry)
        return NULL;
    
    if (NULL == pTokenRegistry->pRegisteredTokens)
        return NULL;
    
    for (int tokenIndex = 0x0; tokenIndex <
        pTokenRegistry->pRegisteredTokens->tokenCount; ++tokenIndex)
    {
        BurstToken *pCurrentToken = token_array_at(tokenIndex,
            pTokenRegistry->pRegisteredTokens);
        
        if (pCurrentToken->charValue == tokenValue)
            return pCurrentToken;
    }
    
    return NULL;
}

BurstToken *token_registry_get_s
(
    char *pTokenValue,
    BurstTokenRegistry *pTokenRegistry
)
{
    if (NULL == pTokenRegistry)
        return NULL;
    
    if (NULL == pTokenRegistry->pRegisteredTokens)
        return NULL;
    
    for (int tokenIndex = 0x0; tokenIndex <
        pTokenRegistry->pRegisteredTokens->tokenCount; ++tokenIndex)
    {
        BurstToken *pCurrentToken = token_array_at(tokenIndex,
            pTokenRegistry->pRegisteredTokens);
        
        if (!strncmp(pTokenValue, pCurrentToken->pStringValue, strlen(pTokenValue)))
            return pCurrentToken;
    }
    
    return NULL;
}

int token_registry_destroy
(
    BurstTokenRegistry *pTokenRegistry
)
{
    if (NULL == pTokenRegistry)
        return BURST_FAIL;
    
    if (NULL != pTokenRegistry->pRegisteredTokens)
        token_array_destroy(pTokenRegistry->pRegisteredTokens);
    
    free(pTokenRegistry);
    
    return BURST_SUCCESS;
}