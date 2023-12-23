#ifndef __C_EEPROM_H__
#define __C_EEPROM_H__


#include <main.h>
#include "CI2CEmu.h"

typedef struct 
{

    CI2CEmu mI2c

}CEProm;

void CEProm_Init(CEProm *pClass, GPIO_TypeDef *pSCLPort, uint32_t pSCLPin, GPIO_TypeDef *pSDAPort, uint32_t pSDAPin, uint8_t pAddress);
void CEProm_ReadByte(CEProm *pClass, uint8_t pAddress, uint8_t *pByte);
void CEProm_SetAddress(CEProm *pClass, uint8_t pAddress);
void CEProm_WriteByte(CEProm *pClass, uint8_t pAddress, uint8_t *pByte);


#endif
