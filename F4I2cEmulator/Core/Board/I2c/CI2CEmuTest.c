#include  "CI2CEmuTest.h"

void Test_I2c_Ex1()
{

    CI2CEmu data;
    CI2CEmu *i2c = &data;
    
    CI2CEmu_Init(i2c,EMEM_SCL_GPIO_Port,EMEM_SCL_Pin,EMEM_SDA_GPIO_Port,EMEM_SDA_Pin,1);
    CI2CEmu_SetDelays(i2c,20,10,20);

    while(1)
    {    
        Test_I2C_Write_Ex1(i2c,2,8);
        HAL_Delay(10);
    }
}

void Test_I2C_Write_Ex1(CI2CEmu *pI2c, uint8_t cmd, uint8_t data)
{
        CI2CEmu_Start(pI2c);
        CI2CEmu_WriteByte(pI2c,cmd);
        CI2CEmu_WriteByte(pI2c,data);
        CI2CEmu_Stop(pI2c);
}
