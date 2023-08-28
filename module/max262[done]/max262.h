/*
 * @Descripttion: max262
 * @version: v0.0
 * @Author: comestones
 * @Message: comestones@outlook.com
 * @Date: 2023-07-02 13:51:36
 * @LastEditTime: 2023-07-20 12:57:39
 */

#ifndef _max262_H_
#define _max262_H_
#ifdef __cplusplus
extern "C"{
#endif

#include "main.h"
#include <math.h> 
#include "gpio.h"

#define PI 3.141592653
#define setWr      HAL_GPIO_WritePin(GPIOA,6,1)
#define resetWr    HAL_GPIO_WritePin(GPIOA,6,0)

// #define fclkk PAout(1)
// #define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)
// #define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)
// #define BITBAND(addr, bitnum)			((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
// #define MEM_ADDR(addr)					*((volatile unsigned long  *)(addr)) 
// #define BIT_ADDR(addr, bitnum)			MEM_ADDR(BITBAND(addr, bitnum))

extern enum {modeOne = 0, modeTwo, modeThree, modeFour} workMode;
extern enum {lowPass = 0, highPass, bandPass, allPass, bandStop} passMode; 
extern enum {channelA = 0, channelB} channel;

void MAX262_Init(void);  
void write(uint8_t add,uint8_t dat2bit); 
void setAf(uint8_t datF);
void setAQ(uint8_t datQ);
void setBf(uint8_t datF);    
void setBQ(uint8_t datQ);

float lh_Getf0(float fc,float Q,uint8_t passMode); 
float lhp_WorkFclk(float fc,float Q,uint8_t passMode,uint8_t workMode,uint8_t channel);
float bp_WorkFclk(float fh,float fl,uint8_t workMode,uint8_t channel); 
float bs_WorkFclk(float f0,float Q,uint8_t workMode,uint8_t channel);
float ap_WorkFclk(float f0,float Q,uint8_t channel);

#ifdef __cplusplus
}
#endif

#endif