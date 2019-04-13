/*
 * UART.cpp
 *
 * Created: 04.04.2019 21:24:26
 *  Author: murad
 */ 
#include "UART.h"

#include <avr/io.h> //подключение стандартной библиотеки ввода/вывода

void UART_Transmit( unsigned char data ) //Функция отправки данных
{
	while((UCSR0A & 0x20) != 0x20); //ждем опустошения буфера передачи
	UDR0 = data; //Начало передачи данных
}

void UART_Transmit(  char* data ){
	int i=0;
	while(data[i]){
		UART_Transmit((unsigned char)data[i]);
		i++;
	}
}

void UART_Init(){
	UCSR0A=0x00; //скорость обмена 1x, микропроцессорный обмен выключен
	UCSR0B=0x18; //разрешение приема и передачи
	UCSR0C=0x06; //асинхронный режим, контроль четности отключен, 1 стоп бит, 8 бит данных
	UBRR0=103; //скорость передачи 9600 бод/с при тактовой частоте 8 МГц
}
void UART_Init_RX(){
	UCSR0A=0x00; //скорость обмена 1x, микропроцессорный обмен выключен
	UCSR0B=0x18; //разрешение приема и передачи
	UCSR0B|=(1<<RXCIE0);
	UCSR0C=0x06; //асинхронный режим, контроль четности отключен, 1 стоп бит, 8 бит данных
	UBRR0=103; //скорость передачи 9600 бод/с при тактовой частоте 8 МГц
}

char UART_Receive(){
	while(!(UCSR0A&(1<<RXC0)));
	
	return UDR0;
}


void transform(unsigned int num, char* string) {
	if (num < 10) {
		string[0] = num + '0';
		string[1] = '\0';
	}
	else if (num < 100) {
		string[0] = ((num % 100) - (num % 10)) / 10 + '0';
		string[1] = (num % 10) + '0';
		string[2] = '\0';
	}
	else if (num < 1000) {
		string[0] = ((num % 1000) - (num % 100)) / 100 + '0';
		string[1] = ((num % 100) - (num % 10)) / 10 + '0';
		string[2] = (num % 10) + '0';
		string[3] = '\0';
	}
	else if (num < 10000) {
		string[0] = ((num % 10000) - (num % 1000)) / 1000 + '0';
		string[1] = ((num % 1000) - (num % 100)) / 100 + '0';
		string[2] = ((num % 100) - (num % 10)) / 10 + '0';
		string[3] = (num % 10) + '0';
		string[4] = '\0';
	}
	else {
		string[0] = ((num % 100000) - (num % 10000)) / 10000 + '0';
		string[1] = ((num % 10000) - (num % 1000)) / 1000 + '0';
		string[2] = ((num % 1000) - (num % 100)) / 100 + '0';
		string[3] = ((num % 100) - (num % 10)) / 10 + '0';
		string[4] = (num % 10) + '0';
		string[5] = '\0';
	}

}

void UART_Transmit(unsigned int n){
	char ch[5];
	transform(n,ch);
	UART_Transmit(ch);
}