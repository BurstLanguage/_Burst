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
        
        BurstASTNode *pCurrentASTNode = NULL;
        
        if (!parser_parseVariableDeclaration(pParser, &pCurrentASTNode))
            pParser->currentTokenIndex = tokenIndexSave;
        
        assert(BURST_SUCCESS == ast_add(pCurrentASTNode, pParser->pAST));
        
        // TODO: Remove this...
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
    BurstParser *pParser,
    BurstASTNode **ppASTNode
)
{
    // BurstASTNode *pVariableValueASTNode = NULL;
    BurstVariableDeclarationNode *pVariableDeclaration = NULL;
    
    BurstToken *pVariableTypeToken = NULL;
    BurstToken *pVariableNameToken = NULL;
    
    if (NULL == pParser)
        return false;
    
    if (NULL != (*ppASTNode))
        return false;
    
    if (!parser_seesToken(BURST_KEYWORD_TOKEN, pParser))
        return false;
    
    pVariableTypeToken = parser_getToken(pParser);
    parser_advanceToken(pParser);
    
    if (!parser_seesToken(BURST_IDENTIFIER_TOKEN, pParser))
        return false;
    
    pVariableNameToken = parser_getToken(pParser);
    parser_advanceToken(pParser);
    
    assert(BURST_SUCCESS == variable_declaration_node_create(
        pVariableTypeToken->pStringValue,
        pVariableNameToken->pStringValue,
        &pVariableDeclaration
    ));
    
    if (parser_seesToken(BURST_EQUALS_TOKEN, pParser))
    {
        int tokenIndexSave = pParser->currentTokenIndex;
        
        if (!parser_parseValueExpression(pParser,
            &pVariableDeclaration->pValueExpressionNode))
            pParser->currentTokenIndex = tokenIndexSave;
    }
    
    assert(BURST_SUCCESS == ast_node_create(
        BURST_VARIABLE_DECLARATION_NODE, pVariableDeclaration, ppASTNode
    ));
    
    return true;
}

bool parser_parseValueExpression
(
    BurstParser *pParser,
    BurstASTNode **ppASTNode
)
{
    if (NULL == pParser)
        return false;
    
    if (NULL != (*ppASTNode))
        return false;
    
    // TODO: Support more than just number-literals
    if (parser_seesToken(BURST_NUMBER_TOKEN, pParser))
    {
        BurstToken *pLiteralExpressionToken = NULL;
        BurstLiteralExpressionNode *pLiteralExpressionNode = NULL;
        
        pLiteralExpressionToken = parser_getToken(pParser);
        parser_advanceToken(pParser);
        
        assert(BURST_SUCCESS == literal_expression_node_create(
            pLiteralExpressionToken->pStringValue, &pLiteralExpressionNode
        ));
        assert(BURST_SUCCESS == ast_node_create(
            BURST_LITERAL_EXPRESSION_NODE, pLiteralExpressionToken, ppASTNode
        ));
        
        return true;
    }
    
    return true;
}