/*
 * SOLAR.cpp
 *
 * Created: 09.03.2019 22:08:00
 * Author : murad
 * Программасчитывает значения с аналоговых портов и подаёт сигналы на двигатели, 
 * если разность между значениями будет слишком большой, чтобы повернуть 
 * солнечную панель прямо к свету.
 */ 

///////////////////////////////////
//	RESET	-## ##- VCC
//	ADC2	-#####-			SCK
//	ADC3	-#####- PB1		MISO
//		GND	-#####- PB0		MOSI
////////////////////////////////////


#define F_CPU 1000000UL 
#include <avr/io.h> //подключение стандартной библиотеки ввода/вывода
#include <avr/interrupt.h> //подключаем библиотеку работы с прерываниями
#include "libSol/ADC.h"

//#define DEBUG_SALAR 

#ifndef DEBUG_SALAR
	#include <util/delay.h>
#endif // DEBUG

#ifdef DEBUG_SALAR
	void _delay_ms(int time){}
#endif // DEBUG

typedef unsigned char byte;
#define pin_A 0
#define pin_B 1
#define gist 35

 unsigned int val1;
 unsigned int val2;


int main(void)
{
	
	analogBegin();
	DDRB|=0b00000011;
	PORTB|=0b00000011;
	
	//sei(); //глобальное разрешение прерываний
	
	digitalWrite(pin_A,0);
	digitalWrite(pin_B,1);
	_delay_ms(500);
	digitalWrite(pin_A,1);
	digitalWrite(pin_B,0);
	_delay_ms(500);
	digitalWrite(pin_A,0);
	digitalWrite(pin_B,0);
	_delay_ms(2000);
	while(1)
	{
	   int val1 = analogRead(2); 
	   int val2 = analogRead(3); 
	if((val1-val2)>gist/2){
		digitalWrite(pin_A,0);
		digitalWrite(pin_B,1);
	  }
	else if((val2-val1)>gist/2){
		digitalWrite(pin_A,1);
		digitalWrite(pin_B,0);
	  }
	   else {
		digitalWrite(pin_A,0);
		digitalWrite(pin_B,0);
		}
	}
}
