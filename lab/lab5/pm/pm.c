#include <avr/io.h> 
//#include <util/delay.h> 

#define F_CPU 100000L  

#define LED0 (1<<PA7)

//dokumentacja strona 80: http://ww1.microchip.com/downloads/en/devicedoc/doc2503.pdf

//Napisa� program powoduj�cy miganie diod� po��czon� do pinu PA7 z cz�stotliwo�ci� 4Hz.
//Funkcje op�niaj�ce (delay) nale�y zrealizwa� z wykorzystaniem Timera 0 pracuj�cego:
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
