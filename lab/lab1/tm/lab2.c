//częstotliwość zegara 
#define F_CPU 1000000L  
 
#include <avr/io.h> 
#include <util/delay.h> 
 
//definicja LED1 (do którego pinu podłączony LED1) 
#define LED1 PB0
 
//definicja LED2 (do którego pinu podłączony LED2)  
#define LED2 PB1
#define LED3 PB2
#define LED4 PB3
#define LED5 PB4
#define LED6 PB5
#define LED7 PB6
#define LED8 PB7
 
 
// Pętla główna 
void main(void) 
{ 
//########### I/O ########### 
    DDRB  |= (1<<LED1) | (1<<LED2) | (1<<LED3) | (1<<LED4) |
            (1<<LED5) | (1<<LED6) | (1<<LED7) | (1<<LED8); //Ustawienie pinów sterujących diodami 
                                         //jako wyjścia 

    PORTB = 0;//(1<<LED1) | (1<<LED2) | (1<<LED3) | (1<<LED3) |
            //(1<<LED4) | (1<<LED5) | (1<<LED6) | (1<<LED7)| (1<<LED8);    //Ustawienie stanu wysokiego na wyjściu  
                                 //sterującym LED1 (stan początkowy) 
     //########################## 
    
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