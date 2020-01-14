#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#define F_CPU 1000000L

#define LCD_DDR DDRB
#define LCD_PORT PORTB
#define LCD_RS 0
#define LCD_EN 1
#define LCD_DB4 4
#define LCD_DB5 5
#define LCD_DB6 6
#define LCD_DB7 7


void wpisz(uint8_t bajt)
{
	//zalaczenie enable 
	LCD_PORT |= _BV(LCD_EN);
	_delay_us(40);
	//przes�anie 4 starszych bit�w
	LCD_PORT = (bajt & 0xF0)|(LCD_PORT & 0x0F);
	_delay_us(40);
	//potwierdzamy przeslanie przez opadajace zbocze en
	LCD_PORT &= ~(_BV(LCD_EN));

	//dodatkowe opoznienie 
	//_delay_ms(1);
	asm volatile("nop");

	//zalaczenie enable 
	LCD_PORT |= _BV(LCD_EN);
	_delay_us(40);
	//przes�anie 4 mlodszych bit�w
	LCD_PORT = ((bajt & 0x0F)<<4)|(LCD_PORT & 0x0F);
	_delay_us(40);
    //potwierdzamy przeslanie
	LCD_PORT &= ~(_BV(LCD_EN));

	//wymagane opoznienie
	//_delay_ms(1);
	asm volatile("nop");
}

void czyscLCD()
{
	 //wysy�anie komendy
	 LCD_PORT &= ~(_BV(LCD_RS));
	 _delay_us(40);
	 wpisz(0b00000001);
	 _delay_us(40);
	 LCD_PORT |= _BV(LCD_RS);

	 _delay_ms(2);
}

void kursor(unsigned char x,unsigned char y)
{
	 LCD_PORT &= ~(_BV(LCD_RS));
	 _delay_us(40);
	 wpisz((x*0x40+y)|0x80);
	 _delay_us(40);
	 LCD_PORT |= _BV(LCD_RS);
	 _delay_ms(2);	
}
void ustawLCD()
{
	 //ustawienie kierunku na wyjscie
	 LCD_DDR = (0xF0)|(_BV(LCD_RS))|(_BV(LCD_EN));
	 //ustawienie stanu niskiego na wszystkich liniach
	 LCD_PORT = 0;

	 //wysy�anie komendy
	 LCD_PORT &= ~(_BV(LCD_RS));
	 _delay_us(40);
	 wpisz(0b00101000);
	 _delay_us(40);
	 //koniec wys�ania komendy
	 LCD_PORT |= _BV(LCD_RS);
	 _delay_us(40);

	 //flaga
	 LCD_PORT &= ~(_BV(LCD_RS));
	 _delay_us(40);
	 wpisz(0b00000100);
	 _delay_us(40);
	 LCD_PORT |= _BV(LCD_RS);
	 _delay_us(40);

	 LCD_PORT &= ~(_BV(LCD_RS));
	 _delay_us(40);
	 wpisz(0b00001100);
	 _delay_us(40);
	 LCD_PORT |= _BV(LCD_RS);
	 _delay_us(40);
	
	

	 czyscLCD();
}

void wyswietl(char *text, int8_t dlogosc)
{
	int8_t x=0;
	while(x<dlogosc)
	{
		  if(x==16)
		  {
		  	 kursor(1,0);
		  }
		  wpisz(text[x]);
		  x++;
	}
}

void LCD_Symbols()
{
	unsigned char i, j,
	
	/****Deklaracja 3 w�asnych symboli****/
	symbols[3][8] =
	{
		{
			0b00000000,
			0b11111000,
			0b10101000,
			0b11011000,
			0b11011000,
			0b10101000,
			0b11111000,
			0b00000000
		},

		{
			0b00000000,
			0b11111000,
			0b11111000,
			0b11011000,
			0b11011000,
			0b11111000,
			0b11111000,
			0b00000000
		},

		{
			0b00000000,
			0b11111000,
			0b11111000,
			0b11111000,
			0b11111000,
			0b11111000,
			0b11111000,
			0b00000000
		}
	};
		char a = 0b01000000; //Zmienna do przechowywania adresu w pami�ci CGRAM
	
	for (i = 0; i < 3; i++) 
	{
		for (j = 0; j < 8; j++) //W tej p�tli do pami�ci CGRAM wysy�ane s� kolejne wiersze znaku
		{
			LCD_PORT &= ~(_BV(LCD_RS));
			wpisz(a); //Wys�anie instrukcji ustawiaj�cej, �e b�dziemy wysy�a� dane do pami�ci CGRAM pod wskazany adres
			LCD_PORT |= _BV(LCD_RS);
			_delay_ms(40); //Op�nienie o 40 milisekund
			wpisz(symbols[i][j]); //Wys�anie do pami�ci CGRAM jednego wiersza znaku
			a++; //Iteracja adresu pami�ci CGRAM (przej�cie do nast�pnego wiersza)
		}
	}
}





int main()
{
	
	
	//char text[]={'A','L','A','M','A','K','O','T','A','A','K','O','T','M','A','A','L','E','E'};
	ustawLCD();
	_delay_us(40);
	kursor(0,0);
	//wyswietl(text,19);
	//wpisz(0);
	while(1)
	{
		unsigned char i;
			for (i = 0; i < 4; i++)
		{
		//	LCD_PORT &= ~(_BV(LCD_RS));
		//	LCD_Send(0b10001111); //Ustawienie kursora na ko�cu pierwszego wiersza
			LCD_PORT |= _BV(LCD_RS);
			wpisz(i); //Wy�wietlenie i-tego symbolu
			_delay_ms(22);
		//	LCD_Clear();
			_delay_ms(500); //Op�nienie o 500 milisekund
			kursor(0,0);
		}
		
	}
}	


