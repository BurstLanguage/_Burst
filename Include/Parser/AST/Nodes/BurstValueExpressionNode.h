//
// Burst
// Include/Parser/AST/Nodes/BurstValueExpressionNode.h
//
#ifndef __BURST_AST_VALUE_EXPRESSION_NODE_H__
#define __BURST_AST_VALUE_EXPRESSION_NODE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <assert.h>

#include "BurstErrorCodes.h"
#include "BurstErrorMessages.h"

#include "BurstASTNode.h"

struct burstValueExpressionNode;
typedef struct burstValueExpressionNode
{
    int valueType;
    BurstASTNode *pValueNode;
    
    int (*destroy)
    (
        struct burstValueExpressionNode *pNode
    );
} BurstValueExpressionNode;

int value_expression_node_create
(
    int valueType,                    // IN
    BurstASTNode *pValueNode,         // IN
    BurstValueExpressionNode **ppNode // OUT
);

int value_expression_node_destroy
(
    BurstValueExpressionNode *pNode // IN
);

#endif