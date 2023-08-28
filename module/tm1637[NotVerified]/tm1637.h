/*
 * @Descripttion:
 * @version:
 * @Author: comestones
 * @Message: comestones@outlook.com
 * @Date: 2023-07-28 16:48:27
 * @LastEditTime: 2023-07-28 16:48:45
 */
#ifndef __tm1637_H
#define __tm1637_H

#include "main.h"

// 与库函数操作取一个
#define SDA_IN()                \
  {                             \
    GPIOA->CRL &= 0X0FFFFFFF;   \
    GPIOA->CRL |= (uint32_t)8 << 28; \
  } // 通过寄存器更改为输入
#define SDA_OUT()               \
  {                             \
    GPIOA->CRL &= 0X0FFFFFFF;   \
    GPIOA->CRL |= (uint32_t)3 << 28; \
  } // 通过寄存器更改为输出

#define TM_SCL_PORT GPIOB
#define TM_SCL_CLK RCC_APB2Periph_GPIOB
#define TM_SCL_PIN GPIO_PIN_8

#define TM_DIO_PORT GPIOB
#define TM_DIO_CLK RCC_APB2Periph_GPIOB
#define TM_DIO_PIN GPIO_PIN_9

#define TM_SCL(x) HAL_GPIO_WritePin(TM_SCL_PORT, TM_SCL_PIN, x ? GPIO_PIN_SET : GPIO_PIN_RESET)
#define TM_SDA(x) HAL_GPIO_WritePin(TM_DIO_PORT, TM_DIO_PIN, x ? GPIO_PIN_SET : GPIO_PIN_RESET)

#define READ_SDA HAL_GPIO_ReadPin(TM_DIO_PORT, TM_DIO_PIN)

void TM_Display(uint8_t *discode);
	
/*函数声明，这里省略，使用时请自加*/

#endif