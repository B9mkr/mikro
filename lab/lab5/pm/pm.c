#include <avr/io.h> 
//#include <util/delay.h> 

#define F_CPU 100000L  

#define LED0 (1<<PA7)

//dokumentacja strona 80: http://ww1.microchip.com/downloads/en/devicedoc/doc2503.pdf

//Napisać program powodujący miganie diodą połączoną do pinu PA7 z częstotliwością 4Hz.
//Funkcje opóżniające (delay) należy zrealizwać z wykorzystaniem Timera 0 pracującego:
//a) w trybie NORMAL (odczyt flagi TOV0)
//b) w trybie CTC (odczyt flagi OCF0)

int main(void) 
{
    DDRA  |= LED0;
	TCNT0 = 0x00;
    TCCR0=(1<<CS00) | (1<<CS02);
	
	uint8_t TOC=0;// tIMERoVERFLOWcOUNT

    while(1)
    {
        while((TIFR & 0x01) != 0);

		TCNT0 = 0x00;
		TIFR=0x01;
		TOC++;
		if(TOC >= 2)
		{
			PORTA ^= LED0;
			TOC=0;
		}
    }
	return 0;
}
