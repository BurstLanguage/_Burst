//
// Burst
// Include/Parser/AST/Nodes/BurstArithmeticExpressionNode.h
//
#ifndef __BURST_AST_ARITHMETIC_EXPRESSION_NODE_H__
#define __BURST_AST_ARITHMETIC_EXPRESSION_NODE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <assert.h>

#include "BurstErrorCodes.h"
#include "BurstErrorMessages.h"

#include "BurstASTNode.h"

struct burstArithmeticExpressionNode;
typedef struct burstArithmeticExpressionNode
{
    BurstASTNode *pLeftSide;
    BurstASTNode *pRightSide;
    
    char *pOperator;
    
    int (*destroy)
    (
        struct burstArithmeticExpressionNode *pNode
    );
} BurstArithmeticExpressionNode;

int arithmetic_expression_node_create
(
    BurstASTNode *pExpressionLeft,         // IN
    BurstASTNode *pExpressionRight,        // IN
    char *pExpressionOperator,             // IN
    BurstArithmeticExpressionNode **ppNode // OUT
);

int arithmetic_expression_node_destroy
(
    BurstArithmeticExpressionNode *pNode // IN
);

#endif