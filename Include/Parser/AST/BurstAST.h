//
// Burst
// Include/Parser/AST/BurstAST.h
//
#ifndef __BURST_AST_H__
#define __BURST_AST_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <assert.h>

#include "BurstErrorCodes.h"
#include "BurstErrorMessages.h"

#include "Nodes/BurstASTNode.h"

struct burstAST;
struct burstAST
{
    int countASTNodes;
    BurstASTNode **ppASTNodes;
};
typedef struct burstAST BurstAST;

int ast_create
(
    BurstAST **ppAST // OUT
);

int ast_add
(
    BurstASTNode *pASTNode, // IN
    BurstAST *pAST          // IN
);

int ast_destroy
(
    BurstAST *pAST // IN
);

#endif