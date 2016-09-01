//
// Burst
// Source/Frontend/Parser/AST/Nodes/BurstVariableDeclarationNode.c
//
#include "Frontend/Parser/AST/Nodes/BurstVariableDeclarationNode.h"

int variable_declaration_node_create
(
    char *pVariableType,
    char *pVariableName,
    BurstVariableDeclarationNode **ppNode
)
{
    if (NULL != (*ppNode))
        return BURST_FAIL;
    
    if (NULL == pVariableType || NULL == pVariableName)
        return BURST_FAIL;
    
    (*ppNode) = (BurstVariableDeclarationNode *) malloc(sizeof(
        BurstVariableDeclarationNode));
    
    if (NULL == (*ppNode))
        return BURST_FAIL;
    
    (*ppNode)->pTypeString = pVariableType;
    (*ppNode)->pNameString = pVariableName;
    (*ppNode)->pValueExpressionNode = NULL;
    
    (*ppNode)->destroy = variable_declaration_node_destroy;
    
    return BURST_SUCCESS;
}

int variable_declaration_node_destroy
(
    BurstVariableDeclarationNode *pNode
)
{
    if (NULL == pNode)
        return BURST_FAIL;
    
    // if (NULL != pNode->pTypeString)
    //     free(pNode->pTypeString);
    
    // if (NULL != pNode->pNameString)
    //     free(pNode->pNameString);
    
    if (NULL != pNode->pValueExpressionNode)
        ast_node_destroy(pNode->pValueExpressionNode);
    
    free(pNode);
    
    return BURST_SUCCESS;
}