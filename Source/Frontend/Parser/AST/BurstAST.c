//
// Burst
// Source/Frontend/Parser/AST/BurstAST.c
//
#include "Frontend/Parser/AST/BurstAST.h"

int ast_create
(
    BurstAST **ppAST
)
{
    if (NULL != (*ppAST))
        return BURST_FAIL;
    
    if (NULL == ((*ppAST) = (BurstAST *) malloc(sizeof(BurstAST))))
        return BURST_FAIL;
    
    (*ppAST)->countASTNodes = 0x0;
    (*ppAST)->ppASTNodes    = (BurstASTNode **) malloc(0x0);
    
    return BURST_SUCCESS;
}

int ast_add
(
    BurstASTNode *pASTNode,
    BurstAST *pAST
)
{
    if (NULL == pAST || NULL == pASTNode)
        return BURST_FAIL;
    
    pAST->ppASTNodes = (BurstASTNode **) realloc(
        pAST->ppASTNodes, (sizeof(BurstASTNode *) * (pAST->countASTNodes + 0x1))
    );
    
    *(pAST->ppASTNodes + pAST->countASTNodes) = pASTNode;
    
    pAST->countASTNodes++;
    
    return BURST_SUCCESS;
}

int ast_destroy
(
    BurstAST *pAST
)
{
    if (NULL == pAST)
        return BURST_FAIL;
    
    if (NULL != pAST->ppASTNodes)
    {
        for (int nodeIndex = 0x0; nodeIndex < pAST->countASTNodes; ++nodeIndex)
            ast_node_destroy(*(pAST->ppASTNodes + nodeIndex));
        
        free(pAST->ppASTNodes);
    }
    
    free(pAST);
    
    return BURST_SUCCESS;
}