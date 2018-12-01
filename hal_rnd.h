#ifndef HAL_RND_H
#define HAL_RND_H


#ifdef __cplusplus
extern "C"
{

#endif


#include "hal_types.h"
#include "hal_board.h"

#define RANDOM_DATA_LOW         RNDL
#define RANDOM_DATA_HIGH        RNDH
#define RND_GENERATION_CONTROL  ADCCON1

#define SEED_REFERENCE          0x13


void halGenerateRndBytes(uint8 * outBuf, uint8 number);
uint16 halGenerateRnd();

#ifdef __cplusplus
}
#endif


#endif