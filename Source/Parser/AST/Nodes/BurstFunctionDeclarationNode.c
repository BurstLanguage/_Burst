//
// Burst
// Source/Parser/AST/Nodes/BurstFunctionDeclarationNode.c
//
#include "Parser/AST/Nodes/BurstFunctionDeclarationNode.h"

int function_declaration_node_create
(
    char *pFunctionReturnType,
    char *pFunctionIdentifier,
    BurstFunctionDeclarationNode **ppNode
)
{
    if (NULL == pFunctionReturnType || NULL == pFunctionIdentifier)
        return BURST_FAIL;
    
    if (NULL != (*ppNode))
        return BURST_FAIL;
    
    (*ppNode) = (BurstFunctionDeclarationNode *) malloc(sizeof(
        BurstFunctionDeclarationNode));
    
    if (NULL == (*ppNode))
        return BURST_FAIL;
    
    (*ppNode)->pReturnType = pFunctionReturnType;
    (*ppNode)->pIdentifier = pFunctionIdentifier;
    
    ast_create(&(*ppNode)->pArgs);
    ast_create(&(*ppNode)->pBody);
    
    (*ppNode)->destroy = function_declaration_node_destroy;
    
    return BURST_SUCCESS;
}

int function_declaration_node_destroy
(
    BurstFunctionDeclarationNode *pNode
)
{
    if (NULL == pNode)
        return BURST_FAIL;
    
    if (NULL != pNode->pArgs)
        ast_destroy(pNode->pArgs);
    
    if (NULL != pNode->pBody)
        ast_destroy(pNode->pBody);
    
    free(pNode);
    
    return BURST_SUCCESS;
}