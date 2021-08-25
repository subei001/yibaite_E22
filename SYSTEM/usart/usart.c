#include "usart.h"

 void UART_PutChar(USART_TypeDef* USARTx, uint8_t Data){
    USART_SendData(USARTx, Data);
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET){}

}
void UART_PutStr (USART_TypeDef* USARTx, uint8_t *str){  
    while (0 != *str){
        UART_PutChar(USARTx, *str);  
        str++;  
    }
}
void UART_PutBytes (USART_TypeDef* USARTx, uint8_t *str, uint8_t length){
		int i=0;
    for(i=0;i<length;i++){
        UART_PutChar(USARTx, *str);  
        str++;  
    }
}


static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* 嵌套向量中断控制器组选择 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* 配置USART为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  /* 抢断优先级*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* 子优先级 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* 使能中断 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* 初始化配置NVIC */
  NVIC_Init(&NVIC_InitStructure);
}

void USART_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	// 打开串口GPIO的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	// 打开串口外设的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	// 将USART Tx的GPIO配置为推挽复用模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

  // 将USART Rx的GPIO配置为浮空输入模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// 配置串口的工作参数
	// 配置波特率
	USART_InitStructure.USART_BaudRate = 9600;
	// 配置 针数据字长
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// 配置停止位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// 配置校验位
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	// 配置硬件流控制
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	// 配置工作模式，收发一起
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// 完成串口的初始化配置
	USART_Init(USART1, &USART_InitStructure);
	
	// 串口中断优先级配置
	NVIC_Configuration();
	
	// 使能串口接收中断
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);	
	
	// 使能串口
	USART_Cmd(USART1, ENABLE);	    
}

//传送一个字节（8位）
void USART_SendByte(USART_TypeDef* pUSARTx,uint8_t data)
{
	USART_SendData(pUSARTx, data);
	while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}

//传送两个字节（半个字，16位）
void USART_SendHalfWord(USART_TypeDef* pUSARTx,uint16_t data)     
{ uint8_t  data_h,data_l;
	
	data_h = (data&0xff00) >> 8;
	data_l = data&0xff;
	
	USART_SendData(pUSARTx, data_h);
	while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	USART_SendData(pUSARTx, data_l);
	while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}

//传送8位数据的数组
void USART_SendArray( USART_TypeDef * pUSARTx, uint8_t *array, uint8_t num)
{
  uint8_t i;
	
	for(i=0; i<num; i++)
  {
	    /* 发送一个字节数据到USART */
	    USART_SendByte(pUSARTx,array[i]);	
  
  }
	/* 等待发送完成 */
	while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET);
}

//传送字符串
void  USART_SendString(USART_TypeDef* pUSARTx,uint8_t *string)
{
	uint8_t  i=0;
	do
	{
		USART_SendByte(pUSARTx, *(string+i));
		i++;
	}while(*(string+i) != '\0');
	while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET);
}  

//用C语言中的printf,putchar来实现串口输出，需要重定向c库函数fputc到串口，重定向后可使用printf,putchar函数
int fputc(int ch, FILE *f)
{
		/* 发送一个字节数据到串口 */
		USART_SendData(USART1, (uint8_t) ch);
		
		/* 等待发送完毕 */
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}
//用C语言中的scanf，getchar来实现串口输入，需要重定向C库函数fgetc到串口，重定向后可使用scanf,getchar
int fgetc(FILE *f)
{
		/* 等待串口输入数据 */
		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(USART1);
}
