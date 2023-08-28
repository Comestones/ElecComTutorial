/*
 * @Descripttion: 
 * @version: 
 * @Author: comestones
 * @Message: comestones@outlook.com
 * @Date: 2023-07-30 15:48:40
 * @LastEditTime: 2023-07-30 15:48:58
 */
#ifndef __DAC8563_H
#define __DAC8563_H

#include "main.h"
 
#define LDAC PCout(0)
#define CLR PCout(1)
#define SYNC PCout(2)
#define SCLK PCout(3)
#define DIN PCout(4)
/*Voltage Set*/
#define WrtirToInputReg_Command_DAC_A 0x18
#define WrtirToInputReg_Command_DAC_B 0x19
#define WrtirToInputReg_Command_DAC_AB 0x1F
/*Command Set*/
#define WrtirToInputReg_Command_DAC_AB_Gain_2 0x020000 //Normal Default
#define WrtirToInputReg_Command_DAC_B_Gain_2_A_Gain_1 0x020001
#define WrtirToInputReg_Command_DAC_B_Gain_1_A_Gain_2	0x020002
#define WrtirToInputReg_Command_DAC_B_Gain_1_A_Gain_1	0x020003 //Power_Down Default
#define WrtirToInputReg_Command_Reset_All_Regs 0x280001
#define WrtirToInputReg_Command_POWERUP_DAC_A_B 0x200003
#define WrtirToInputReg_Command_ENABLE_INTERNAL 0x380001

#define Max_Dac_Data 43254 //输出电压为3.3V
void DAC856x_GPIO_Init(void);
void DAC856x_Write_Data(uint8_t command,uint16_t data);
void DAC856x_Init(void);
void DAC856x_SetVoltage(uint8_t DAC_Channel,uint16_t Dac_Data);
#endif