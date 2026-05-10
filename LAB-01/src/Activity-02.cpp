#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRC = DDRC | (1 << PC0) | (1 << PC1) | (1 << PC2) | (1 << PC3);

    while (1)
    {
        PORTC = PORTC | (1 << PC0);
        _delay_ms(1000);

        PORTC = PORTC | (1 << PC1);
        _delay_ms(1000);

        PORTC = PORTC | (1 << PC2);
        _delay_ms(1000);

        PORTC = PORTC | (1 << PC3);
        _delay_ms(1000);
    }

    return 0;
}