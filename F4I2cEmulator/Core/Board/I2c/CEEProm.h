#ifndef __C_EEPROM_H__
#define __C_EEPROM_H__


#include <main.h>
#include "CI2CEmu.h"

typedef struct 
{

    CI2CEmu mI2c

}CEProm;


void CEProm_Init(CEProm *pCeprom, GPIO_TypeDef *pSCLPort, uint32_t pSCLPin, GPIO_TypeDef *pSDAPort, uint32_t pSDAPin, uint8_t pAddress);
{

    pCeprom->mI2c.mSCLPort = pSCLPort;
    pCeprom->mI2c.mSCLPin = pSCLPin;
    pCeprom->mI2c.mSDAPort = pSDAPort;
    pCeprom->mI2c.mSDAPin = pSDAPin;
    pCeprom->mI2c.mAddress = pAddress;    
}


void CEProm_SetAddress(CEProm *pCeprom, uint8_t pAddress)
{

    pCeprom->mI2c.mAddress = pAddress;
}

void CEProm_ReadByte(CEProm *pCeprom, uint8_t pAddress, uint8_t *pByte)
{

    uint8_t res=0;
    CEProm_SetAddress(pCeprom, pAddress);
    CI2CEmu_Start(&pCeprom->mI2c);
    CI2CEmu_WriteByte(&pCeprom->mI2c, &pCeprom->mI2c.mAddress);
    CI2CEmu_ReadByte(&pCeprom->mI2c, &res);
    CI2CEmu_Stop(&pCeprom->mI2c);
    *pByte = res;
}




#endif
