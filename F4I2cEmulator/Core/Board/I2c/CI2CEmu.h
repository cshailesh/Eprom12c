#ifndef __CI2CEMU_H__
#define __CI2CEMU_H__

#include <main.h>

// gpio emulator for I2C
#define d_I2C_EMULATOR_ADDRESS 0x50
#define d_I2C_EMULATOR_TX_DATA_SIZE 1
#define d_I2C_EMULATOR_RX_DATA_SIZE 1


#define CI2CEmu_SDA_HIGH()    HAL_GPIO_WritePin(pI2CEmu->mSDAPort, pI2CEmu->mSDAPin, GPIO_PIN_SET)
#define CI2CEmu_SCL_HIGH()        HAL_GPIO_WritePin(pI2CEmu->mSCLPort, pI2CEmu->mSCLPin, GPIO_PIN_SET)

#define CI2CEmu_SDA_LOW()    HAL_GPIO_WritePin(pI2CEmu->mSDAPort, pI2CEmu->mSDAPin, GPIO_PIN_RESET)
#define CI2CEmu_SCL_LOW()        HAL_GPIO_WritePin(pI2CEmu->mSCLPort, pI2CEmu->mSCLPin, GPIO_PIN_RESET)

#define CI2CEmu_SDA_READ()    HAL_GPIO_ReadPin(pI2CEmu->mSDAPort, pI2CEmu->mSDAPin)




typedef struct
{

	GPIO_TypeDef *mSCLPort;
	uint32_t mSCLPin;

	GPIO_TypeDef *mSDAPort;
	uint32_t mSDAPin;

    uint8_t mAddress;
    uint8_t mTxData[d_I2C_EMULATOR_TX_DATA_SIZE];
    uint8_t mTxDataSize;

    uint8_t mRxData[d_I2C_EMULATOR_RX_DATA_SIZE];
    uint8_t mRxDataSize;

    uint8_t mStartDelay;
    uint8_t mAckDelay;
    uint8_t mEndDelay;    

} CI2CEmu;

void CI2CEmu_DelayUs(uint8_t pDelay);

void CI2CEmu_Init(CI2CEmu *pI2CEmu, GPIO_TypeDef *pSCLPort, uint32_t pSCLPin, GPIO_TypeDef *pSDAPort, uint32_t pSDAPin, uint8_t pAddress);
void CI2CEmu_SetDelays(CI2CEmu *pI2CEmu, uint8_t pStartDelay, uint8_t pEndDelay, uint8_t pAckDelay);

void CI2CEmu_SetAddress(CI2CEmu *pI2CEmu, uint8_t pAddress);
void CI2CEmu_SetTxData(CI2CEmu *pI2CEmu, uint8_t *pData, uint8_t pSize);

void CI2CEmu_SetSdaMode(CI2CEmu *pI2CEmu, uint8_t pMode);

void CI2CEmu_WriteBit(CI2CEmu *pI2CEmu,uint8_t c);
unsigned char CI2CEmu_ReadBit(CI2CEmu *pI2CEmu);

void CI2CEmu_Start(CI2CEmu *pI2CEmu);
void CI2CEmu_Stop(CI2CEmu *pI2CEmu);

void CI2CEmu_WriteByte(CI2CEmu *pI2CEmu, uint8_t pByte);
void CI2CEmu_ReadByte(CI2CEmu *pI2CEmu, uint8_t *pByte,uint8_t ack);

void CI2CEmu_WriteByte(CI2CEmu *pI2CEmu, uint8_t pByte);
#endif
