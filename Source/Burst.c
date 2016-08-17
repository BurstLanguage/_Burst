//
// Burst
// Source/Burst.c
//
#include "Burst.h"

int main
(
    int argumentCount,
    const char **ppArgumentValues
)
{
    BurstLexer *pFileLexer = NULL;
    
    if (BURST_MIN_ARG_COUNT > argumentCount)
    {
        printf(BURST_NOT_ENOUGH_ARGS_MSG, BURST_MIN_ARG_COUNT, argumentCount);
        
        return BURST_NOT_ENOUGH_ARGS;
    }
    else if (BURST_MAX_ARG_COUNT < argumentCount)
    {
        printf(BURST_TOO_MANY_ARGS_MSG, BURST_MAX_ARG_COUNT, argumentCount);
        
        return BURST_TOO_MANY_ARGS;
    }
    
    // TODO: Create a command-line argument parser
    for (int argumentIndex = 0x1; argumentIndex < argumentCount; ++argumentIndex)
    {
        const char *pCurrentArgumentValue = *(ppArgumentValues + argumentIndex);
        
        printf("Current argument: %s\n", pCurrentArgumentValue);
        
        if (BURST_SUCCESS != lexer_create(pCurrentArgumentValue, &pFileLexer))
            return BURST_FAIL;
        
        if (BURST_SUCCESS != lexer_prepare(pFileLexer))
        {
            lexer_destroy(pFileLexer);
            
            return BURST_FAIL;
        }
        
        lexer_run(pFileLexer);
        lexer_destroy(pFileLexer);
    }
    
    return BURST_SUCCESS;
}