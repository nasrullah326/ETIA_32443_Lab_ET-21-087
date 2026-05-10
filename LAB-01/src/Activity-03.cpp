#define F_CPU 16000000UL

#include <avr/io.h>

int main(void)
{
    DDRB = DDRB | (1 << PB0);

    DDRD = DDRD & ~(1 << PD2);

    while (1)
    {
        if (PIND & (1 << PD2))
        {
            PORTB = PORTB | (1 << PB0); 
        }
        else
        {
            PORTB = PORTB & ~(1 << PB0); 
        }
    }

    return 0;
}