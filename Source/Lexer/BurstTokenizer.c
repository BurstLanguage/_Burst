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
        return BURST_TOKENIZER_ERR;
    
    token_registry_add_c('+', BURST_ADD_TOKEN, pTokenizer->pTokenRegistry);
    token_registry_add_c('-', BURST_SUBTRACT_TOKEN, pTokenizer->pTokenRegistry);
    token_registry_add_c('*', BURST_MULTIPLY_TOKEN, pTokenizer->pTokenRegistry);
    token_registry_add_c('/', BURST_DIVIDE_TOKEN, pTokenizer->pTokenRegistry);
    token_registry_add_c('=', BURST_EQUALS_TOKEN, pTokenizer->pTokenRegistry);
    
    token_registry_add_c(';', BURST_SEMICOLON_TOKEN, pTokenizer->pTokenRegistry);
    
    return BURST_TOKENIZER_OK;
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
    // {
    //     switch (nextChar)
    //     {
    //         default:
    //             token_create_c(nextChar, BURST_UNKNOWN_TOKEN, ppToken);
    //             break;
    //     }
    // }
    
    return pNextToken;
}

// int tokenizer_getNext
// (
//     BurstTokenizer *pTokenizer,
//     BurstToken **ppToken
// )
// {
//     char nextChar = 0x0;
    
//     if (NULL == pTokenizer || NULL != (*ppToken))
//         return BURST_TOKENIZER_ERR;
    
//     if (EOF == (nextChar = fgetc(pTokenizer->pFile)) || feof(pTokenizer->pFile))
//         return BURST_TOKENIZER_EOF;
    
//     if (isspace(nextChar))
//     {
//         token_create_c(nextChar, BURST_WHITESPACE_TOKEN, ppToken);
//     }
//     else if (isalpha(nextChar))
//     {
//         token_create_c(nextChar, BURST_LETTER_TOKEN, ppToken);
//     }
//     else if (isdigit(nextChar))
//     {
//         token_create_c(nextChar, BURST_NUMBER_TOKEN, ppToken);
//     }
//     else
//     {
//         BurstToken *pRegistryResult = token_registry_get_c(nextChar,
//             pTokenizer->pTokenRegistry);
        
//         if (NULL != pRegistryResult)
//         {
//             (*ppToken) = pRegistryResult;
//         }
//         else
//         {
//             token_create_c(nextChar, BURST_UNKNOWN_TOKEN, ppToken);
//         }
//     }
//     // {
//     //     switch (nextChar)
//     //     {
//     //         default:
//     //             token_create_c(nextChar, BURST_UNKNOWN_TOKEN, ppToken);
//     //             break;
//     //     }
//     // }
    
//     return BURST_TOKENIZER_OK;
// }

int tokenizer_run
(
    BurstTokenizer *pTokenizer
)
{
    BurstToken *pCurrentToken = NULL;
    // char currentCharacter = 0x0;
    
    // int combinedTokenType = BURST_UNKNOWN_TOKEN;
    // char *pCombinedTokenValue = (char *) malloc(0x0);
    // size_t combinedTokenLength = 0x0;
    
    if (NULL == pTokenizer)
        return BURST_FAIL;
    
    if (NULL == pTokenizer->pFile)
        return BURST_FAIL;
    
    if (NULL == pTokenizer->pTokens)
        return BURST_FAIL;
    
    while (NULL != (pCurrentToken = tokenizer_getNext(pTokenizer)))
    {
        // Make sure we ignore all unknown and whitespace tokens
        if (BURST_UNKNOWN_TOKEN == pCurrentToken->type ||
            BURST_WHITESPACE_TOKEN == pCurrentToken->type)
        {
            printf("\n");
            
            token_destroy(pCurrentToken);
            
            continue;
        }
        
        printf("'%c' - %02x\n", pCurrentToken->charValue, pCurrentToken->type);
        token_array_add(pCurrentToken, pTokenizer->pTokens);
        
        // if (combinedTokenType == pCurrentToken->type)
        // {
        //     pCombinedTokenValue = (char *) realloc(pCombinedTokenValue,
        //         (sizeof(char) * (combinedTokenLength + 0x1)));
            
        //     *(pCombinedTokenValue + combinedTokenLength) = (
        //         pCurrentToken->charValue
        //     );
            
        //     combinedTokenLength++;
        // }
        // else
        // {
        //     if (BURST_UNKNOWN_TOKEN != combinedTokenType &&
        //         BURST_WHITESPACE_TOKEN != combinedTokenType)
        //     {
        //         BurstToken *pCombinedToken = NULL;
                
        //         // We'll append a null-terminator to the end of our combined
        //         //  token's string, so the strdup function works correctly.
        //         pCombinedTokenValue = (char *) realloc(pCombinedTokenValue, (
        //             sizeof(char) * (combinedTokenLength + 0x1)
        //         ));
        //         *(pCombinedTokenValue + combinedTokenLength) = '\0';
                
        //         token_create_s(strdup(pCombinedTokenValue), combinedTokenType,
        //             &pCombinedToken);
                
        //         token_array_add(pCombinedToken, pTokenizer->pTokens);
                
        //         free(pCombinedTokenValue);
                
        //         pCombinedTokenValue = (char *) malloc(0x0);
        //         combinedTokenLength = 0x0;
        //         combinedTokenType   = BURST_UNKNOWN_TOKEN;
        //     }
        // }
    }
    
    // if (NULL != pCombinedTokenValue)
    //     free(pCombinedTokenValue);
    
    // while (BURST_TOKENIZER_EOF != (getNextStatus = tokenizer_getNext(pTokenizer,
    //     &pCurrentToken)))
    // {
    //     if (BURST_TOKENIZER_ERR == getNextStatus)
    //         break;
        
    //     // Ignore all tokens with the 'BURST_UNKNOWN_TOKEN' type
    //     if (BURST_UNKNOWN_TOKEN == pCurrentToken->type)
    //     {
    //         pCurrentToken = NULL;
            
    //         continue;
    //     }
        
    //     printf("'%c' - %02x\n", pCurrentToken->charValue, pCurrentToken->type);
        
    //     // switch (pCurrentToken->type)
    //     // {
    //     //     default:
    //     //         break;
    //     // }
        
    //     pCurrentToken = NULL;
    // }
    
    // while (EOF != (currentCharacter = fgetc(pTokenizer->pFile)))
    // {
    //     BurstToken *pCurrentToken = NULL;
    //     int currentTokenType = BURST_UNKNOWN_TOKEN;
        
    //     if (isspace(currentCharacter))
    //         currentTokenType = BURST_WHITESPACE_TOKEN;
    //     else if (isalpha(currentCharacter))
    //         currentTokenType = BURST_LETTER_TOKEN;
    //     else if (isdigit(currentCharacter))
    //         currentTokenType = BURST_NUMBER_TOKEN;
    //     else if (ispunct(currentCharacter))
    //         currentTokenType = BURST_PUNCTUATION_TOKEN;
        
    //     if (BURST_UNKNOWN_TOKEN != currentTokenType)
    //     {
    //         if (BURST_SUCCESS != token_create_c(currentCharacter,
    //             currentTokenType, &pCurrentToken))
    //             return BURST_FAIL;
            
    //         token_array_add(pCurrentToken, pTokenizer->pTokens);
    //     }
    // }
    
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