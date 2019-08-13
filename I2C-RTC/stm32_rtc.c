#include "stm32_rtc.h"

// Dung chung ham xu ly loi voi file main
extern void Error_Handler(void);

// Dung chung bien cau truc I2C voi file main
extern I2C_HandleTypeDef hrtc;

//Chuyen tu ma BCD sang thap phan
unsigned char rtc_bcd2dec(unsigned char bcd)
{
		unsigned char highNible, lowNible;
    unsigned char dec;
    
    highNible = bcd >> 4;
    lowNible = bcd & 0x0F; // 0x0F = 0b00001111;
    dec = highNible*10 + lowNible;;
    return dec;
}	

//Chuyen tu thap sang sang ma BCD
unsigned char rtc_dec2bcd(unsigned char dec)
{
		unsigned char tens, unit;
    unsigned char bcd;
    
    tens = dec / 10;
    unit = dec % 10;
    bcd = (tens << 4) | unit;
    return bcd;
}	

// Ghi du lieu vao thanh ghi cua RTC
void rtc_write(unsigned char regAddr, unsigned char data)
{	
	unsigned char buff[8];
	buff[0] = regAddr;      // Register Address
	buff[1] = data;					// Data to write Register Address
	HAL_I2C_Master_Transmit(&hrtc, RTC_ADDR, buff, 2, 100);
	while(HAL_I2C_GetState(&hrtc) != HAL_I2C_STATE_READY);
}

// Doc du lieu tu thanh ghi cua RTC
unsigned char rtc_read(unsigned char regAddr)
{
	unsigned char buff[8];
	buff[0] = regAddr;
	HAL_I2C_Master_Transmit(&hrtc, RTC_ADDR, buff, 1, 100);
	while(HAL_I2C_GetState(&hrtc) != HAL_I2C_STATE_READY);
	
	HAL_I2C_Master_Receive(&hrtc, RTC_ADDR, buff, 1, 100);
	return buff[0];
}	

void rtc_setTime(unsigned char hrs, unsigned char min, unsigned char sec, unsigned char day, unsigned char dat, unsigned char mth, unsigned char yrs)
{
	unsigned char buff[8];
	buff[0] = RTC_SEC_ADDR;							// Dia chi thanh ghi bat dau doc
	buff[1] = rtc_dec2bcd(sec);
	buff[2] = rtc_dec2bcd(min);
	buff[3] = rtc_dec2bcd(hrs);
	buff[4] = rtc_dec2bcd(day);
	buff[5] = rtc_dec2bcd(dat);
	buff[6] = rtc_dec2bcd(mth);
	buff[7] = rtc_dec2bcd(yrs);	
	HAL_I2C_Master_Transmit(&hrtc, RTC_ADDR, buff, 8, 100);
	while(HAL_I2C_GetState(&hrtc) != HAL_I2C_STATE_READY);
}

// Doc gio phut giay
void rtc_getTime(unsigned char *hrs, unsigned char *min, unsigned char *sec, unsigned char *day, unsigned char *dat, unsigned char *mth, unsigned char *yrs)
{
	unsigned char buff[8];
	buff[0] = RTC_SEC_ADDR;
	HAL_I2C_Master_Transmit(&hrtc, RTC_ADDR, buff, 1, 100);
	while(HAL_I2C_GetState(&hrtc) != HAL_I2C_STATE_READY);	

	HAL_I2C_Master_Receive(&hrtc, RTC_ADDR, buff, 7, 100);
	*sec 	= rtc_bcd2dec(buff[0]);
	*min 	= rtc_bcd2dec(buff[1]);
	*hrs 	= rtc_bcd2dec(buff[2]);
	*day 	= rtc_bcd2dec(buff[3]);
	*dat 	= rtc_bcd2dec(buff[4]);
	*mth 	= rtc_bcd2dec(buff[5]);
	*yrs 	= rtc_bcd2dec(buff[6]);	
}

// Khoi tao ket noi cho rtc
void rtc_init(void)
{
	hrtc.Instance = I2C_RTC	;
  hrtc.Init.Timing = 0x2000090B;  // 100KHz
  hrtc.Init.OwnAddress1 = 0;
  hrtc.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hrtc.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hrtc.Init.OwnAddress2 = 0;
  hrtc.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hrtc.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hrtc.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter 
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hrtc, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter 
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hrtc, 0) != HAL_OK)
  {
    Error_Handler();
  }
}
