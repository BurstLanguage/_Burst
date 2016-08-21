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

#define BURST_VARIABLE_DECLARATION_NODE 0x00

struct burstASTNode;
struct burstASTNode
{
    int nodeType;
    void *pNode;
};
typedef struct burstASTNode BurstASTNode;

#endif