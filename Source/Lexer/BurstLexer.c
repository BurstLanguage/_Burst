//
// Burst
// Source/Lexer/BurstLexer.c
//
#include "Lexer/BurstLexer.h"

int lexer_create
(
    const char *pFilePath,
    BurstLexer **ppLexer
)
{
    if (NULL != (*ppLexer))
        return BURST_FAIL;
    
    if (NULL == ((*ppLexer) = (BurstLexer *) malloc(sizeof(BurstLexer))))
        return BURST_FAIL;
    
    (*ppLexer)->pFile     = NULL;
    (*ppLexer)->pFilePath = pFilePath;
    
    (*ppLexer)->pTokenizer = NULL;
    
    return BURST_SUCCESS;
}

int lexer_prepare
(
    BurstLexer *pLexer
)
{
    if (NULL == pLexer)
        return BURST_FAIL;
    
    if (NULL == pLexer->pFilePath)
        return BURST_FAIL;
    
    if (NULL == (pLexer->pFile = fopen(pLexer->pFilePath, "r")))
        return BURST_FAIL;
    
    if (BURST_SUCCESS != tokenizer_create(pLexer->pFile, &pLexer->pTokenizer))
        return BURST_FAIL;
    
    return BURST_SUCCESS;
}

int lexer_run
(
    BurstLexer *pLexer
)
{
    if (NULL == pLexer)
        return BURST_FAIL;
    
    if (BURST_SUCCESS != tokenizer_run(pLexer->pTokenizer))
    {
        printf("An error occurred during tokenization of file at path %s\n",
            pLexer->pFilePath);
        
        return BURST_FAIL;
    }
    
    // TODO: Perform lexical analysis
    //  ...
    
    return BURST_SUCCESS;
}

int lexer_destroy
(
    BurstLexer *pLexer
)
{
    if (NULL == pLexer)
        return BURST_FAIL;
    
    if (NULL != pLexer->pTokenizer)
        tokenizer_destroy(pLexer->pTokenizer);
    
    if (NULL != pLexer->pFile)
        fclose(pLexer->pFile);
    
    free(pLexer);
    
    return BURST_SUCCESS;
}