//
// Burst
// Include/Parser/AST/Nodes/BurstVariableDeclarationNode.h
//
#ifndef __BURST_AST_VARIABLE_DECLARATION_NODE_H__
#define __BURST_AST_VARIABLE_DECLARATION_NODE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <assert.h>

#include "BurstErrorCodes.h"
#include "BurstErrorMessages.h"

#include "BurstASTNode.h"

struct burstVariableDeclarationNode;
struct burstVariableDeclarationNode
{
    char *pTypeString; // Variable Type
    char *pNameString; // Variable Name
    
    // TODO: Variable Value Node
    
    int (*destroy)
    (
        struct burstVariableDeclarationNode *pNode
    );
};
typedef struct burstVariableDeclarationNode BurstVariableDeclarationNode;

int variable_declaration_node_create
(
    char *pVariableType,                  // IN
    char *pVariableName,                  // IN
    BurstVariableDeclarationNode **ppNode // OUT
);

int variable_declaration_node_destroy
(
    BurstVariableDeclarationNode *pNode // IN
);

#endif