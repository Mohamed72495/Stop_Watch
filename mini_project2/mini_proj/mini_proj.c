#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>



unsigned char s1=0;

unsigned char s2=0;

unsigned char m1=0;

unsigned char m2=0;

unsigned char h1=0;

unsigned char h2=0;

int n=0;



ISR(TIMER1_COMPA_vect){
	OCR1A=976;
	//	OCR1A=200;
	s1++;

	if(s1==10){
		s1=0;
		s2++;
		if(s2==6){
			s2=0;
			m1++;

		}
		if(m1==10){
			m1=0;
			m2++;
			if(m2==6){
				m2=0;
				h1++;
			}
		}
		if(h1==10){
			h1=0;
			h2++;}
		if((h1==4)&&(h2==2)){
			s1=0;
			s2=0;
			m1=0;
			m2=0;
			h1=0;
			h2=0;

		}




	}


}


ISR(INT0_vect){
	s1=0;
	s2=0;
	m1=0;
	m2=0;
	h1=0;
	h2=0;
}

ISR(INT1_vect){
	TCCR1B = 0 ;
	//	TCCR1A = (1<<FOC1A)   ;
	TIMSK&=~(1<<4);

}

ISR(INT2_vect){
	TIMSK=1<<4;
	TCCR1A = (1<<FOC1A)   ;
	TCCR1B = (1<<WGM12) |  (1<<CS10) |  (1<<CS12)  ;
}

void init_INT2(void){
	DDRB &=~(1<<2);  //0 TO INPUT
	PORTB |=(1<<2);  //0 TO INPUT

	MCUCSR&=~(1<<6);
	GICR|=1<<5;
	SREG |=1<<7;

}
void init_INT1(void){
	DDRD &=~(1<<3);
	PORTD &=~(1<<3);
	MCUCR|=(1<<3) |(1<<2);
	GICR|=1<<7;
	SREG |=1<<7;

}
void INTO_Init(void){
	GICR |= (1 <<INT0);  //module interrupt enable
	DDRD &= ~(1 << 2); //port d input
	PORTD |= (1 << 2); //port d input
	MCUCR |= (1<< ISC01); //falling edge
	SREG |= (1<<7);  //I-bit = 1
}
void timer1(void){
	TCNT1=0;
	OCR1A=976;
	TIMSK=1<<4;
	TCCR1A = (1<<FOC1A)   ;
	TCCR1B = (1<<WGM12) |  (1<<CS10) |  (1<<CS12)  ;

}
void display(unsigned char x){
	PORTC = (PORTC & 0xF0)|(x & 0x0F);

}

int main(void){
	DDRA |=0x3F;   //ENABLE 6 7SEGMENT
	PORTA|=0b00111111;	//ENABLE IT
	DDRC |=0x0F;   //ENABLE AS OUTPUT
	PORTC &=~(0x0F); //PRINT 0 AT FIRST
	SREG|=1<<7;
	timer1();
	INTO_Init();
	init_INT1();
	init_INT2();
	while(1){

		PORTA =(PORTA & 0xC0)|(0x01);
		//		PORTC = (PORTC & 0xF0)|(s1 & 0x0F);
		display(s1);
		//		PORTA =(PORTA & 0xC0)|(0x01);
		_delay_ms(2);
		//		PORTA =(PORTA & 0xC0);


		PORTA =(PORTA & 0xC0)|(0x02);
		//		PORTC = (PORTC & 0xF0)|(s2 & 0x0F);
		display(s2);
		//		PORTA =(PORTA & 0xC0)|(0x02);
		_delay_ms(2);
		//		PORTA =(PORTA & 0xC0);


		PORTA =(PORTA & 0xC0)|(0x04);
		//		PORTC = (PORTC & 0xF0)|(m1 & 0x0F);
		display(m1);
		//		PORTA =(PORTA & 0xC0)|(0x04);
		_delay_ms(2);
		//		PORTA =(PORTA & 0xC0);


		PORTA =(PORTA & 0xC0)|(0x08);
		//		PORTC = (PORTC & 0xF0)|(m2 & 0x0F);
		display(m2);
		//		PORTA =(PORTA & 0xC0)|(0x08);
		_delay_ms(2);
		//		PORTA =(PORTA & 0xC0);


		PORTA =(PORTA & 0xC0)|(0x10);
		//		PORTC = (PORTC & 0xF0)|(h1 & 0x0F);
		display(h1);
		//		PORTA =(PORTA & 0xC0)|(0x10);
		_delay_ms(2);
		//		PORTA =(PORTA & 0xC0);


		PORTA =(PORTA & 0xC0)|(0x20);
		//		PORTC = (PORTC & 0xF0)|(h2 & 0x0F);
		display(h2);
		//		PORTA =(PORTA & 0xC0)|(0x20);
		_delay_ms(2);
		//		PORTA =(PORTA & 0xC0);



	}
}


