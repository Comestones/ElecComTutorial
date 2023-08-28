#ifndef __AD9910_H__
#define __AD9910_H__
#ifdef __cplusplus
extern "C" {
#endif
#include "main.h"

#define AD9910_PF1(x) HAL_GPIO_WritePin(AD9910_PF1_GPIO_Port, AD9910_PF1_Pin, x ? GPIO_PIN_SET : GPIO_PIN_RESET)
#define AD9910_PF2(x) HAL_GPIO_WritePin(AD9910_PF2_GPIO_Port, AD9910_PF2_Pin, x ? GPIO_PIN_SET : GPIO_PIN_RESET)
#define AD9910_PF0(x) HAL_GPIO_WritePin(AD9910_PF0_GPIO_Port, AD9910_PF0_Pin, x ? GPIO_PIN_SET : GPIO_PIN_RESET)
#define AD9910_DRC(x) HAL_GPIO_WritePin(AD9910_DRC_GPIO_Port, AD9910_DRC_Pin, x ? GPIO_PIN_SET : GPIO_PIN_RESET)
#define AD9910_DRO(x) HAL_GPIO_WritePin(AD9910_DRO_GPIO_Port, AD9910_DRO_Pin, x ? GPIO_PIN_SET : GPIO_PIN_RESET)
#define AD9910_UP(x) HAL_GPIO_WritePin(AD9910_UP_GPIO_Port, AD9910_UP_Pin, x ? GPIO_PIN_SET : GPIO_PIN_RESET)
#define AD9910_SCK(x) HAL_GPIO_WritePin(AD9910_SCK_GPIO_Port, AD9910_SCK_Pin, x ? GPIO_PIN_SET : GPIO_PIN_RESET)
#define AD9910_SDI(x) HAL_GPIO_WritePin(AD9910_SDI_GPIO_Port, AD9910_SDI_Pin, x ? GPIO_PIN_SET : GPIO_PIN_RESET)
#define AD9910_MRT(x) HAL_GPIO_WritePin(AD9910_MRT_GPIO_Port, AD9910_MRT_Pin, x ? GPIO_PIN_SET : GPIO_PIN_RESET)
#define AD9910_CS(x) HAL_GPIO_WritePin(AD9910_CS_GPIO_Port, AD9910_CS_Pin, x ? GPIO_PIN_SET : GPIO_PIN_RESET)

void AD9910_Init(void);
void AD9910_Send(uint8_t channel, uint8_t change);
void AD9910_SendProfile(void);
void AD9910_SendRAM_Profile(void);
void AD9910_SendRAM(uint32_t length);
void AD9910_SendCtrl(void);
void AD9910_SetTriangle(uint32_t Sample_interval);
void AD9910_SetSquare(uint32_t Sample_interval);
void AD9910_SetAmp(float Amp);
void AD9910_SetFreq(int Fre);
void AD9910_Set(uint32_t Freq, float Amp);
void AD9910_WriteByte(uint8_t tx_dat);
#define CFR1_Addr 0x00
#define CFR2_Addr 0x01
#define CFR3_Addr 0x02


#ifdef __cplusplus
}
#endif

#endif