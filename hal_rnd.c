#include "hal_board.h"
#include "hal_rnd.h"
#include "hal_types.h"

#define WRITE_RNDH(a) st(RNDH = a;)
#define WRITE_RNDL(a) st(RNDL = a;)
#define WRITE_CONFIG(a) st(ADCCON1 = a;)

#define READ_RNDH(a) st(a = RNDH;)
#define READ_RNDL(a) st(a = RNDL;)
#define READ_CONF(a) st(a = ADCCON1;)

#define MODE_NORMAL()       st(ADCCON1 &= ~(BV(3) | BV(2));)
#define MODE_ONE_CLOCK()    st(ADCCON1 &= BV(3); ADCCON1 |= BV(2);)
#define MODE_STOP()         st(ADCCON1 |= BV(3) | BV(2);)



void halGenerateRndBytes(uint8 * outBuf, uint8 number){

    if(number > 0){
        uint8 cntrl;
        MODE_ONE_CLOCK();
        for (uint8 i = 0; i < number; i += 2){
            MODE_ONE_CLOCK();
            while(cntrl != 0){
                READ_CONF(cntrl);
                cntrl = cntrl & 0x12;
            }
            READ_RNDL(outBuf[i]);
            READ_RNDH(outBuf[i+1]);
        }
    }
}

uint16 halGenerateRnd(){
    MODE_ONE_CLOCK();
    WRITE_RNDL(SEED_REFERENCE);
    WRITE_RNDL(SEED_REFERENCE);
    return BUILD_UINT16(RANDOM_DATA_LOW, RANDOM_DATA_HIGH);

}