#include "ebyte.h"
#include "usart.h"

/*
0:本次接收到低电平
1:本次接收到高电平
2:之前接收过低电平
3:之前接收过高电平
4:探测到下降沿
5:探测到上升沿
*/
uint8_t AUX_Indice = 0x00;

void E22_400_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = E22_M0_PIN|E22_M1_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//复用推挽输出
  GPIO_Init(E22_MODE_GPIO, &GPIO_InitStructure);//初始化E22-400模式配制IO
	
//	GPIO_InitStructure.GPIO_Pin = E22_RES_PIN; 
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//复用推挽输出
//  GPIO_Init(E22_RES_GPIO, &GPIO_InitStructure);//初始化E22-400复位IO
//	
//	GPIO_InitStructure.GPIO_Pin = E22_CHECK_PIN; 
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//上拉输入
//  GPIO_Init(E22_CHECK_GPIO, &GPIO_InitStructure);//初始化E22-400状态检测IO
	
	GPIO_ResetBits(E22_MODE_GPIO, E22_M0_PIN);
	GPIO_ResetBits(E22_MODE_GPIO, E22_M1_PIN);
	//初始化模式休眠状态

//	GPIO_SetBits(E22_RES_GPIO, E22_RES_PIN);//复位引脚高电平
}







