//
// Burst
// Source/Lexer/Token/BurstToken.c
//
#include "Lexer/Token/BurstToken.h"

int token_create
(
    int type,
    BurstToken **ppToken
)
{
    if (NULL != (*ppToken))
        return BURST_FAIL;
    
    if (NULL == ((*ppToken) = (BurstToken *) malloc(sizeof(BurstToken))))
        return BURST_FAIL;
    
    (*ppToken)->type = type;
    
    (*ppToken)->charValue    = 0x0;
    (*ppToken)->pStringValue = NULL;
    
    return BURST_SUCCESS;
}

int token_create_c
(
    char value,
    int type,
    BurstToken **ppToken
)
{
    if (BURST_SUCCESS != token_create(type, ppToken))
        return BURST_FAIL;
    
    (*ppToken)->charValue = value;
    
    return BURST_SUCCESS;
}

int token_create_s
(
    char *pValue,
    int type,
    BurstToken **ppToken
)
{
    if (BURST_SUCCESS != token_create(type, ppToken))
        return BURST_FAIL;
    
    (*ppToken)->pStringValue = pValue;
    
    return BURST_SUCCESS;
}

int token_destroy
(
    BurstToken *pToken
)
{
    if (NULL == pToken)
        return BURST_FAIL;
    
    if (NULL != pToken->pStringValue)
        free(pToken->pStringValue);
    
    free(pToken);
    
    return BURST_SUCCESS;
}

int token_array_create
(
    BurstTokenArray **ppTokenArray
)
{
    if (NULL != (*ppTokenArray))
        return BURST_FAIL;
    
    if (NULL == ((*ppTokenArray) = (BurstTokenArray *) malloc(sizeof(
        BurstTokenArray))))
        return BURST_FAIL;
    
    (*ppTokenArray)->tokenCount = 0x0;
    (*ppTokenArray)->ppTokens   = (BurstToken **) malloc(0x0);
    
    return BURST_SUCCESS;
}

int token_array_add
(
    BurstToken *pToken,
    BurstTokenArray *pTokenArray
)
{
    if (NULL == pToken || NULL == pTokenArray)
        return BURST_FAIL;
    
    if (NULL == pTokenArray->ppTokens)
        return BURST_FAIL;
    
    pTokenArray->ppTokens = (BurstToken **) realloc(pTokenArray->ppTokens,
        (sizeof(BurstToken *) * (pTokenArray->tokenCount + 1)));
    *(pTokenArray->ppTokens + pTokenArray->tokenCount) = pToken;
    
    pTokenArray->tokenCount++;
    
    return BURST_SUCCESS;
}

BurstToken *token_array_at
(
    int index,
    BurstTokenArray *pTokenArray
)
{
    if (NULL == pTokenArray)
        return NULL;
    
    if (0 > index || pTokenArray->tokenCount <= index)
        return NULL;
    
    return *(pTokenArray->ppTokens + index);
}

int token_array_destroy
(
    BurstTokenArray *pTokenArray
)
{
    if (NULL == pTokenArray)
        return BURST_FAIL;
    
    if (NULL != pTokenArray->ppTokens)
    {
        for (int tokenIndex = 0x0; tokenIndex < pTokenArray->tokenCount;
            ++tokenIndex)
        {
            token_destroy(*(pTokenArray->ppTokens + tokenIndex));
        }
        
        free(pTokenArray->ppTokens);
    }
    
    free(pTokenArray);
    
    return BURST_SUCCESS;
}