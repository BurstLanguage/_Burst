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
    
    return BURST_SUCCESS;
}