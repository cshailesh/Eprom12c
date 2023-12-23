#include "CEEProm.h"

void CEProm_Init(CEProm *pClass, GPIO_TypeDef *pSCLPort, uint32_t pSCLPin, GPIO_TypeDef *pSDAPort, uint32_t pSDAPin, uint8_t pAddress)
{

	pClass->mI2c.mSCLPort = pSCLPort;
	pClass->mI2c.mSCLPin = pSCLPin;
	pClass->mI2c.mSDAPort = pSDAPort;
	pClass->mI2c.mSDAPin = pSDAPin;
	pClass->mI2c.mAddress = pAddress;
}

void CEProm_SetAddress(CEProm *pClass, uint8_t pAddress)
{

	pClass->mI2c.mAddress = pAddress;
}

void CEProm_ReadByte(CEProm *pClass, uint8_t pAddress, uint8_t *pByte)
{

	uint8_t res = 0;
	uint8_t cmd = 0x80;
	cmd = cmd | (pClass->mI2c.mAddress);

	CEProm_SetAddress(pClass, pAddress);
	CI2CEmu_Start(&pClass->mI2c);
	CI2CEmu_WriteByte(&pClass->mI2c, pClass->mI2c.mAddress);
	CI2CEmu_ReadByte(&pClass->mI2c, &res, 1);
	CI2CEmu_Stop(&pClass->mI2c);
	*pByte = res;
}

void CEProm_WriteByte(CEProm *pClass, uint8_t pAddress, uint8_t *pByte)
{
	uint8_t res = 0;
	uint8_t cmd = 0x08;
	cmd = cmd | (pClass->mI2c.mAddress);

	CEProm_SetAddress(pClass, pAddress);
	CI2CEmu_Start(&pClass->mI2c);
	CI2CEmu_WriteByte(&pClass->mI2c, cmd);
	CI2CEmu_WriteByte(&pClass->mI2c, *pByte);
	CI2CEmu_Stop(&pClass->mI2c);
	*pByte = res;
}
