//
// Burst
// Include/Frontend/Parser/AST/BurstAST.h
//
#ifndef __BURST_AST_H__
#define __BURST_AST_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <assert.h>

#include "BurstCommons.h"
#include "BurstErrorCodes.h"
#include "BurstErrorMessages.h"

struct burstAST;
typedef struct burstAST BurstAST;

#include "Nodes/BurstASTNode.h"

struct burstAST
{
    int countASTNodes;
    BurstASTNode **ppASTNodes;
};

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