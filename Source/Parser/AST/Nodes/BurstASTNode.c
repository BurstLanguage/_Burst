//
// Burst
// Source/Parser/AST/Nodes/BurstASTNode.c
//
#include "Parser/AST/Nodes/BurstASTNode.h"

int ast_node_create
(
    int astNodeType,
    void *pNode,
    BurstASTNode **ppASTNode
)
{
    if (NULL == pNode)
        return BURST_FAIL;
    
    if (NULL != (*ppASTNode))
        return BURST_FAIL;
    
    if (NULL == ((*ppASTNode) = (BurstASTNode *) malloc(sizeof(BurstASTNode))))
        return BURST_FAIL;
    
    (*ppASTNode)->nodeType = astNodeType;
    (*ppASTNode)->pNode    = pNode;
    
    return BURST_SUCCESS;
}

int ast_node_destroy
(
    BurstASTNode *pASTNode
)
{
    if (NULL == pASTNode)
        return BURST_FAIL;
    
    if (NULL != pASTNode->pNode)
    {
        switch (pASTNode->nodeType)
        {
            case BURST_VARIABLE_DECLARATION_NODE:
                ((BurstVariableDeclarationNode *) pASTNode->pNode)->destroy(
                    ((BurstVariableDeclarationNode *) pASTNode->pNode)
                );
                break;
            
            case BURST_VALUE_EXPRESSION_NODE:
                ((BurstValueExpressionNode *) pASTNode->pNode)->destroy(
                    ((BurstValueExpressionNode *) pASTNode->pNode)
                );
                break;
            
            case BURST_LITERAL_EXPRESSION_NODE:
                ((BurstLiteralExpressionNode *) pASTNode->pNode)->destroy(
                    ((BurstLiteralExpressionNode *) pASTNode->pNode)
                );
                break;
            
            case BURST_ARITHMETIC_EXPRESSION_NODE:
                ((BurstArithmeticExpressionNode *) pASTNode->pNode)->destroy(
                    ((BurstArithmeticExpressionNode *) pASTNode->pNode)
                );
                break;
            
            default:
                break;
        }
    }
    
    free(pASTNode);
    
    return BURST_SUCCESS;
}