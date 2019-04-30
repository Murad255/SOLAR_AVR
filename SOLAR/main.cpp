/*
 * SOLAR.cpp
 *
 * Created: 09.03.2019 22:08:00
 * Author : murad
 * ѕрограммасчитывает значени€ с аналоговых портов и подаЄт сигналы на двигатели, 
 * если разность между значени€ми будет слишком большой, чтобы повернуть 
 * солнечную панель пр€мо к свету.
 */ 

///////////////////////////////////
//	RESET	-## ##- VCC
//	ADC2	-#####-			SCK
//	ADC3	-#####- PB1		MISO
//	GND		-#####- PB0		MOSI
////////////////////////////////////


#define F_CPU 1000000UL 
#include <avr/io.h> //подключение стандартной библиотеки ввода/вывода
#include <avr/interrupt.h> //подключаем библиотеку работы с прерывани€ми
#include "libSol/ADC.h"
#include "libSol/watcdog.h"

//#define DEBUG_SALAR 
#define  LEFT	digitalWrite(pin_A,0); \
				digitalWrite(pin_B,1);
				
#define  RIGHT	digitalWrite(pin_A,1); \
				digitalWrite(pin_B,0);		
				
#define  STOP	digitalWrite(pin_A,0); \
				digitalWrite(pin_B,0);						
				

typedef unsigned char byte;
#define pin_A 0
#define pin_B 1
#define gist 35

 unsigned int val1;
 unsigned int val2;


int main(void)
{
	
	analogBegin();
	wBegin();
	DDRB|=0b00000011;
	PORTB|=0b00000011;

	
	#ifndef DEBUG_SOLAR
		digitalWrite(pin_A,0);
		digitalWrite(pin_B,1);
		delay(500);
		digitalWrite(pin_A,1);
		digitalWrite(pin_B,0);
		delay(500);
		digitalWrite(pin_A,0);
		digitalWrite(pin_B,0);
		delay(500);
	#endif // DEBUG_SOLAR
	
	while(1)
	{
		LEFT
		delay(2000);
		RIGHT
		delay(2000);
		STOP
		delay(500);
	}
}
