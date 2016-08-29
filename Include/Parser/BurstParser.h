//
// Burst
// Include/Parser/BurstParser.h
//
#ifndef __BURST_PARSER_H__
#define __BURST_PARSER_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <assert.h>

#include "BurstErrorCodes.h"
#include "BurstErrorMessages.h"

#include "Lexer/Token/BurstToken.h"

#include "AST/BurstAST.h"
#include "AST/Nodes/BurstASTNode.h"

#define BURST_PARSER_GOOD 0x00
#define BURST_PARSER_ERR  0x01
#define BURST_PARSER_EOF  0x02

#define PARSER_ERROR(msg) { \
    if (msg) printf("%s\n", msg); \
    exit(BURST_PARSER_ERR); \
}

struct burstParser;
struct burstParser
{
    int currentTokenIndex;
    
    BurstAST *pAST;
    BurstTokenArray *pTokens;
};
typedef struct burstParser BurstParser;

int parser_create
(
    BurstTokenArray *pTokens, // IN
    BurstParser **ppParser    // OUT
);

int parser_run
(
    BurstParser *pParser // IN
);

BurstToken *parser_getToken
(
    BurstParser *pParser // IN
);

bool parser_seesToken
(
    int tokenType,       // IN
    BurstParser *pParser // IN
);

void parser_advanceToken
(
    BurstParser *pParser // IN
);

int parser_destroy
(
    BurstParser *pParser // IN
);

bool parser_parseVariableDeclaration
(
    BurstParser *pParser,    // IN
    BurstASTNode **ppASTNode // OUT
);

bool parser_parseValueExpression
(
    BurstParser *pParser,    // IN
    BurstASTNode **ppASTNode // OUT
);

bool parser_parseArithmeticExpression
(
    BurstParser *pParser,    // IN
    BurstASTNode **ppASTNode // OUT
);

#endif