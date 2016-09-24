//
// Burst
// Source/Frontend/Parser/AST/Nodes/BurstASTNode.c
//
#include "Frontend/Parser/AST/Nodes/BurstASTNode.h"

int ast_node_create
(
    int nodeType,
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
    
    (*ppASTNode)->nodeType = nodeType;
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
            case BURST_AST_GENERIC_NODE:
            {
                // If, for some odd reason, the "instance" of the 'BurstASTNode'
                //  struct that was passed to us, was used to store another
                //  "instance" of the 'BurstASTNode' struct, we'll call ourself
                //  again.
                ast_node_destroy(
                    (BurstASTNode *) pASTNode->pNode
                );
                
                break;
            }
            
            case BURST_AST_LITERAL_EXPRESSION_NODE:
            {
                literal_expression_node_destroy(
                    (BurstLiteralExpressionNode *) pASTNode->pNode
                );
                
                break;
            }
            
            default:
            {
                // If we make it to this point, we apparently don't have any
                //  idea what type of AST node we're currently trying to
                //  destroy.
                //
                // As a result of this, we're going to perform a basic
                //  'free'. This may or may not (probably the latter) free all
                //  of the memory used for this node.
                free(pASTNode->pNode);
                
                break;
            }
        }
    }
    
    free(pASTNode);
    
    return BURST_SUCCESS;
}