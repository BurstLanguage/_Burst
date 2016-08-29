//
// Burst
// Source/Lexer/BurstTokenizer.c
//
#include "Lexer/BurstTokenizer.h"

int tokenizer_create
(
    FILE *pFile,
    BurstTokenizer **ppTokenizer
)
{
    if (NULL != (*ppTokenizer))
        return BURST_FAIL;
    
    if (NULL == pFile)
        return BURST_FAIL;
    
    if (NULL == ((*ppTokenizer) = (BurstTokenizer *) malloc(sizeof(BurstTokenizer))))
        return BURST_FAIL;
    
    (*ppTokenizer)->pFile = pFile;
    
    (*ppTokenizer)->pTokens = NULL;
    (*ppTokenizer)->pTokenRegistry = NULL;
    
    token_array_create(&(*ppTokenizer)->pTokens);
    token_registry_create(&(*ppTokenizer)->pTokenRegistry);
    
    return BURST_SUCCESS;
}

int tokenizer_setup
(
    BurstTokenizer *pTokenizer
)
{
    if (NULL == pTokenizer)
        return BURST_FAIL;
    
    token_registry_add_c('+', BURST_ADD_TOKEN,       pTokenizer->pTokenRegistry);
    token_registry_add_c('-', BURST_SUBTRACT_TOKEN,  pTokenizer->pTokenRegistry);
    token_registry_add_c('*', BURST_MULTIPLY_TOKEN,  pTokenizer->pTokenRegistry);
    token_registry_add_c('/', BURST_DIVIDE_TOKEN,    pTokenizer->pTokenRegistry);
    token_registry_add_c('=', BURST_EQUALS_TOKEN,    pTokenizer->pTokenRegistry);
    token_registry_add_c(';', BURST_SEMICOLON_TOKEN, pTokenizer->pTokenRegistry);
    token_registry_add_c('[', BURST_LBRACKET_TOKEN,  pTokenizer->pTokenRegistry);
    token_registry_add_c(']', BURST_RBRACKET_TOKEN,  pTokenizer->pTokenRegistry);
    
    return BURST_SUCCESS;
}

BurstToken *tokenizer_getNext
(
    BurstTokenizer *pTokenizer
)
{
    BurstToken *pNextToken = NULL;
    char nextChar = 0x0;
    
    if (NULL == pTokenizer)
        return NULL;
    
    if (EOF == (nextChar = fgetc(pTokenizer->pFile)) || feof(pTokenizer->pFile))
        return NULL;
    
    if (isspace(nextChar))
    {
        token_create_c(nextChar, BURST_WHITESPACE_TOKEN, &pNextToken);
    }
    else if (isalpha(nextChar))
    {
        token_create_c(nextChar, BURST_LETTER_TOKEN, &pNextToken);
    }
    else if (isdigit(nextChar))
    {
        token_create_c(nextChar, BURST_NUMBER_TOKEN, &pNextToken);
    }
    else
    {
        BurstToken *pRegistryResult = token_registry_get_c(nextChar,
            pTokenizer->pTokenRegistry);
        
        if (NULL != pRegistryResult)
        {
            pNextToken = (BurstToken *) malloc(sizeof(BurstToken));
            memcpy(pNextToken, pRegistryResult, sizeof(BurstToken));
        }
        else
        {
            token_create_c(nextChar, BURST_UNKNOWN_TOKEN, &pNextToken);
        }
    }
    
    return pNextToken;
}

int tokenizer_run
(
    BurstTokenizer *pTokenizer
)
{
    BurstToken *pCurrentToken = NULL;
    
    if (NULL == pTokenizer)
        return BURST_FAIL;
    
    if (NULL == pTokenizer->pFile)
        return BURST_FAIL;
    
    if (NULL == pTokenizer->pTokens)
        return BURST_FAIL;
    
    while (NULL != (pCurrentToken = tokenizer_getNext(pTokenizer)))
    {
        // Make sure we ignore all unknown tokens
        if (BURST_UNKNOWN_TOKEN == pCurrentToken->type)
        {
            token_destroy(pCurrentToken);
            
            continue;
        }
        
        token_array_add(pCurrentToken, pTokenizer->pTokens);
    }
    
    return BURST_SUCCESS;
}

int tokenizer_destroy
(
    BurstTokenizer *pTokenizer
)
{
    if (NULL == pTokenizer)
        return BURST_FAIL;
    
    if (NULL != pTokenizer->pTokens)
        token_array_destroy(pTokenizer->pTokens);
    
    if (NULL != pTokenizer->pTokenRegistry)
        token_registry_destroy(pTokenizer->pTokenRegistry);
    
    free(pTokenizer);
    
    return BURST_SUCCESS;
}