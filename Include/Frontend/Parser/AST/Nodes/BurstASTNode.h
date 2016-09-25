//
// Burst
// Include/Frontend/Parser/AST/Nodes/BurstASTNode.h
//
#ifndef __BURST_AST_NODE_H__
#define __BURST_AST_NODE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "BurstCommons.h"
#include "BurstErrorCodes.h"
#include "BurstErrorMessages.h"

#define BURST_AST_GENERIC_NODE            0x00
#define BURST_AST_LITERAL_EXPRESSION_NODE 0x01

// The 'BurstASTNode' struct is a generic AST node, designed to store
//  information about other AST nodes.
//
// The information contained within this struct, will be the type of AST node
//  being contained, as well as a pointer to said AST node.
//
// We take this approach, as it allows us to have one central node that we can
//  use to reference other AST nodes with. The usefulness of this will
//  [hopefully] become more apparent in the future.
struct burstASTNode;
typedef struct burstASTNode
{
    int nodeType;
    void *pNode;
} BurstASTNode;

// These includes are placed below the definition of the 'BurstASTNode' type, as
//  there's a good chance that one of the following files might require the use
//  of the aforementioned type.
#include "BurstLiteralExpressionNode.h"

int ast_node_create
(
    int nodeType,            // IN
    void *pNode,             // IN
    BurstASTNode **ppASTNode // OUT
);

int ast_node_destroy
(
    BurstASTNode *pASTNode // IN
);

#endif