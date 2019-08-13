#ifndef __STM32_RTC_H
#define __STM32_RTC_H

#ifdef __cplusplus
extern "C" {
#endif

// Them header cua dong chip dang su dung
//#include "stm32f1xx_hal.h"			// <== Dung chip STM32F1
#include "stm32f3xx_hal.h" 				// <== Dung chip STM32F3
//#include "stm32f4xx_hal.h"			// <== Dung chip STM32F4
//#include "stm32l0xx_hal.h"			// <== Dung chip STM32L0

/* --------- Sua kenh I2C ket noi voi RTC --------- */ 		
/*																									*/
#define I2C_RTC		I2C2  // <== Chon kenh I2C				 /
#define	hrtc			hi2c2 // <== Chon kenh I2C				 /
/*																									*/
/* -------------------------------------- --------- */ 
	
// Dinh nghia dia chi cua thiet bi
#define RTC_ADDR					(0x68 << 1) // 0xD0

// Dinh nghia dia chi cua thanh ghi
#define RTC_SEC_ADDR     0x00    // Dia chi thang ghi giay 
#define RTC_MIN_ADDR     0x01    // Dia chi thang ghi phut   
#define RTC_HRS_ADDR     0x02    // Dia chi thang ghi gio  
#define RTC_DAY_ADDR     0x03    // Dia chi thang ghi thu  
#define RTC_DAT_ADDR     0x04    // Dia chi thang ghi ngay  
#define RTC_MTH_ADDR     0x05    // Dia chi thang ghi thang  
#define DRTC_YRS_ADDR    0x06    // Dia chi thang ghi nam 

#ifdef DS1307
	#define RTC_CTR_ADDR     0x07    // Dia chi thang ghi dieu khien 
	#define RTC_RAM_ADDR     0x08    // Dia chi thang ghi RAM (0x08 - 0x3F)
#elif	DS3231
	#define RTC_ALM1_SEC_ADDR     0x07    // Dia chi thang ghi bao giay 1
	#define RTC_ALM1_MIN_ADDR     0x08    // Dia chi thang ghi bao phut 1
	#define RTC_ALM1_HRS_ADDR     0x09    // Dia chi thang ghi bao gio 1
	#define RTC_ALM1_DYDT_ADDR    0x0A    // Dia chi thang ghi bao thu va ngay 1
	
	#define RTC_ALM2_MIN_ADDR     0x0B    // Dia chi thang ghi bao phut 2
	#define RTC_ALM2_HRS_ADDR     0x0C    // Dia chi thang ghi bao gio 2
	#define RTC_ALM2_DYDT_ADDR    0x0D    // Dia chi thang ghi bao thu va ngay 2
	
	#define RTC_CTR_ADDR     			0x0E    // Dia chi thang ghi dieu khien 
	#define RTC_STA_ADDR     			0x0F    // Dia chi thang ghi trang thai
	#define RTC_OFS_ADDR     			0x10    // Dia chi thang ghi Offset
	#define RTC_TEMP_MSB_ADDR     0x11    // Dia chi thang ghi nhiet do (byte cao)
	#define RTC_TEMP_LSB_ADDR     0x12    // Dia chi thang ghi nhiet do (byte thap
#endif
	
// Chuyen tu ma BCD sang thap phan
unsigned char rtc_bcd2dec(unsigned char bcd);  

// Chuyen tu thap sang sang ma BCD
unsigned char rtc_dec2bcd(unsigned char dec);     					

// Ghi du lieu vao thanh ghi cua rtc
void rtc_write(unsigned char regAddr, unsigned char data); 

// Doc du lieu tu thanh ghi cua rtc
unsigned char rtc_read(unsigned char regAddr);   

// Ghi thoi gian vao rtc
void rtc_setTime(unsigned char hrs, unsigned char min, unsigned char sec, unsigned char day, unsigned char dat, unsigned char mth, unsigned char yrs);

// Doc thoi gian tu rtc
void rtc_getTime(unsigned char *hrs, unsigned char *min, unsigned char *sec, unsigned char *day, unsigned char *dat, unsigned char *mth, unsigned char *yrs);

// Khoi tao rtc
void rtc_init(void);	

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/*****END OF FILE****/

