/*
 * UART.h
 *
 * Created: 04.04.2019 21:23:16
 *  Author: murad
 */ 


#ifndef UART_H_
#define UART_H_


void UART_Transmit(unsigned char);
void UART_Transmit(char* data);
void UART_Init();
void UART_Init_RX();
char UART_Receive();
void transform(unsigned int, char*);
void UART_Transmit(unsigned int );
#endif /* UART_H_ */