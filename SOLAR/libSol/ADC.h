/*
 * IncFile1.h
 *
 * Created: 13.04.2019 19:17:25
 *  Author: murad
 */ 


#ifndef ADC_H_
#define ADC_H_

unsigned int analogRead(int pin);
void digitalWrite(int pin,bool lew);
void analogBegin();


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
	ADCSRA|=(1<<ADSC);			//начинаем преобразование
	while(ADCSRA &(1<<ADSC));	//пока не завершится преобразование
	return  (unsigned int)ADC;
}


void digitalWrite(int pin,bool lew){
	if (lew)PORTB|=(1<<pin);
	
	else PORTB&=~(1<<pin);
}

void analogBegin(){
	
	ADCSRA|=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<< ADPS0);
	//включение АЦП, запуск от периферии, разрешение прерывания от АЦП, предделитель на 128
	ADMUX|=(1<<MUX1);//(1<<REFS0)|(1<<MUX1); //опорное напряжение - Vпит, вход ADC1
	//ADCSRB=0x04; //запуск от прерывания по переполнению таймера T0
}

#endif /* INCFILE1_H_ */