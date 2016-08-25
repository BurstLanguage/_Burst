//
// Burst
// Source/Parser/AST/Nodes/BurstLiteralExpressionNode.c
//
#include "Parser/AST/Nodes/BurstLiteralExpressionNode.h"

int literal_expression_node_create
(
    char *pExpressionValue,
    BurstLiteralExpressionNode **ppNode
)
{
    if (NULL != (*ppNode))
        return BURST_FAIL;
    
    (*ppNode) = (BurstLiteralExpressionNode *) malloc(sizeof(
        BurstLiteralExpressionNode));
    
    if (NULL == (*ppNode))
        return BURST_FAIL;
    
    (*ppNode)->pValueString = pExpressionValue;
    
    (*ppNode)->destroy = literal_expression_node_destroy;
    
    return BURST_SUCCESS;
}

int literal_expression_node_destroy
(
    BurstLiteralExpressionNode *pNode
)
{
    if (NULL == pNode)
        return BURST_FAIL;
    
    free(pNode);
    
    return BURST_SUCCESS;
}