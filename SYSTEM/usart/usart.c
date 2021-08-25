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
  
  /* Ƕ�������жϿ�������ѡ�� */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* ����USARTΪ�ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  /* �������ȼ�*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* �����ȼ� */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* ʹ���ж� */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* ��ʼ������NVIC */
  NVIC_Init(&NVIC_InitStructure);
}

void USART_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	// �򿪴���GPIO��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	// �򿪴��������ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	// ��USART Tx��GPIO����Ϊ���츴��ģʽ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

  // ��USART Rx��GPIO����Ϊ��������ģʽ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// ���ô��ڵĹ�������
	// ���ò�����
	USART_InitStructure.USART_BaudRate = 9600;
	// ���� �������ֳ�
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// ����ֹͣλ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// ����У��λ
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	// ����Ӳ��������
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	// ���ù���ģʽ���շ�һ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// ��ɴ��ڵĳ�ʼ������
	USART_Init(USART1, &USART_InitStructure);
	
	// �����ж����ȼ�����
	NVIC_Configuration();
	
	// ʹ�ܴ��ڽ����ж�
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);	
	
	// ʹ�ܴ���
	USART_Cmd(USART1, ENABLE);	    
}

//����һ���ֽڣ�8λ��
void USART_SendByte(USART_TypeDef* pUSARTx,uint8_t data)
{
	USART_SendData(pUSARTx, data);
	while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}

//���������ֽڣ�����֣�16λ��
void USART_SendHalfWord(USART_TypeDef* pUSARTx,uint16_t data)     
{ uint8_t  data_h,data_l;
	
	data_h = (data&0xff00) >> 8;
	data_l = data&0xff;
	
	USART_SendData(pUSARTx, data_h);
	while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	USART_SendData(pUSARTx, data_l);
	while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}

//����8λ���ݵ�����
void USART_SendArray( USART_TypeDef * pUSARTx, uint8_t *array, uint8_t num)
{
  uint8_t i;
	
	for(i=0; i<num; i++)
  {
	    /* ����һ���ֽ����ݵ�USART */
	    USART_SendByte(pUSARTx,array[i]);	
  
  }
	/* �ȴ�������� */
	while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET);
}

//�����ַ���
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

//��C�����е�printf,putchar��ʵ�ִ����������Ҫ�ض���c�⺯��fputc�����ڣ��ض�����ʹ��printf,putchar����
int fputc(int ch, FILE *f)
{
		/* ����һ���ֽ����ݵ����� */
		USART_SendData(USART1, (uint8_t) ch);
		
		/* �ȴ�������� */
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}
//��C�����е�scanf��getchar��ʵ�ִ������룬��Ҫ�ض���C�⺯��fgetc�����ڣ��ض�����ʹ��scanf,getchar
int fgetc(FILE *f)
{
		/* �ȴ������������� */
		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(USART1);
}
