//
// Burst
// Include/Frontend/Parser/AST/Nodes/BurstFunctionDeclarationNode.h
//
#ifndef __BURST_AST_FUNCTION_DECLARATION_NODE_H__
#define __BURST_AST_FUNCTION_DECLARATION_NODE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <assert.h>

#include "BurstErrorCodes.h"
#include "BurstErrorMessages.h"

#include "Frontend/Parser/AST/BurstAST.h"
#include "BurstASTNode.h"

struct burstFunctionDeclarationNode;
typedef struct burstFunctionDeclarationNode
{
    char *pReturnType;
    char *pIdentifier;
    
    BurstAST *pArgs;
    BurstAST *pBody;
    
    int (*destroy)
    (
        struct burstFunctionDeclarationNode *pNode
    );
} BurstFunctionDeclarationNode;

int function_declaration_node_create
(
    char *pFunctionReturnType,            // IN
    char *pFunctionIdentifier,            // IN
    BurstFunctionDeclarationNode **ppNode // OUT
);

int function_declaration_node_destroy
(
    BurstFunctionDeclarationNode *pNode // IN
);

#endif