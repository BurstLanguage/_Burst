//
// Burst
// Source/Lexer/BurstAnalyzer.c
//
#include "Lexer/BurstAnalyzer.h"

int analyzer_create
(
    BurstTokenArray *pInputTokens,
    BurstAnalyzer **ppAnalyzer
)
{
    if (NULL != (*ppAnalyzer))
        return BURST_FAIL;
    
    if (NULL == ((*ppAnalyzer) = (BurstAnalyzer *) malloc(sizeof(BurstAnalyzer))))
        return BURST_FAIL;
    
    (*ppAnalyzer)->pInputTokens     = pInputTokens;
    (*ppAnalyzer)->pOutputTokens    = NULL;
    (*ppAnalyzer)->pKeywordRegistry = NULL;
    
    token_array_create(&((*ppAnalyzer)->pOutputTokens));
    token_registry_create(&((*ppAnalyzer)->pKeywordRegistry));
    
    return BURST_SUCCESS;
}

int analyzer_setup
(
    BurstAnalyzer *pAnalyzer
)
{
    if (NULL == pAnalyzer)
        return BURST_FAIL;
    
    token_registry_add_s("int",    BURST_TYPE_TOKEN,    pAnalyzer->pKeywordRegistry);
    token_registry_add_s("void",   BURST_TYPE_TOKEN,    pAnalyzer->pKeywordRegistry);
    token_registry_add_s("fn",     BURST_KEYWORD_TOKEN, pAnalyzer->pKeywordRegistry);
    token_registry_add_s("func",   BURST_KEYWORD_TOKEN, pAnalyzer->pKeywordRegistry);
    token_registry_add_s("return", BURST_KEYWORD_TOKEN, pAnalyzer->pKeywordRegistry);
    
    return BURST_SUCCESS;
}

int analyzer_run
(
    BurstAnalyzer *pAnalyzer
)
{
    BurstToken *pLastInputToken = NULL;
    BurstToken *pCurrentInputToken = NULL;
    
    int outputTokenType = BURST_UNKNOWN_TOKEN;
    char *pOutputTokenValue = NULL;
    size_t outputTokenValueLength = 0x0;
    
    if (NULL == pAnalyzer)
        return BURST_FAIL;
    
    if (NULL == pAnalyzer->pInputTokens || NULL == pAnalyzer->pOutputTokens)
        return BURST_FAIL;
    
    for (int inputTokenIndex = 0x0; inputTokenIndex <
        pAnalyzer->pInputTokens->tokenCount; ++inputTokenIndex)
    {
        pCurrentInputToken = token_array_at(inputTokenIndex,
            pAnalyzer->pInputTokens);
        
        if (NULL == pOutputTokenValue)
            pOutputTokenValue = (char *) malloc(sizeof(char));
        
        if (outputTokenType == pCurrentInputToken->type)
        {
            pOutputTokenValue = (char *) realloc(pOutputTokenValue, (
                sizeof(char) * (outputTokenValueLength + 0x1))
            );
            
            *(pOutputTokenValue + outputTokenValueLength) = (
                pCurrentInputToken->charValue
            );
            
            outputTokenValueLength++;
        }
        else
        {
            if (BURST_UNKNOWN_TOKEN != outputTokenType &&
                BURST_WHITESPACE_TOKEN != outputTokenType)
            {
                BurstToken *pTokenRegistryResult = NULL;
                BurstToken *pOutputToken = NULL;
                
                pOutputTokenValue = (char *) realloc(pOutputTokenValue, (
                    sizeof(char) * (outputTokenValueLength + 0x1)
                ));
                
                *(pOutputTokenValue + outputTokenValueLength) = '\0';
                
                if (NULL != (pTokenRegistryResult = token_registry_get_s(
                    pOutputTokenValue, pAnalyzer->pKeywordRegistry)))
                    outputTokenType = pTokenRegistryResult->type;
                else
                {
                    switch (outputTokenType)
                    {
                        case BURST_LETTER_TOKEN:
                            outputTokenType = BURST_IDENTIFIER_TOKEN;
                            break;
                        
                        default:
                            break;
                    }
                }
                
                token_create_s(strdup(pOutputTokenValue), outputTokenType,
                    &pOutputToken);
                token_array_add(pOutputToken, pAnalyzer->pOutputTokens);
            }
            
            free(pOutputTokenValue);
            pOutputTokenValue = (char *) calloc(0x1, sizeof(char));
            
            memcpy(pOutputTokenValue, &pCurrentInputToken->charValue, sizeof(char));
            
            outputTokenValueLength = 0x1;
            outputTokenType = pCurrentInputToken->type;
        }
        
        pLastInputToken = pCurrentInputToken;
    }
    
    // Make sure last token in file gets added to token array.
    if (BURST_UNKNOWN_TOKEN != outputTokenType)
    {
        BurstToken *pLastToken = NULL;
        
        pOutputTokenValue = (char *) realloc(pOutputTokenValue, (
            sizeof(char) * (outputTokenValueLength + 0x1)
        ));
        
        *(pOutputTokenValue + outputTokenValueLength) = '\0';
        
        token_create_s(strdup(pOutputTokenValue), outputTokenType, &pLastToken);
        token_array_add(pLastToken, pAnalyzer->pOutputTokens);
    }
    
    if (NULL != pOutputTokenValue)
        free(pOutputTokenValue);
    
    return BURST_SUCCESS;
}

int analyzer_destroy
(
    BurstAnalyzer *pAnalyzer
)
{
    if (NULL == pAnalyzer)
        return BURST_FAIL;
    
    if (NULL != pAnalyzer->pOutputTokens)
        token_array_destroy(pAnalyzer->pOutputTokens);
    
    if (NULL != pAnalyzer->pKeywordRegistry)
        token_registry_destroy(pAnalyzer->pKeywordRegistry);
    
    free(pAnalyzer);
    
    return BURST_SUCCESS;
}