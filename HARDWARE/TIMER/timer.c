#include "timer.h"

void TIM2_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);						//TIM2 时钟使能 
	
	TIM_TimeBaseStructure.TIM_Period = 10000; //设定计数器自动重装值 最大10ms溢出  
	TIM_TimeBaseStructure.TIM_Prescaler =(72-1); 	//预分频器,1M的计数频率,1us加1.	   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式

	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx
	TIM_Cmd(TIM2,ENABLE ); 	//使能定时器2
 
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM2中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //从优先级0级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器	
 
 	TIM_ITConfig( TIM2,TIM_IT_Update,ENABLE);
}

