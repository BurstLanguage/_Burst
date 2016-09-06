//
// Burst
// Include/BurstUtilities.h
//
#ifndef __BURST_UTILITIES_H__
#define __BURST_UTILITIES_H__

#include <stdio.h>
#include <stdlib.h>

#ifdef _MSC_VER
static FILE *burst_fopen
(
    const char *pFilename, // IN
    const char *pMode      // IN
)
{
    FILE *pResult = NULL;
    
    fopen_s(&pResult, pFilename, pMode);
    
    return pResult;
}
#endif

#endif