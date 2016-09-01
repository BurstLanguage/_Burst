//
// Burst
// Source/Frontend/Parser/AST/Nodes/BurstArithmeticExpressionNode.c
//
#include "Frontend/Parser/AST/Nodes/BurstArithmeticExpressionNode.h"

int arithmetic_expression_node_create
(
    BurstASTNode *pExpressionLeft,
    BurstASTNode *pExpressionRight,
    char *pExpressionOperator,
    BurstArithmeticExpressionNode **ppNode
)
{
    if (NULL != (*ppNode))
        return BURST_FAIL;
    
    if (NULL == pExpressionLeft || NULL == pExpressionRight)
        return BURST_FAIL;
    
    if (NULL == pExpressionOperator)
        return BURST_FAIL;
    
    (*ppNode) = (BurstArithmeticExpressionNode *) malloc(sizeof(
        BurstArithmeticExpressionNode));
    
    if (NULL == (*ppNode))
        return BURST_FAIL;
    
    (*ppNode)->pLeftSide  = pExpressionLeft;
    (*ppNode)->pRightSide = pExpressionRight;
    (*ppNode)->pOperator  = pExpressionOperator;
    
    (*ppNode)->destroy = arithmetic_expression_node_destroy;
    
    return BURST_SUCCESS;
}

int arithmetic_expression_node_destroy
(
    BurstArithmeticExpressionNode *pNode
)
{
    if (NULL == pNode)
        return BURST_FAIL;
    
    if (NULL != pNode->pLeftSide)
        ast_node_destroy(pNode->pLeftSide);
    
    if (NULL != pNode->pRightSide)
        ast_node_destroy(pNode->pRightSide);
    
    free(pNode);
    
    return BURST_SUCCESS;
}