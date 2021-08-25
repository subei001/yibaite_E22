#ifndef __usart_H
#define __usart_H

#include "stm32f10x.h"
#include <stdio.h>


void UART_PutChar(USART_TypeDef* USARTx, uint8_t Data);
void UART_PutStr (USART_TypeDef* USARTx, uint8_t *str);
void UART_PutBytes (USART_TypeDef* USARTx, uint8_t *str, uint8_t length);

void USART_Config(void);
void USART_SendByte(USART_TypeDef* pUSARTx,uint8_t data);
void USART_SendHalfWord(USART_TypeDef* pUSARTx,uint16_t data);
void USART_SendArray(USART_TypeDef* pUSARTx,uint8_t *array ,uint8_t num);
void USART_SendString(USART_TypeDef* pUSARTx,uint8_t *string);
int fputc(int ch, FILE *f);
int fgetc(FILE *f);

#endif /* __BSP_USART_H */
