#ifndef __EBYTE_H
#define __EBYTE_H	
#include "stm32f10x.h"

#define E22_400_Serial 	USART1
#define AUX		GPIO_ReadInputDataBit(E22_CHECK_GPIO,E22_CHECK_PIN)

#define E22_M0_PIN			GPIO_Pin_0
#define E22_M1_PIN			GPIO_Pin_1
#define E22_MODE_GPIO 	GPIOA
//E22-400模式配置IO

#define E22_RES_PIN			GPIO_Pin_0
#define E22_RES_GPIO		GPIOB
//E22-400复位IO，低电平复位

#define E22_CHECK_PIN		GPIO_Pin_1
#define E22_CHECK_GPIO	GPIOB
//E22-400状态检测IO

#define E22_MODE_TRANS	0
#define E22_MODE_WOR		1
#define E22_MODE_CONFIG	2
#define E22_MODE_SLEEP	3
////E22-400模式

#define E22_M0	PAout(0)
#define E22_M1	PAout(1)

#define ADDH_Add 		0X00
#define ADDL_Add 		0X01
#define NetID_Add		0X02
#define REG0_Add		0X03
#define REG1_Add		0X04
#define CHANNEL_Add	0X05
#define REG3_Add		0X06
#define KEYH_Add		0X07
#define KEYL_Add		0X08
//寄存器地址

#define ADDH				0X00							//0X00~0XFF
#define ADDL				0X03							//0X00~0XFF
//FFFF为广播和监听地址

#define NetID				0X00							//0X00~0XFF网络地址

#define REG0_UART_Bps_1200			0X00
#define REG0_UART_Bps_2400			0X20
#define REG0_UART_Bps_4800			0X40
#define REG0_UART_Bps_9600			0X60
#define REG0_UART_Bps_19200			0X80
#define REG0_UART_Bps_38400			0XA0
#define REG0_UART_Bps_57600			0XC0
#define REG0_UART_Bps_115200		0XE0
//串口波特率

#define REG0_CheckBit_8N1				0X00
#define REG0_CheckBit_801				0X08
#define REG0_CheckBit_8E1				0X10
//设置串口校验位

#define REG0_AIR_Bps_300				0X00
#define REG0_AIR_Bps_1200				0X01
#define REG0_AIR_Bps_2400				0X02
#define REG0_AIR_Bps_4800				0X03
#define REG0_AIR_Bps_9600				0X04
#define REG0_AIR_Bps_19200			0X05
#define REG0_AIR_Bps_38400			0X06
#define REG0_AIR_Bps_62500			0X07
//设置无线空中速率

#define REG1_Package_240				0X00
#define REG1_Package_128				0X40
#define REG1_Package_64					0X80
#define REG1_Package_32					0XC0
//分包设定

#define REG1_RSSI_OPEN					0X20
#define REG1_RSSI_CLOSE					0X00
//环境噪声使能

#define REG1_TransPower_30			0X00
#define REG1_TransPower_27			0X01
#define REG1_TransPower_24			0X02
#define REG1_TransPower_21			0X03
//设置发射功率

#define REG2_CHANNEL						0X04		//0X00~0X53信道控制0~83

#define REG3_RSSI_BIT_CLOSE			0X00
#define REG3_RSSI_BIT_OPEN			0X80
//启用RSSI字节

#define REG3_TRANS							0X00
#define REG3_POINT							0X40
//设置传输方式

#define REG3_RELAY_CLOSE				0X00
#define REG3_RELAY_OPEN					0X20
//设置中继功能

#define REG3_LBT_CLOSE					0X00
#define REG3_LBT_OPEN						0X10
//设置中LBT使能

#define REG3_WOR_RECEIVER				0X00
#define REG3_LBT_TRANSMITTER		0X04
//WOR模式收发控制

#define REG3_WorPeriod_500ms		0X00
#define REG3_WorPeriod_1000ms		0X01
#define REG3_WorPeriod_1500ms		0X02
#define REG3_WorPeriod_2000ms		0X03
#define REG3_WorPeriod_2500ms		0X04
#define REG3_WorPeriod_3000ms		0X05
#define REG3_WorPeriod_3500ms		0X06
#define REG3_WorPeriod_4000ms		0X07

typedef struct
{
	uint8_t REG0_UART_Bps;
	
	uint8_t REG0_CheckBit;
	
	uint8_t REG0_AIR_Bps;
	
} E22_400_REG0;


void E22_400_GPIO_Init(void);
void E22_400_Reset(void);
void E22_400_SetMode(uint8_t E22_Mode);

void E22_400_ModeAdd_Config(void);
void E22_400_NetAdd_Config(void);
void E22_400_CHANNEL_Config(void);

void E22_400_Reg0_Config(void);

uint8_t E22_400_Transmit(uint8_t Mode_Add_H,uint8_t Mode_Add_L,uint8_t Channel,uint8_t Message);

void AUX_Read(void);
uint8_t AUX_OUTPUT(void);


#endif




