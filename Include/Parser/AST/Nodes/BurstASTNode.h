//
// Burst
// Include/Parser/AST/Nodes/BurstASTNode.h
//
#ifndef __BURST_AST_NODE_H__
#define __BURST_AST_NODE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <assert.h>

#include "BurstErrorCodes.h"
#include "BurstErrorMessages.h"

#define BURST_VARIABLE_DECLARATION_NODE  0x00
#define BURST_VALUE_EXPRESSION_NODE      0x01
#define BURST_LITERAL_EXPRESSION_NODE    0x02
#define BURST_ARITHMETIC_EXPRESSION_NODE 0x03
#define BURST_REFERENCE_EXPRESSION_NODE  0x04
#define BURST_FUNCTION_DECLARATION_NODE  0x05

struct burstASTNode;
struct burstASTNode
{
    int nodeType;
    void *pNode;
};
typedef struct burstASTNode BurstASTNode;

// These are placed below the definition of the 'BurstASTNode' type, because
//  there's a chance that one of the following files might require the use of
//  that type.
#include "BurstVariableDeclarationNode.h"
#include "BurstValueExpressionNode.h"
#include "BurstLiteralExpressionNode.h"
#include "BurstArithmeticExpressionNode.h"
#include "BurstReferenceExpressionNode.h"
#include "BurstFunctionDeclarationNode.h"

int ast_node_create
(
    int astNodeType,         // IN
    void *pNode,             // IN
    BurstASTNode **ppASTNode // OUT
);

int ast_node_destroy
(
    BurstASTNode *pASTNode // IN
);

#endif