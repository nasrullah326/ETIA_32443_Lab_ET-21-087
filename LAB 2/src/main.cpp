#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

// Password
int password[4] = {1, 2, 3, 4};
int entered[4];
int indexPos = 0;

void storeInput(Pint value);

int main(void)
{
    // ================= INPUT (PB1–PB4) =================
    DDRB &= ~((1 << PB1) | (1 << PB2) | (1 << PB3) | (1 << PB4));

    // Enable pull-up resistors
    PORTB |= (1 << PB1) | (1 << PB2) | (1 << PB3) | (1 << PB4);

    // ================= OUTPUT LEDs =================
    DDRD |= (1 << PD5) | (1 << PD6);

    PORTD &= ~((1 << PD5) | (1 << PD6));

    while (1)
    {
        if (!(PINB & (1 << PB1))) storeInput(1);
        if (!(PINB & (1 << PB2))) storeInput(2);
        if (!(PINB & (1 << PB3))) storeInput(3);
        if (!(PINB & (1 << PB4))) storeInput(4);
    }
}

void storeInput(int value)
{
    entered[indexPos] = value;
    indexPos++;

    _delay_ms(250); // debounce

    // wait release
    while (!(PINB & (1 << PB1)) ||
           !(PINB & (1 << PB2)) ||
           !(PINB & (1 << PB3)) ||
           !(PINB & (1 << PB4)));

    if (indexPos == 4)
    {
        int correct = 1;

        for (int i = 0; i < 4; i++)
        {
            if (entered[i] != password[i])
                correct = 0;
        }

        if (correct)
        {
            PORTD |= (1 << PD5);   // GREEN ON
            _delay_ms(2000);
            PORTD &= ~(1 << PD5);  // OFF
        }
        else
        {
            PORTD |= (1 << PD6);   // RED ON
            _delay_ms(2000);
            PORTD &= ~(1 << PD6);
        }

        indexPos = 0;
    }
}