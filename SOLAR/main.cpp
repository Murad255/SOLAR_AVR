/*
 * SOLAR.cpp
 *
 * Created: 09.03.2019 22:08:00
 * Author : murad
 * ������������������ �������� � ���������� ������ � ����� ������� �� ���������, 
 * ���� �������� ����� ���������� ����� ������� �������, ����� ��������� 
 * ��������� ������ ����� � ����� 
 */ 
#define F_CPU 1000000UL 
#include <avr/io.h> //����������� ����������� ���������� �����/������
#include <avr/interrupt.h> //���������� ���������� ������ � ������������

//#define DEBUG_SALAR 

#ifndef DEBUG_SALAR
	#include <util/delay.h>
#endif // DEBUG

#ifdef DEBUG_SALAR
	void _delay_ms(int time){}
#endif // DEBUG

///////////////////////////////////
//	RESET	-## ##- VCC
//	ADC2	-#####-			SCK
//	ADC3	-#####- PB1		MISO
//		GND	-#####- PB0		MOSI
////////////////////////////////////

typedef unsigned char byte;
#define pin_A 0
#define pin_B 1
#define gist 35

 unsigned int val1;
 unsigned int val2;
unsigned int analogRead(int pin);
void digitalWrite(int pin,bool lew);
void analogBegin();

//
//ISR(TIM0_OVF_vect) //������������ ��������� ���������� �� ������������ �������
//{
	//// !!!��������!!!
	//// ��� ���������� ������������ ���������� �� �������, ���� ���� � ��� ������ �� ��������, ��� ����������� �� �����!
//}
//
//ISR(ADC_vect) //������������ ��������� ���������� �� ���
//{
	//
//}


int main(void)
{
	
	analogBegin();
	DDRB|=0b00000011;
	PORTB|=0b00000011;
	
	//sei(); //���������� ���������� ����������
	
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

unsigned int analogRead( int pin){
	switch (pin){
	case (1):
		ADMUX&=~(1<<MUX0);
		ADMUX&=~(1<<MUX1);
	break;
	case (2):
		ADMUX|=(1<<MUX1);
		ADMUX&=~(1<<MUX0);
	break;
	
	case (3):
		ADMUX|=(1<<MUX1)|(1<<MUX0);
	break;


	default:

	break;
	}
ADCSRA|=(1<<ADSC);			//�������� ��������������
while(ADCSRA &(1<<ADSC));	//���� �� ���������� ��������������
	return  (unsigned int)ADC;
}


void digitalWrite(int pin,bool lew){
	if (lew)PORTB|=(1<<pin);
	
	else PORTB&=~(1<<pin);
}

void analogBegin(){
	
	ADCSRA|=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<< ADPS0); 
//��������� ���, ������ �� ���������, ���������� ���������� �� ���, ������������ �� 128
	ADMUX|=(1<<MUX1);//(1<<REFS0)|(1<<MUX1); //������� ���������� - V���, ���� ADC1
		//ADCSRB=0x04; //������ �� ���������� �� ������������ ������� T0
}