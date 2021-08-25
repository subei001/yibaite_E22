#include "stm32f10x.h"
#include "delay.h"
#include "ebyte.h"
#include "usart.h"	
#include "key.h"
#include "oled.h"
#include "bmp.h"


char string[100]="";
char * dest_string;
uint32_t j=0;
extern uint8_t USART1_FINISH;
extern uint32_t i;

	u8 Set_Config1[]={0xC0,0x00,0x04,0x00,0x00,0x00,0x61}; //C0+addr+length+parameter (ID+net ID+baund)

	u8 Set_Config3[]={0xC0,0x05,0x02,0x17,0x40};//C0+addr+length+parameter (channel+mode)

	
		u8 Message2[]={0x00,0x02,0x17,0x01,0x88,0x11};//target address+Target channel+message	
		u8 Message3[]={0x00,0x03,0x17,0x01,0x99,0x11};//target address+Target channel+message	
		u8 Message4[]={0x00,0x04,0x17,0x01,0x99,0x11};//target address+Target channel+message	
int main(void)
{	
	
		u8 key;	
	u8 count1=0;
	u8 count2=0;
	u8 count3=0;
	
				u8 reccount1=0;
	u8 reccount2=0;
	u8 reccount3=0;
		delay_init();
KEY_Init();
	OLED_Init();
			OLED_Clear()  	; 
	USART_Config();
	E22_400_GPIO_Init();




		USART_GetFlagStatus(USART1, USART_FLAG_TC);//本行可解决串口首字节丢失问题，详情参照CSDN
			UART_PutBytes(USART1,Message2,sizeof (Message2));
		OLED_ShowString(40,0,"TX:",16);
			OLED_ShowString(0,0,"MS:",16);
					OLED_ShowString(85,0,"RX:",16);
	
//				delay_ms(50);
//			UART_PutBytes(USART1,Message2,sizeof (Message2));
//				delay_ms(50);
//			UART_PutBytes(USART1,Message2,sizeof (Message2));
	
//		OLED_ShowNum(30,0,6,3,16);
//	delay_ms(1500);
//		UART_PutBytes(USART1,Message3,sizeof (Message3));
//		UART_PutChar(USART1,0x00);
//		UART_PutChar(USART1,0x03);	
//		UART_PutChar(USART1,0x17);	
//		UART_PutChar(USART1,0x55);	
//		UART_PutChar(USART1,0x66);	
//		UART_PutChar(USART1,0x77);	
//		UART_PutChar(USART1,0x0d);
//		UART_PutChar(USART1,0x0a);
	while(1)
	{
		key=KEY_Scan();
		if(key)
		{
			switch(key)
			{
				case 1:
			UART_PutBytes(USART1,Message2,sizeof (Message2));
				
									count1++;
							OLED_ShowNum(50,2,count1 ,3,16);
					break;
				case 2:
			UART_PutBytes(USART1,Message3,sizeof (Message3));
									count2++;
				
							OLED_ShowNum(50,4,count2 ,3,16);
					break;
				case 3:
			UART_PutBytes(USART1,Message4,sizeof (Message4));
									count3++;
			
							OLED_ShowNum(50,6,count3 ,3,16);
					break;
			}
			delay_ms(600);
		}



		if(USART1_FINISH)
		{

	
				OLED_ShowNum(10,2,string [0],3,16);
			OLED_ShowNum(10,4,string [1],3,16);
			OLED_ShowNum(10,6,string [2],3,16);
		
			
//		OLED_ShowNum(60,2,string[0],2,16);
//					OLED_ShowNum(70,2,string[1],2,16);
//					OLED_ShowNum(80,2,string[2],2,16);
		
			switch(string [0]){
				case 1: reccount1++;OLED_ShowNum(100,0,reccount1,3,16);break;
				case 2: reccount2++;OLED_ShowNum(100,2,reccount2,3,16);break;
				case 3: reccount3++;OLED_ShowNum(100,4,reccount3,3,16);break;
			
			
			}
		
//		OLED_ShowNum(60,2,string[0],2,16);
//					OLED_ShowNum(70,2,string[1],2,16);
//					OLED_ShowNum(80,2,string[2],2,16);


			for(j=0;j<i;j++)
			{
				string[j]=0x00;
			}
			i = 0;
			USART1_FINISH = 0;
		}
	}	
}



 
 