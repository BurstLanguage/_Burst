//
// Burst
// Source/Frontend/Parser/AST/Nodes/BurstLiteralExpressionNode.c
//
#include "Frontend/Parser/AST/Nodes/BurstLiteralExpressionNode.h"

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
    
    // Error allocating memory for node
    // TODO (Giga): Come up with a better way to handle this.
    if (NULL == (*ppNode))
        return BURST_FAIL;
    
    (*ppNode)->pValueString = pExpressionValue;
    
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