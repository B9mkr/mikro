#include <avr/io.h>
#include <string.h>
#include <util/delay.h>

#define LCD_DDR DDRB
#define LCD_PORT PORTB
#define LCD_RS 2
#define LCD_EN 3
#define LCD_DB4 4
#define LCD_DB5 5
#define LCD_DB6 6
#define LCD_DB7 7

void LCD_SendChar(int8_t bajt)
{
	// wlaczenie linii ENABLE
	LCD_PORT |= _BV(LCD_EN);

	//wys�anie 4 starszych bit�w
	LCD_PORT = (bajt & 0xF0)|(LCD_PORT & 0x0F);

	// potwierdzenie wys�ana danych poprzez opadni�cie ENABLE
	LCD_PORT &= ~(_BV(LCD_EN));

	// odczekanie jednego cyklu
	asm volatile("nop");

	LCD_PORT |= _BV(LCD_EN);
	//wys�anie 4 m�odszych bit�w
	LCD_PORT = ((bajt & 0x0F)<<4)|(LCD_PORT & 0x0F);
	LCD_PORT &= ~(_BV(LCD_EN));

	// odczekanie niezb�dnej d�ugo�ci czasu na potwierdzenie wprowadzenia danych
	_delay_us(40);
}
void LCD_Clear()
{
	// przestawia na linii RS warto�� na 0 po to by wys�a� komend� a nie dane
	LCD_PORT &= ~(_BV(LCD_RS));
	// wysy�amy polecenie wyczyszczenia LCD
	LCD_SendChar(1);

	// przestawia lini� RS na warto�� 1 odpowiadaj�c� wprowadzaniu danych
	LCD_PORT |= _BV(LCD_RS);

	// maksymalny czas oczekiwania na wyczyszczenie ekranu LCD
	_delay_ms(1.64);
}

void LCD_SwitchOn()
{
	// ustawienie kierunku wyj�ciowego dla wszystkich linii
	LCD_DDR = (0xF0)|(_BV(LCD_RS))|(_BV(LCD_EN));

	LCD_PORT = 0;


	LCD_PORT &= ~(_BV(LCD_RS));

	LCD_SendChar(0b00101000);
	LCD_PORT |= _BV(LCD_RS);

	LCD_PORT &= ~(_BV(LCD_RS));

	LCD_SendChar(0b00000110);
	LCD_PORT |= _BV(LCD_RS);


	LCD_PORT &= ~(_BV(LCD_RS));
	LCD_SendChar(0b00001100);
	LCD_PORT |= _BV(LCD_RS);

	LCD_Clear();
}
void LCD_SendText(char *text, int8_t textLength)
{
	int8_t k=0;
	while(k < textLength&&k<16)
	{
		LCD_SendChar(text[k]);
		k++;
	
	}
	
		LCD_PORT &= ~(_BV(LCD_RS));
	LCD_SendChar(0b10101000);
	LCD_PORT |= _BV(LCD_RS);
		while(k < textLength)
	{
		LCD_SendChar(text[k]);
		k++;
	
	
	}
}
int main(void){
 char napis[20] = "Hello World!! EluwinaCOstam";

	LCD_SwitchOn();
	LCD_SendText(napis,20);


        while(1){
        }
        return 0;
} 
