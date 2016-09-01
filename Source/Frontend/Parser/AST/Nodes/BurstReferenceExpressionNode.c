//
// Burst
// Source/Frontend/Parser/AST/Nodes/BurstReferenceExpressionNode.c
//
#include "Frontend/Parser/AST/Nodes/BurstReferenceExpressionNode.h"

int reference_expression_node_create
(
    char *pIdentifier,
    BurstReferenceExpressionNode **ppNode
)
{
    if (NULL == pIdentifier)
        return BURST_FAIL;
    
    if (NULL != (*ppNode))
        return BURST_FAIL;
    
    (*ppNode) = (BurstReferenceExpressionNode *) malloc(sizeof(
        BurstReferenceExpressionNode));
    
    if (NULL == (*ppNode))
        return BURST_SUCCESS;
    
    (*ppNode)->pIdentifier = pIdentifier;
    
    (*ppNode)->destroy = reference_expression_node_destroy;
    
    return BURST_SUCCESS;
}

int reference_expression_node_destroy
(
    BurstReferenceExpressionNode *pNode
)
{
    if (NULL == pNode)
        return BURST_FAIL;
    
    free(pNode);
    
    return BURST_SUCCESS;
}