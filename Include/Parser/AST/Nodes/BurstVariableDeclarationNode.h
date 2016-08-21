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

struct burstVariableDeclarationNode;
struct burstVariableDeclarationNode
{
    char *pType; // Variable Type
    char *pName; // Variable Name
};
typedef struct burstVariableDeclarationNode BurstVariableDeclarationNode;

#endif