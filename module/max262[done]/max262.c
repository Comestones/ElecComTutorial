/*
 * @Descripttion: max262
 * @version: v0.0
 * @Author: comestones
 * @Message: comestones@outlook.com
 * @Date: 2023-07-02 13:51:27
 * @LastEditTime: 2023-07-20 13:18:11
 */

#include "max262.h"

/**
 * @func: max262 initialize
 * @return {*}
 * @note: 
 */
void MAX262_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	MX_GPIO_Init();
}

/**
 * @func: write data to max262
 * @param {uint8_t} add
 * @param {uint8_t} dat2bit
 * @return {*}
 * @note: 
 */
void write(uint8_t add,uint8_t dat2bit)    
{   
	uint16_t data; 
	uint8_t i;  
//	data = HAL_GPIO_ReadPin(GPIOA);  
//	data = (data&0xfff0)|(add&0x000f);
//	data = (data&0xffcf)|((dat2bit<<8)&0x0030);
//	GPIO_Write(GPIOA,data);
	HAL_GPIO_WritePin(GPIOB, add, 1);
	resetWr;    
		for(i=0; i<255; i++);
	setWr;
		for(i=0; i<100; i++);
}

/**
 * @func: set channel A's F
 * @param {uint8_t} datF
 * @return {*}
 * @note: 
 */
void setAf(uint8_t datF)
{    
	write(1, datF);         
	datF = datF>>2;         
	write(2, datF);         
	datF = datF>>2;         
	write(3, datF);    
}

/**
 * @func: set channel A's Q
 * @param {uint8_t} datQ
 * @return {*}
 * @note: 
 */
void setAQ(uint8_t datQ)
{    
	write(4, datQ);         
	datQ = datQ>>2;         
	write(5, datQ);         
	datQ = datQ>>2;         
	write(6, datQ);         
	datQ = (datQ>>2)&1;   
	write(7, datQ);    
}

/**
 * @func: set channel B's F
 * @param {uint8_t} datF
 * @return {*}
 * @note: 
 */
void setBf(uint8_t datF)    
{    
  write(9, datF);        
	datF = datF>>2;       
	write(10, datF);      
	datF = datF>>2;       
	write(11, datF);    
} 
/**
 * @func: set channel B's Q 
 * @param {uint8_t} datQ
 * @return {*}
 * @note: 
 */
void setBQ(uint8_t datQ)    
{    
  write(12, datQ);         
	datQ = datQ>>2;        
	write(13, datQ);         
	datQ = datQ>>2;         
	write(14, datQ);    
  datQ = (datQ>>2)&1;
	write(15, datQ);    
}

/**
 * @func: calculate f0
 * @param {float} fc
 * @param {float} Q
 * @param {uint8_t} passMode
 * @return {*}
 * @note: 
 */
float lh_Getf0(float fc, float Q, uint8_t passMode) 
{    
  float temp; 
	temp = 1 - 0.5 / pow(Q,2);   //pow(Q, 2) ¼ÆËãQµÄ2´ÎÃÝ
	temp = sqrt(temp + sqrt(pow(temp, 2) + 1));  
	if(passMode == lowPass)  //µÍÍ¨ÖÐÐÄÆµÂÊ¼ÆËã¹«Ê½ 
		return  fc / temp;     
	else  //¸ßÍ¨ÖÐÐÄÆµÂÊ¼ÆËã¹«Ê½       
		return  fc * temp;
}

/**
 * @func: set f_clk of low_pass and high_pass filter
 * @param {float} fc
 * @param {float} Q
 * @param {uint8_t} passMode
 * @param {uint8_t} workMode
 * @param {uint8_t} channel
 * @return {*}
 * @note: 
 */
float lhp_WorkFclk(float fc,float Q,uint8_t passMode,uint8_t workMode,uint8_t channel)    
{       
	float f0;
	uint8_t Qn, Fn;
  f0 = lh_Getf0(fc, Q, passMode);  
  if (workMode == modeTwo)
		Qn = (uint8_t)(128 - 90.51 / Q);
	else
		Qn = (uint8_t)(128 - 64 / Q);
	if(passMode == highPass)
		workMode = modeThree;	
//	Fn = FnFin_config(f0, workMode);

	if(channel == channelA)       
	{
    write(0, workMode);         
		setAf(0);     
		setAQ(Qn);       
	}
	else 
  {
    write(8, workMode);         
		setBf(0);   
		setBQ(Qn);       
	}
  if(workMode==modeTwo)
		return  28.87872 * f0;//(Fn+26)*1.11072*f0;//31.46625*PI*f0;//31.46625-63   16.26361-20
	else
    return  40.84071 * f0;//(26+Fn)*PI/2*f0;//44.5*PI*f0;//44.5-63  23-20
}

/**
 * @func: set fclk of band pass filter
 * @param {float} fh
 * @param {float} fl
 * @param {uint8_t} workMode
 * @param {uint8_t} channel
 * @return {*}
 * @note: 
 */
float bp_WorkFclk(float fh, float fl,uint8_t workMode,uint8_t channel)    
{   
  float f0, Q;    
	uint8_t Qn, Fn; 
  f0 = sqrt(fh * fl);   
	Q = f0 / (fh - fl); 
 
	if (workMode == modeTwo)
		Qn = (uint8_t)(128 - 90.51 / Q);
	else
    Qn = (uint8_t)(128 - 64 / Q);
//	Fn = FnFin_config(f0, workMode);
	if(channel == channelA) 
	{
		write(0, workMode);         
		setAf(0);  //ÒªÏë»ñµÃ´ó·¶Î§¿Éµ÷£¬¿ª¹ØµçÈÝµÄ²ÉÑùÆµÂÊ²ÎÊýÈ¡×î´óÖµ. 
		setAQ(Qn); 
	}     
	else       
	{ 
    write(8, workMode);         
		setBf(0);     //ÒªÏë»ñµÃ´ó·¶Î§¿Éµ÷£¬¿ª¹ØµçÈÝµÄ²ÉÑùÆµÂÊ²ÎÊýÈ¡×î´óÖµ.         
		setBQ(Qn);       
	}   
	if(workMode == modeTwo)    
		return 28.87872 * f0;//(Fn+26)*1.11072*f0;//31.46625*PI*f0;
	else
    return 40.84071 * f0;//(26+Fn)*PI/2*f0;//44.5*PI*f0;
}

/**
 * @func: set fclk of band-stop filter
 * @param {float} f0
 * @param {float} Q
 * @param {uint8_t} workMode
 * @param {uint8_t} channel
 * @return {*}
 * @note: 
 */
float bs_WorkFclk(float f0,float Q,uint8_t workMode,uint8_t channel) 
{ 
	uint8_t Qn; 
  if (workMode == modeTwo)
		Qn = (uint8_t)(128 - 90.51 / Q);
	else
    Qn = (uint8_t)(128 - 64 / Q);
	if(channel == channelA)		
	{ 
    write(0, workMode);         
		setAf(63);  //ÒªÏë»ñµÃ´ó·¶Î§¿Éµ÷£¬¿ª¹ØµçÈÝµÄ²ÉÑùÆµÂÊ²ÎÊýÈ¡×î´óÖµ.         
		setAQ(Qn);       
	}     
	else      
	{ 
		write(8, workMode);         
		setBf(63);     //ÒªÏë»ñµÃ´ó·¶Î§¿Éµ÷£¬¿ª¹ØµçÈÝµÄ²ÉÑùÆµÂÊ²ÎÊýÈ¡×î´óÖµ.         
		setBQ(Qn);       
	}   
	if(workMode == modeTwo)
		return  31.46625 * PI * f0;
	else
    return  44.5 * PI * f0; 
}

/**
 * @func: set fclk of all-pole-filter
 * @param {float} f0
 * @param {float} Q
 * @param {uint8_t} channel
 * @return {*}
 * @note: 
 */
float ap_WorkFclk(float f0,float Q,uint8_t channel) 
{    
	uint8_t Qn; 
  Qn = (uint8_t)(128 - 64 / Q);   
  
	if(channel == channelA) 
  { 
    write(0, modeFour);         
		setAf(63);  //ÒªÏë»ñµÃ´ó·¶Î§¿Éµ÷£¬¿ª¹ØµçÈÝµÄ²ÉÑùÆµÂÊ²ÎÊýÈ¡×î´óÖµ.         
		setAQ(Qn);       
	}     
	else 
  { 
    write(8, modeFour);         
		setBf(63);     //ÒªÏë»ñµÃ´ó·¶Î§¿Éµ÷£¬¿ª¹ØµçÈÝµÄ²ÉÑùÆµÂÊ²ÎÊýÈ¡×î´óÖµ.         
		setBQ(Qn);       
	}
	return  44.5 * PI * f0; 
} 

/**
 * @func: set PWM clk
 * @param {uint32_t} f0
 * @return {*}
 * @note: 
 */
void PWM_Set(uint32_t f0)
{
	uint32_t arr_t;
	if(f0<10000)	//frequency = 10k Hz
	{
		TIM3->PSC = 720 - 1;
		arr_t = 100000 / f0;
		arr_t--;
		TIM3->ARR = arr_t;
		TIM3->CCR2 = arr_t / 2;
	}
	else
	{
		TIM3->PSC = 0;
		arr_t = 72000000 / f0;
		arr_t--;
		TIM3->ARR = arr_t;
		TIM3->CCR2 = arr_t / 2;
	}
}