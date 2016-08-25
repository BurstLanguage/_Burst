//
// Burst
// Source/Parser/BurstParser.c
//
#include "Parser/BurstParser.h"

int parser_create
(
    BurstTokenArray *pTokens,
    BurstParser **ppParser
)
{
    if (NULL != (*ppParser))
        return BURST_FAIL;
    
    if (NULL == ((*ppParser) = (BurstParser *) malloc(sizeof(BurstParser))))
        return BURST_FAIL;
    
    (*ppParser)->currentTokenIndex = 0x0;
    (*ppParser)->pTokens = pTokens;
    (*ppParser)->pAST = NULL;
    
    ast_create(&(*ppParser)->pAST);
    
    return BURST_SUCCESS;
}

int parser_run
(
    BurstParser *pParser
)
{
    if (NULL == pParser)
        return BURST_FAIL;
    
    if (NULL == pParser->pTokens)
        return BURST_FAIL;
    
    while (NULL != parser_getToken(pParser))
    {
        int tokenIndexSave = pParser->currentTokenIndex;
        
        if (parser_parseVariableDeclaration(pParser))
        {
            // TODO
            
            continue;
        }
        
        pParser->currentTokenIndex = tokenIndexSave;
        
        // TODO
        
        break;
    }
    
    return BURST_SUCCESS;
}

BurstToken *parser_getToken
(
    BurstParser *pParser
)
{
    if (NULL == pParser)
        return NULL;
    
    if (NULL == pParser->pTokens)
        return NULL;
    
    return token_array_at(pParser->currentTokenIndex, pParser->pTokens);
}

bool parser_seesToken
(
    int tokenType,
    BurstParser *pParser
)
{
    BurstToken *pToken = NULL;
    
    if (NULL == pParser)
        return false;
    
    if (NULL == pParser->pTokens)
        return false;
    
    if (NULL == (pToken = parser_getToken(pParser)))
        return false;
    
    return tokenType == pToken->type;
}

void parser_advanceToken
(
    BurstParser *pParser
)
{
    if (NULL == pParser)
        return;
    
    pParser->currentTokenIndex++;
}

int parser_destroy
(
    BurstParser *pParser
)
{
    if (NULL == pParser)
        return BURST_FAIL;
    
    if (NULL != pParser->pAST)
        ast_destroy(pParser->pAST);
    
    free(pParser);
    
    return BURST_SUCCESS;
}

bool parser_parseVariableDeclaration
(
    BurstParser *pParser
)
{
    BurstToken *pVariableTypeToken = NULL;
    BurstToken *pVariableNameToken = NULL;
    
    if (NULL == pParser)
        return false;
    
    if (!parser_seesToken(BURST_KEYWORD_TOKEN, pParser))
        return false;
    
    pVariableTypeToken = parser_getToken(pParser);
    parser_advanceToken(pParser);
    
    if (!parser_seesToken(BURST_IDENTIFIER_TOKEN, pParser))
        return false;
    
    pVariableNameToken = parser_getToken(pParser);
    parser_advanceToken(pParser);
    
    printf("[Variable Declaration] Type: %s, Name: %s\n",
        pVariableTypeToken->pStringValue, pVariableNameToken->pStringValue);
    
    return true;
}