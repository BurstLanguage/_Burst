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
    
    token_array_create(&(*ppTokenizer)->pTokens);
    
    return BURST_SUCCESS;
}

int tokenizer_run
(
    BurstTokenizer *pTokenizer
)
{
    char currentCharacter = 0x0;
    
    if (NULL == pTokenizer)
        return BURST_FAIL;
    
    if (NULL == pTokenizer->pFile)
        return BURST_FAIL;
    
    if (NULL == pTokenizer->pTokens)
        return BURST_FAIL;
    
    while (EOF != (currentCharacter = fgetc(pTokenizer->pFile)))
    {
        BurstToken *pCurrentToken = NULL;
        int currentTokenType = BURST_UNKNOWN_TOKEN;
        
        if (isspace(currentCharacter))
            currentTokenType = BURST_WHITESPACE_TOKEN;
        else if (isalpha(currentCharacter))
            currentTokenType = BURST_LETTER_TOKEN;
        else if (isdigit(currentCharacter))
            currentTokenType = BURST_NUMBER_TOKEN;
        else if (ispunct(currentCharacter))
            currentTokenType = BURST_PUNCTUATION_TOKEN;
        
        if (BURST_UNKNOWN_TOKEN != currentTokenType)
        {
            if (BURST_SUCCESS != token_create_c(currentCharacter,
                currentTokenType, &pCurrentToken))
                return BURST_FAIL;
            
            token_array_add(pCurrentToken, pTokenizer->pTokens);
        }
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
    
    free(pTokenizer);
    
    return BURST_SUCCESS;
}