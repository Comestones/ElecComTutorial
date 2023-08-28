/*
 * @Descripttion:
 * @version:
 * @Author: comestones
 * @Message: comestones@outlook.com
 * @Date: 2023-07-28 16:47:09
 * @LastEditTime: 2023-07-28 16:49:38
 */
#include "tm1637.h"
#include "delay.h"

//void TM_Init(void)
//{
//    GPIO_InitTypeDef GPIO_InitStructure;

//    RCC_APB2PeriphClockCmd(TM_SDA_CLK | TM_SCL_CLK, ENABLE);

//    GPIO_InitStructure.GPIO_Pin = TM_SDA_PIN | TM_SCL_PIN;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init(TM_SDA_PORT, &GPIO_InitStructure);

//    //    TM_SCL=1;
//    //    TM_SDA=1;
//}

void TM_Start(void)
{
    TM_SDA(1);
    delay_us(2);
    TM_SCL(1);
    delay_us(2);
    TM_SDA(0);
    delay_us(2);
    TM_SCL(0);
    delay_us(2);
}

void TM_Stop(void)
{
    TM_SCL(0);
    delay_us(2);
    TM_SDA(0);
    delay_us(2);
    TM_SCL(1);
    delay_us(2);
    TM_SDA(1);
    delay_us(2);
}

void TM_Wait_Ask(void)
{
    SDA_IN();
    unsigned char i;
    TM_SCL(0);
    delay_us(5);
    while (READ_SDA == 1 && (i < 250)) //
        i++;
    TM_SCL(1);
    delay_us(2);
    TM_SCL(0);
    SDA_OUT();
}

void TM_WriteByte(uint8_t txd)
{
    uint8_t i;
    for (i = 0; i < 8; i++)
    {
        TM_SCL(0);
        delay_us(2);
        if (txd & 0x01)
        {
            TM_SDA(1);
        }
        else
        {
            TM_SDA(0);
        }
        delay_us(3);
        txd >>= 1;
        TM_SCL(1);
        delay_us(3);
    }
    // TM_Wait_Ask();
}

void TM_Display(uint8_t *discode)
{
    uint8_t i;

    TM_Start();
    TM_WriteByte(0x40); // 40 地址自加模式     44 固定地址模式
    TM_Wait_Ask();
    TM_Stop();

    TM_Start();
    TM_WriteByte(0xc0); // 首地址
    TM_Wait_Ask();

    for (i = 0; i < 4; i++)
    {
        TM_WriteByte(*(discode + i)); // 依次发送数组数据
        TM_Wait_Ask();
    }
    TM_Stop();

    TM_Start();
    TM_WriteByte(0x10); // 亮度
    TM_Wait_Ask();
    TM_Stop();
}