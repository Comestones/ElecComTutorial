/*
 * @Descripttion: module ads1256 c file
 * @version: v0.0
 * @Author: comestones
 * @Message: comestones@outlook.com
 * @Date: 2023-07-04 18:35:20
 * @LastEditTime: 2023-07-20 12:54:37
 */

#include "ads1256.h"

/**
 * @func: ads1256 initialization
 * @return {*}
 * @note: 
 */
void ADS1256_Init(void)
{
	RST_L;
	delay_ms(1);
	RST_H;
	delay_ms(100);
	CS_H;
	SCLK_L;
	DIN_H;
}
/**
 * @func: send data
 * @param {uint8_t} data
 * @return {*}
 * @note: basic
 */
void ADS1256_Send8Bit(uint8_t data)
{
	uint8_t i;
	ADS1256_DelaySCLK();
	ADS1256_DelaySCLK();
	for(i = 0; i < 8; i++)
	{
		if (data & 0x80)
			DIN_H;
		else
			DIN_L;
		SCLK_H;
		ADS1256_DelaySCLK();
		data <<= 1;
		SCLK_L;
		ADS1256_DelaySCLK();
	}
}
/**
 * @func: receive data
 * @return {*}
 * @note: 
 */
uint8_t ADS1256_Recive8Bit(void)
{
	uint8_t i;
	uint8_t read = 0;

  ADS1256_DelaySCLK();
	/*¡¡ADS1256 ÒªÇó SCL¸ßµçÆ½ºÍµÍµçÆ½³ÖÐøÊ±¼ä×îÐ¡ 200ns  */
	for (i = 0; i < 8; i++)
	{
		SCLK_H;
		ADS1256_DelaySCLK();
		read = read<<1;
		SCLK_L;
		if (DO_IS_H)
			read++;
		ADS1256_DelaySCLK();
	}
	return read;
}
/**
 * @func: send data to register
 * @param {uint8_t} RegID
 * @param {uint8_t} RegValue
 * @return {*}
 * @note: 
 */
void ADS1256_WriteReg(uint8_t RegID, uint8_t RegValue)
{
	CS_L;
	ADS1256_Send8Bit(CMD_WREG| RegID);
	ADS1256_Send8Bit(0x00);
	ADS1256_Send8Bit(RegValue);
	CS_H;
}
/**
 * @func: read the data from regisiter
 * @param {uint8_t} _RegID
 * @return {uint8_t} read
 * @note: 
 */
uint8_t ADS1256_ReadReg(uint8_t _RegID)
{
	uint8_t read;
	CS_L;
	ADS1256_Send8Bit(CMD_RREG | _RegID);
	ADS1256_Send8Bit(0x00);
  ADS1256_DelayDATA();
	read = ADS1256_Recive8Bit();
	CS_H;
	return read;
}
/**
 * @func: write command
 * @param {uint8_t} cmd
 * @return {*}
 * @note: 
 */
void ADS1256_WriteCmd(uint8_t cmd)
{
	CS_L;
	ADS1256_Send8Bit(cmd);
	CS_H;
}
/**
 * @func: adc configeration
 * @param {uint8_t} gain
 * @param {uint8_t} drate
 * @return {*}
 * @note: 
 */
void ADS1256_CfgADC(uint8_t gain,uint8_t drate)   
{
	ADS1256_WriteCmd(CMD_RESET); 
	ADS1256_WriteReg(REG_STATUS,0XF4); 
	ADS1256_WriteCmd(CMD_SELFCAL);
	ADS1256_ResetHard();
	ADS1256_WaitDRDY();
	{
		uint8_t buf[4];
		/* 	Bits 7-4 ID3, ID2, ID1, ID0  Factory Programmed Identification Bits (Read Only)

			Bit 3 ORDER: Data Output Bit Order
				0 = Most Significant Bit First (default)
				1 = Least Significant Bit First
			Input data  is always shifted in most significant byte and bit first. Output data is always shifted out most significant
			byte first. The ORDER bit only controls the bit order of the output data within the byte.

			Bit 2 ACAL : Auto-Calibration
				0 = Auto-Calibration Disabled (default)
				1 = Auto-Calibration Enabled
			When Auto-Calibration is enabled, self-calibration begins at the completion of the WREG command that changes
			the PGA (bits 0-2 of ADCON register), DR (bits 7-0 in the DRATE register) or BUFEN (bit 1 in the STATUS register)
			values.

			Bit 1 BUFEN: Analog Input Buffer Enable
				0 = Buffer Disabled (default)
				1 = Buffer Enabled

			Bit 0 DRDY :  Data Ready (Read Only)
				This bit duplicates the state of the DRDY pin.

			ACAL=1Ê¹ÄÜ×ÔÐ£×¼¹¦ÄÜ¡£µ± PGA£¬BUFEEN, DRATE¸Ä±äÊ±»áÆô¶¯×ÔÐ£×¼
		*/
		buf[0] = (0 << 3) | (1 << 2) | (0 << 1);

		buf[1] = 0x08;
		/*	ADCON: A/D Control Register (Address 02h)
			Bit 7 Reserved, always 0 (Read Only)
			Bits 6-5 CLK1, CLK0 : D0/CLKOUT Clock Out Rate Setting
				00 = Clock Out OFF
				01 = Clock Out Frequency = fCLKIN (default)
				10 = Clock Out Frequency = fCLKIN/2
				11 = Clock Out Frequency = fCLKIN/4
				When not using CLKOUT, it is recommended that it be turned off. These bits can only be reset using the RESET pin.

			Bits 4-2 SDCS1, SCDS0: Sensor Detect Current Sources
				00 = Sensor Detect OFF (default)
				01 = Sensor Detect Current = 0.5 ¦Ì A
				10 = Sensor Detect Current = 2 ¦Ì A
				11 = Sensor Detect Current = 10¦Ì A
				The Sensor Detect Current Sources can be activated to verify  the integrity of an external sensor supplying a signal to the
				ADS1255/6. A shorted sensor produces a very small signal while an open-circuit sensor produces a very large signal.

			Bits 2-0 PGA2, PGA1, PGA0: Programmable Gain Amplifier Setting
				000 = 1 (default)
				001 = 2
				010 = 4
				011 = 8
				100 = 16
				101 = 32
				110 = 64
				111 = 64
		*/
		buf[2] = (0 << 5) | (0 << 3) | (gain << 0);//Ê±ÖÓ¹Ø±Õ£¬ÔöÒæ±¶ÊýÎª1
		
		buf[3] = drate;	// DRATE_10SPS;
		CS_L;
		ADS1256_Send8Bit(CMD_WREG|0);          
		ADS1256_Send8Bit(0x03);                
		ADS1256_Send8Bit(buf[0]);              
		ADS1256_Send8Bit(buf[1]);              
		ADS1256_Send8Bit(buf[2]);              
		ADS1256_Send8Bit(buf[3]);	           
		CS_H;
	}
	delay_us(50);
}
/**
 * @func: ads1256 read adc data
 * @return {*}
 * @note: 
 */
uint32_t ADS1256_ReadData(void)
{
	uint32_t read = 0;
	CS_L;
	ADS1256_Send8Bit(CMD_RDATA);
	ADS1256_DelayDATA();
	read = (uint32_t)ADS1256_Recive8Bit() << 16;
	read += ((uint32_t)ADS1256_Recive8Bit() << 8);
	read += ADS1256_Recive8Bit();
	if (read & 0x800000)
	{
		read += 0xFF000000;
	}
	CS_H;
	return read;
}
/**
 * @func: ads1256 gets the adc data 
 * @param {uint8_t} channel
 * @return {*}
 * @note: 
 */
uint32_t ADS1256_GetAdc(uint8_t channel)
{
	uint32_t read;
	read = 0;
// 	while(DRDY);
	ADS1256_WriteReg(REG_MUX,channel);
	ADS1256_WriteCmd(CMD_SYNC);
// 	Delay_1us(1);
	ADS1256_WriteCmd(CMD_WAKEUP);
	while(!DRDY_IS_L);                          
 	read = 	ADS1256_ReadData();
	return read;	
}

#if 0
/**
 * @func: read the adc data
 * @param {uint8_t} _ch
 * @return {*}
 * @note: 
 */
int32_t ADS1256_ReadAdc(uint8_t _ch)
{

#if 0
	int32_t read;
	while (DRDY_IS_L);
	while (!DRDY_IS_L);
	ADS1256_SetChannal(_ch);
	delay_us(5);
	ADS1256_WriteCmd(CMD_SYNC);
	delay_us(5);
	ADS1256_WriteCmd(CMD_WAKEUP);
	delay_us(25);
	read =  (int32_t)ADS1256_ReadData();
	while (DRDY_IS_LOW());
	while (!DRDY_IS_LOW());
	read =  (int32_t)ADS1256_ReadData();
	return read;
#else
	//while (DRDY_IS_LOW());
	ADS1256_WaitDRDY();
	ADS1256_SetChannal(_ch);
	delay_us(5);
	ADS1256_WriteCmd(CMD_SYNC);
	delay_us(5);

	ADS1256_WriteCmd(CMD_WAKEUP);
	delay_us(25);

	//ADS1256_WaitDRDY();

	return (int32_t)ADS1256_ReadData();
#endif
}
#endif
static void ADS1256_DelaySCLK(void)
{
	uint16_t i;
	for (i = 0; i < 10; i++);
}
static void ADS1256_DelayDATA(void)
{
	delay_us(10);
}
static void ADS1256_ResetHard(void)
{
	//RESET_0();
	//bsp_DelayUS(5);
	//RESET_1();

	//PWDN_0();	
	//bsp_DelayUS(2);
	//PWDN_1();	

	delay_us(5);

	//ADS1256_WaitDRDY();
}
static void ADS1256_SetChannal(uint8_t _ch)
{
	/*
	Bits 7-4 PSEL3, PSEL2, PSEL1, PSEL0: Positive Input Channel (AINP) Select
		0000 = AIN0 (default)
		0001 = AIN1
		0010 = AIN2 (ADS1256 only)
		0011 = AIN3 (ADS1256 only)
		0100 = AIN4 (ADS1256 only)
		0101 = AIN5 (ADS1256 only)
		0110 = AIN6 (ADS1256 only)
		0111 = AIN7 (ADS1256 only)
		1xxx = AINCOM (when PSEL3 = 1, PSEL2, PSEL1, PSEL0 are ¡°don¡¯t care¡±)

		NOTE: When using an ADS1255 make sure to only select the available inputs.

	Bits 3-0 NSEL3, NSEL2, NSEL1, NSEL0: Negative Input Channel (AINN)Select
		0000 = AIN0
		0001 = AIN1 (default)
		0010 = AIN2 (ADS1256 only)
		0011 = AIN3 (ADS1256 only)
		0100 = AIN4 (ADS1256 only)
		0101 = AIN5 (ADS1256 only)
		0110 = AIN6 (ADS1256 only)
		0111 = AIN7 (ADS1256 only)
		1xxx = AINCOM (when NSEL3 = 1, NSEL2, NSEL1, NSEL0 are ¡°don¡¯t care¡±)
	*/
	if (_ch > 7)
	{
		return;
	}
	ADS1256_WriteReg(REG_MUX, (_ch << 4) | (1 << 3));
}
static void ADS1256_SetDiffChannal(uint8_t _ch)
{
	/*
	Bits 7-4 PSEL3, PSEL2, PSEL1, PSEL0: Positive Input Channel (AINP) Select
		0000 = AIN0 (default)
		0001 = AIN1
		0010 = AIN2 (ADS1256 only)
		0011 = AIN3 (ADS1256 only)
		0100 = AIN4 (ADS1256 only)
		0101 = AIN5 (ADS1256 only)
		0110 = AIN6 (ADS1256 only)
		0111 = AIN7 (ADS1256 only)
		1xxx = AINCOM (when PSEL3 = 1, PSEL2, PSEL1, PSEL0 are ¡°don¡¯t care¡±)

		NOTE: When using an ADS1255 make sure to only select the available inputs.

	Bits 3-0 NSEL3, NSEL2, NSEL1, NSEL0: Negative Input Channel (AINN)Select
		0000 = AIN0
		0001 = AIN1 (default)
		0010 = AIN2 (ADS1256 only)
		0011 = AIN3 (ADS1256 only)
		0100 = AIN4 (ADS1256 only)
		0101 = AIN5 (ADS1256 only)
		0110 = AIN6 (ADS1256 only)
		0111 = AIN7 (ADS1256 only)
		1xxx = AINCOM (when NSEL3 = 1, NSEL2, NSEL1, NSEL0 are ¡°don¡¯t care¡±)
	*/
	if (_ch == 0)
	{
		ADS1256_WriteReg(REG_MUX, (0 << 4) | 1);	/* ²î·ÖÊäÈë AIN0£¬ AIN1 */
	}
	else if (_ch == 1)
	{
		ADS1256_WriteReg(REG_MUX, (2 << 4) | 3);	/* ²î·ÖÊäÈë AIN2£¬ AIN3 */
	}
	else if (_ch == 2)
	{
		ADS1256_WriteReg(REG_MUX, (4 << 4) | 5);	/* ²î·ÖÊäÈë AIN4£¬ AIN5 */
	}
	else if (_ch == 3)
	{
		ADS1256_WriteReg(REG_MUX, (6 << 4) | 7);	/* ²î·ÖÊäÈë AIN6£¬ AIN7 */
	}
}
/**
 * @func: DRDY waiting data
 * @return {*}
 * @note: 
 */
void ADS1256_WaitDRDY(void)
{
	uint32_t i;

	for (i = 0; i < 40000000; i++)
	{
		if (DRDY_IS_L)
		{
			break;
		}
	}
	if (i >=40000000)
	{
		printf("\r\n connecting \r\n");
	}
}
/**
 * @func: read ads1256 id
 * @return {*}
 * @note: 
 */
uint8_t ADS1256_ReadChipID(void)
{
	uint8_t id;

	ADS1256_WaitDRDY();
	id = ADS1256_ReadReg(REG_STATUS);
	return (id >> 4);
}