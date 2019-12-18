#include <avr/io.h> 
#include <util/delay.h> 
 
 
void main(void) 
{ 
    DDRB = 0xFF;

    PORTB = 0;
	
    // ---ZAD2-------------------------

    while(1)
    {
        for(int i = 0; i < 8; i++)
        {    
            PORTB ^= _BV(i);
        
            _delay_ms(500);
        }


         for(int i = 7; i >= 0; i--)
        {    
            PORTB ^= _BV(i);
        
            _delay_ms(500);
        }
    }



 
    // ---ZAD1-------------------------

    /*int i = 0;
    int powrot = 0;

    while (1) //Pętla główna 
    {
        if(i==5)
            powrot=1;
        if(i==0)
            powrot=0;

        PORTB = 7<<i;

        i+=1-(2*powrot);

        _delay_ms(500); //opóźnienie 1000ms czyli 1s 
    }*/

    // ---------------------------------
} 