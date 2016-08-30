//
// Burst
// Include/Parser/AST/Nodes/BurstReferenceExpressionNode.h
//
#ifndef __BURST_AST_REFERENCE_EXPRESSION_NODE_H__
#define __BURST_AST_REFERENCE_EXPRESSION_NODE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <assert.h>

#include "BurstErrorCodes.h"
#include "BurstErrorMessages.h"

#include "BurstASTNode.h"

struct burstReferenceExpressionNode;
struct burstReferenceExpressionNode
{
    char *pIdentifier;
    
    int (*destroy)
    (
        struct burstReferenceExpressionNode *pNode
    );
};
typedef struct burstReferenceExpressionNode BurstReferenceExpressionNode;

int reference_expression_node_create
(
    char *pIdentifier,                    // IN
    BurstReferenceExpressionNode **ppNode // OUT
);

int reference_expression_node_destroy
(
    BurstReferenceExpressionNode *pNode // IN
);

#endif