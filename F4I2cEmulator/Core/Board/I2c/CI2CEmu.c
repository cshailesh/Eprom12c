#include "CI2CEmu.h"

void CI2CEmu_DelayUs(uint8_t pDelay)
{
	for (int i = 0; i < pDelay; ++i)
	{
		__NOP();
	}
}

void CI2CEmu_Init(CI2CEmu *pClass, GPIO_TypeDef *pSCLPort, uint32_t pSCLPin, GPIO_TypeDef *pSDAPort, uint32_t pSDAPin, uint8_t pAddress)
{

	memset(pClass, 0, sizeof(CI2CEmu));
	pClass->mSCLPort = pSCLPort;
	pClass->mSCLPin = pSCLPin;

	pClass->mSDAPort = pSDAPort;
	pClass->mSDAPin = pSDAPin;

	pClass->mAddress = pAddress;

}

void CI2CEmu_SetDelays(CI2CEmu *pClass, uint8_t pStartDelay, uint8_t pEndDelay, uint8_t pAckDelay)
{
	pClass->mStartDelay = pStartDelay;
	pClass->mEndDelay = pEndDelay;
	pClass->mAckDelay = pAckDelay;
}

void CI2CEmu_SetAddress(CI2CEmu *pI2CEmu, uint8_t pAddress)
{
	pI2CEmu->mAddress = pAddress;

}

void CI2CEmu_SetTxData(CI2CEmu *pI2CEmu, uint8_t *pData, uint8_t pSize)
{
	memcpy(pI2CEmu->mTxData, pData, pSize);
	pI2CEmu->mTxDataSize = pSize;
}

GPIO_InitTypeDef gTM_SDA_GPIO_Init;

void CI2CEmu_SetSdaMode(CI2CEmu *pI2CEmu, uint8_t pMode)
{

	GPIO_InitTypeDef *gpio_Init = &gTM_SDA_GPIO_Init;
	if (pMode == 0)
	{
		gpio_Init->Pin = pI2CEmu->mSDAPin;
		gpio_Init->Mode = GPIO_MODE_INPUT;
		gpio_Init->Speed = GPIO_SPEED_FREQ_HIGH;
		gpio_Init->Pull = GPIO_NOPULL;

	}
	else
	{
		gpio_Init->Pin = pI2CEmu->mSDAPin;
		gpio_Init->Mode = GPIO_MODE_OUTPUT_PP;
		gpio_Init->Speed = GPIO_SPEED_FREQ_HIGH;
		gpio_Init->Pull = GPIO_NOPULL;
	}

	HAL_GPIO_Init(pI2CEmu->mSDAPort, gpio_Init);

}

void CI2CEmu_Start(CI2CEmu *pI2CEmu)
{
	CI2CEmu_SetSdaMode(pI2CEmu, 1);
	CI2CEmu_DelayUs(pI2CEmu->mStartDelay);

	CI2CEmu_SDA_LOW();
	CI2CEmu_DelayUs(pI2CEmu->mStartDelay);

	CI2CEmu_SCL_LOW();
	CI2CEmu_DelayUs(pI2CEmu->mStartDelay);

}

void CI2CEmu_WriteByte(CI2CEmu *pI2CEmu, uint8_t pByte)
{
	for (char i = 0; i < 8; i++)
	{
		CI2CEmu_WriteBit(pI2CEmu, pByte & 128);
		pByte <<= 1;
	}
}

void CI2CEmu_ReadByte(CI2CEmu *pI2CEmu, uint8_t *pByte, uint8_t ack)
{

	CI2CEmu_SetSdaMode(pI2CEmu, 0);
	unsigned char res = 0;

	for (char i = 0; i < 8; i++)
	{
		res <<= 1;
		res |= CI2CEmu_ReadBit(pI2CEmu);
	}

	if (ack > 0)
	{
		CI2CEmu_SDA_HIGH();
	}
	else
	{
		CI2CEmu_SDA_LOW();
	}

	CI2CEmu_DelayUs(pI2CEmu->mEndDelay);

	CI2CEmu_SetSdaMode(pI2CEmu, 1);
	*pByte = res;

}

void CI2CEmu_Stop(CI2CEmu *pI2CEmu)
{
	CI2CEmu_SDA_HIGH();
	CI2CEmu_DelayUs(pI2CEmu->mEndDelay);
	CI2CEmu_SCL_HIGH();
	CI2CEmu_DelayUs(pI2CEmu->mEndDelay);
}

void CI2CEmu_WriteBit(CI2CEmu *pI2CEmu, uint8_t c)
{
	if (c > 0)
	{
		CI2CEmu_SDA_HIGH();
	}
	else
	{
		CI2CEmu_SDA_LOW();
	}

	CI2CEmu_DelayUs(pI2CEmu->mAckDelay);
	CI2CEmu_SCL_HIGH();
	CI2CEmu_DelayUs(pI2CEmu->mAckDelay);
	CI2CEmu_SCL_LOW();
	CI2CEmu_DelayUs(pI2CEmu->mAckDelay);

	if (c > 0)
	{
		CI2CEmu_SDA_LOW();
	}

	CI2CEmu_DelayUs(pI2CEmu->mAckDelay);

}

unsigned char CI2CEmu_ReadBit(CI2CEmu *pI2CEmu)
{

	CI2CEmu_SDA_HIGH();
	CI2CEmu_SCL_HIGH();
	CI2CEmu_DelayUs(pI2CEmu->mAckDelay);

	unsigned char c = CI2CEmu_SDA_READ();

	CI2CEmu_SCL_LOW();
	CI2CEmu_DelayUs(pI2CEmu->mAckDelay);
	return c;

}
