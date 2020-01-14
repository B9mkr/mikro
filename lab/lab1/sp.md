# Sprawozdanie 1

7.11.2019 Borys Mushka 5.4/8

14
21
28
05.12
12
19

## Zadanie:

Wyświetlenie po koleji diod a póżniej po koleji zgaszenie.

## Kod programu:

```c
#define F_CPU 1000000L

#include <avr/io.h>
#include <util/delay.h>

#define LED1 (1<<PA0)
#define LED2 (1<<PA1)
#define LED3 (1<<PA2)
#define LED4 (1<<PA3)
#define LED5 (1<<PA4)
#define LED6 (1<<PA5)
#define LED7 (1<<PA6)
#define LED8 (1<<PA7)

int main(void)
{
        DDRA |= 0xFF;

        while (1) {
                PORTA |= LED1;
                _delay_ms(80);
                PORTA |= LED2;
                _delay_ms(80);
                PORTA |= LED3;
                _delay_ms(80);
                PORTA |= LED4;
                _delay_ms(80);
                PORTA |= LED5;
                _delay_ms(80);
                PORTA |= LED6;
                _delay_ms(80);
                PORTA |= LED7;
                _delay_ms(80);
                PORTA |= LED8;
                _delay_ms(80);

                PORTA &= ~LED8;
                _delay_ms(80);
                PORTA &= ~LED7;
                _delay_ms(80);
                PORTA &= ~LED6;
                _delay_ms(80);
                PORTA &= ~LED5;
                _delay_ms(80);
                PORTA &= ~LED4;
                _delay_ms(80);
                PORTA &= ~LED3;
                _delay_ms(80);
                PORTA &= ~LED2;
                _delay_ms(80);
                PORTA &= ~LED1;
                _delay_ms(80);
        }
        return 0;
}

```

## Wnioski

Do wykonaia ćwiczeia należały ustawić wszustkie porty A jako wyjście.
