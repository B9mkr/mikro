#include <avr/io.h> 
#include <util/delay.h> 

#define F_CPU 1000000L 

char seg[]={0x00,0x01,0x02,0x03};
//char seg[]={0xFE,0xFD,0xFB,0xF7};
char segCode[]={PA0, PA1, PA2, PA3, PA4, PA5, PA6};//segmenty

//	 PA0
//PA5	PA1
//	 PA6
//PA4	PA2
//   PA3

void main(void) 
{ 
    DDRA = 0xff;
	DDRB = 0x0f;
	int cnt, num, temp, i;
	
	short ost[]={1000,100,10};

	//		   0	1	 2	  3    4	5	 6	  7	   8	 9
	char li[]={0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00, 0x10};

    while(1)
    {
		for(cnt = 9999; cnt < 0; cnt--)
		{
			for (i = 0; i < 100; i++)
            {
				num = cnt;
				temp = num / 1000;
                num = num % 1000;
                PORTB = seg[0]; 
                PORTA = li[temp];
                _delay_ms(1);

				temp = num / 100;
                num = num % 100;
                PORTB = seg[1];
                PORTA = li[temp];
                _delay_ms(1);
                
				temp = num / 10;
                PORTB = seg[2];
                PORTA = li[temp];
                _delay_ms(1);

                temp = num % 10;
                PORTB = seg[3];
                PORTA = li[temp];
                _delay_ms(1);
        	}
		}
    }

} 
