//
// Burst
// Source/Parser/AST/Nodes/BurstValueExpressionNode.c
//
#include "Parser/AST/Nodes/BurstValueExpressionNode.h"

int value_expression_node_create
(
    int valueType,
    BurstASTNode *pValueNode,
    BurstValueExpressionNode **ppNode
)
{
    if (NULL != (*ppNode))
        return BURST_FAIL;
    
    if (NULL == pValueNode)
        return BURST_FAIL;
    
    (*ppNode) = (BurstValueExpressionNode *) malloc(sizeof(
        BurstValueExpressionNode));
    
    if (NULL == (*ppNode))
        return BURST_FAIL;
    
    (*ppNode)->valueType = valueType;
    (*ppNode)->pValueNode = pValueNode;
    
    (*ppNode)->destroy = value_expression_node_destroy;
    
    return BURST_SUCCESS;
}

int value_expression_node_destroy
(
    BurstValueExpressionNode *pNode
)
{
    if (NULL == pNode)
        return BURST_FAIL;
    
    if (NULL != pNode->pValueNode)
        ast_node_destroy(pNode->pValueNode);
    
    free(pNode);
    
    return BURST_SUCCESS;
}