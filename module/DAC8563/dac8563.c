/*
 * @Descripttion:
 * @version:
 * @Author: comestones
 * @Message: comestones@outlook.com
 * @Date: 2023-07-30 15:48:28
 * @LastEditTime: 2023-07-30 15:53:54
 */
#include "dac8563.h"

void DAC856x_Init(void)
{
  // 将CLR,SYNC拉高
  GPIO_SetBits(GPIOC, GPIO_Pin_2);
  GPIO_SetBits(GPIOC, GPIO_Pin_0);
  // 将时钟拉低，CLR拉高
  GPIO_ResetBits(GPIOC, GPIO_Pin_3);
  GPIO_ResetBits(GPIOC, GPIO_Pin_1);
  // 初始化配置
  DAC856x_Write_Data((WrtirToInputReg_Command_Reset_All_Regs >> 16), (WrtirToInputReg_Command_Reset_All_Regs & 0xFFFF));   // 复位
  DAC856x_Write_Data((WrtirToInputReg_Command_POWERUP_DAC_A_B >> 16), (WrtirToInputReg_Command_POWERUP_DAC_A_B & 0xFFFF)); // 启动
  DAC856x_Write_Data((WrtirToInputReg_Command_ENABLE_INTERNAL >> 16), (WrtirToInputReg_Command_ENABLE_INTERNAL & 0xFFFF)); // 选用内部参考电压
}
void DAC856x_Write_Data(uint8_t command, uint16_t data)
{
  int i;
  SYNC = 1;
  delay_us(1);
  SYNC = 0;
  for (i = 7; i >= 0; i--) // 写入指令与地址
  {
    SCLK = 1;
    delay_us(10);
    DIN = (command >> i) % 2;
    delay_us(10);
    SCLK = 0;
    delay_us(10);
  }
  for (i = 15; i >= 0; i--) // 写入相应的数据
  {
    SCLK = 1;
    delay_us(10);
    DIN = (data >> i) % 2;
    delay_us(10);
    SCLK = 0;
    delay_us(10);
  }
}


void DAC856x_SetVoltage(uint8_t DAC_Channel, uint16_t Dac_Data)
{
  if (DAC_Channel == WrtirToInputReg_Command_DAC_A)
  {
    if (Dac_Data <= Max_Dac_Data)
      DAC856x_Write_Data(WrtirToInputReg_Command_DAC_A, Dac_Data);
    else
      DAC856x_Write_Data(WrtirToInputReg_Command_DAC_A, Max_Dac_Data);
  }
  if (DAC_Channel == WrtirToInputReg_Command_DAC_B)
  {
    if (Dac_Data <= Max_Dac_Data)
      DAC856x_Write_Data(WrtirToInputReg_Command_DAC_B, Dac_Data);
    else
      DAC856x_Write_Data(WrtirToInputReg_Command_DAC_B, Max_Dac_Data);
  }
  if (DAC_Channel == WrtirToInputReg_Command_DAC_AB)
  {
    if (Dac_Data <= Max_Dac_Data)
      DAC856x_Write_Data(WrtirToInputReg_Command_DAC_AB, Dac_Data);
    else
      DAC856x_Write_Data(WrtirToInputReg_Command_DAC_AB, Max_Dac_Data);
  }
  LDAC = 0;
  delay_us(100);
  LDAC = 1;
}