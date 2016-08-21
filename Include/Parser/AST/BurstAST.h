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
#include "Nodes/BurstVariableDeclarationNode.h"

struct burstAST;
struct burstAST
{
    int countASTNodes;
    BurstASTNode *pASTNodes;
};
typedef struct burstAST BurstAST;

#endif