/*
 * @Descripttion: ads1256 driver header file
 * @version: v0.0
 * @Author: comestones
 * @Message: comestones@outlook.com
 * @Date: 2023-07-04 18:35:20
 * @LastEditTime: 2023-07-20 12:54:20
 */

#ifndef _ads1256_H
#define _ads1256_H
#ifdef __cplusplus
extern "C"{
#endif

/*build in keil 5 version*/

#include "stdint.h"
#include "main.h"
#include "delay.h"
#include "usart.h"

#define REG_STATUS	(0)	// x1H		
#define	REG_MUX    	(1) // 01H		
#define	REG_ADCON   (2) // 20H		
#define	REG_DRATE   (3) // F0H		
#define	REG_IO      (4) // E0H		
#define	REG_OFC0    (5) // xxH		
#define	REG_OFC1    (6) // xxH		
#define	REG_OFC2    (7) // xxH		
#define	REG_FSC0    (8) // xxH		
#define	REG_FSC1    (9) // xxH		
#define	REG_FSC2    (10)// xxH		

#define	CMD_WAKEUP		(0x00)	// Completes SYNC and Exits Standby Mode 0000  0000 (00h)
#define	CMD_RDATA   	(0x01) 	// Read Data 0000  0001 (01h)		
#define	CMD_RDATAC  	(0x03) 	// Read Data Continuously 0000   0011 (03h)		
#define	CMD_SDATAC  	(0x0F) 	// Stop Read Data Continuously 0000   1111 (0Fh)	
#define	CMD_RREG    	(0x10) 	// Read from REG rrr 0001 rrrr (1xh)		
#define	CMD_WREG    	(0x50) 	// Write to REG rrr 0101 rrrr (5xh)		
#define	CMD_SELFCAL 	(0xF0) 	// Offset and Gain Self-Calibration 1111    0000 (F0h)	
#define	CMD_SELFOCAL	(0xF1) 	// Offset Self-Calibration 1111    0001 (F1h)	
#define	CMD_SELFGCAL	(0xF2) 	// Gain Self-Calibration 1111    0010 (F2h)		
#define	CMD_SYSOCAL 	(0xF3) 	// System Offset Calibration 1111   0011 (F3h)	
#define	CMD_SYSGCAL 	(0xF4) 	// System Gain Calibration 1111    0100 (F4h)
#define	CMD_SYNC    	(0xFC) 	// Synchronize the A/D Conversion 1111   1100 (FCh)
#define	CMD_STANDBY 	(0xFD) 	// Begin Standby Mode 1111   1101 (FDh)	
#define	CMD_RESET   	(0xFE) 	// Reset to Power-Up Values 1111   1110 (FEh)

#define PGA_1            0x00
#define PGA_2            0x01
#define PGA_4            0x02
#define PGA_8            0x03
#define PGA_16           0x04
#define PGA_32           0x05
#define PGA_64           0x06

#define POSITIVE_AIN0       (0X00)
#define POSITIVE_AIN1       (0X10)
#define POSITIVE_AIN2       (0X20)
#define POSITIVE_AIN3       (0X30)
#define POSITIVE_AIN4       (0X40)
#define POSITIVE_AIN5       (0X50)
#define POSITIVE_AIN6       (0X60)
#define POSITIVE_AIN7       (0X70)
#define POSITIVE_AINCOM     (0X80)        

#define NEGTIVE_AIN0         0X00
#define NEGTIVE_AIN1         0X01
#define NEGTIVE_AIN2         0X02
#define NEGTIVE_AIN3         0X03
#define NEGTIVE_AIN4         0X04
#define NEGTIVE_AIN5         0X05
#define NEGTIVE_AIN6         0X06
#define NEGTIVE_AIN7         0X07
#define NEGTIVE_AINCOM       0X08

#define DATARATE_30K         0xF0
#define DATARATE_15K         0xE0
#define DATARATE_7_5K        0xD0
#define DATARATE_3_7_5K      0xC0
#define DATARATE_2K          0xB0
#define DATARATE_1K          0xA0
#define DATARATE_500         0x92
#define DATARATE_100         0x82
#define DATARATE_60        	 0x72
#define DATARATE_50        	 0x63
#define DATARATE_30        	 0x53
#define DATARATE_25        	 0x43
#define DATARATE_15        	 0x33
#define DATARATE_10        	 0x23
#define DATARATE_5        	 0x13
#define DATARATE_2_5     	 0x02

#define	RST				(GPIOB,GPIO_PIN_3)
#define RST_L			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,0)
#define RST_H			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,1)

#define	CS				(GPIOB,GPIO_PIN_5)
#define	CS_L			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,0)
#define	CS_H			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,1)

#define	DRDY			(GPIOB,GPIO_PIN_4)
#define	DRDY_L		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,0)
#define	DRDY_H		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,1)
#define DRDY_IS_L	(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4) == GPIO_PIN_RESET)

#define	DOUT			(GPIOB,GPIO_PIN_7)
#define	DOUT_L		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,0)
#define	DOUT_H		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,1)
#define DO_IS_H		(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_7) == GPIO_PIN_SET)

#define	DIN				(GPIOB,GPIO_PIN_6)
#define	DIN_L			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,0)
#define	DIN_H			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,1)

#define	SCLK			(GPIOB,GPIO_PIN_8)
#define	SCLK_L		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,0)
#define	SCLK_H		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,1)

///*STATUS REGISTER*/
//#define MSB_FRIST                (0x00<<3)
//#define LSB_FRIST                (0x01<<3)
//#define ACAL_OFF                 (0x00<<2)
//#define ACAL_ON                  (0x01<<2)
//#define BUFEN_OFF                (0x00<<1)
//#define BUFEN_ON                 (0x01<<1)

///*ADCON REGISTER*/
//#define CLKOUT_OFF               (0x00<<5)
//#define CLKOUT_CLKIN             (0x01<<5)
//#define DETECT_OFF               (0x00<<3)
//#define DETECT_ON_2UA            (0x02<<3)

void ADS1256_Init(void);
extern void ADS1256_Send8Bit(uint8_t data);
extern uint8_t ADS1256_Recive8Bit(void);
extern void ADS1256_WriteReg(uint8_t RegID, uint8_t RegValue);
extern uint8_t ADS1256_ReadReg(uint8_t _RegID);
extern void ADS1256_WriteCmd(uint8_t cmd);
extern uint32_t ADS1256_ReadData(void);
extern uint32_t ADS1256_GetAdc(uint8_t channel);
extern void ADS1256_CfgADC(uint8_t gain, uint8_t drate);
static void ADS1256_DelaySCLK(void);
static void ADS1256_DelayDATA(void);
static void ADS1256_ResetHard(void);
static void ADS1256_SetChannal(uint8_t _ch);
static void ADS1256_SetDiffChannal(uint8_t _ch);
void ADS1256_WaitDRDY(void);
uint8_t ADS1256_ReadChipID(void);

#ifdef __cplusplus
}
#endif

#endif