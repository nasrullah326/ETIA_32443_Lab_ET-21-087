
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define ROAD_RED PB2
#define ROAD_YELLOW PB3
#define ROAD_GREEN PB4

#define PED_RED PB1
#define PED_GREEN PB0

volatile uint8_t emergency_flag = 0;
volatile uint8_t pedestrian_flag = 0;
volatile uint8_t maintenance_flag = 0;

void normalMode(void);
void emergencyMode(void);
void pedestrianMode(void);
void maintenanceMode(void);
void allOff(void);

int main(void)
{
    DDRB |= (1 << ROAD_RED) |
            (1 << ROAD_YELLOW) |
            (1 << ROAD_GREEN) |
            (1 << PED_RED) |
            (1 << PED_GREEN);

    DDRD &= ~((1 << PD2) | (1 << PD3));
    DDRC &= ~(1 << PC0);

    PORTD |= (1 << PD2) | (1 << PD3);
    PORTC |= (1 << PC0);

    EICRA |= (1 << ISC01);
    EICRA &= ~(1 << ISC00);

    EICRA |= (1 << ISC11);
    EICRA &= ~(1 << ISC10);

    EIMSK |= (1 << INT0) | (1 << INT1);

    PCMSK1 |= (1 << PCINT8);

    PCICR |= (1 << PCIE1);

    sei();

    while (1)
    {
        if (maintenance_flag)
        {
            maintenanceMode();
        }
        else if (emergency_flag)
        {
            emergencyMode();
        }
        else if (pedestrian_flag)
        {
            pedestrianMode();
        }
        else
        {
            normalMode();
        }
    }
}

void normalMode(void)
{
    PORTB = (1 << ROAD_RED) | (1 << PED_GREEN);

    for (uint8_t i = 0; i < 50; i++)
    {
        _delay_ms(100);

        if (emergency_flag || pedestrian_flag || maintenance_flag)
            return;
    }

    PORTB = (1 << ROAD_GREEN) | (1 << PED_RED);

    for (uint8_t i = 0; i < 50; i++)
    {
        _delay_ms(100);

        if (emergency_flag || pedestrian_flag || maintenance_flag)
            return;
    }
}

void emergencyMode(void)
{
    allOff();

    PORTB |= (1 << PED_RED) | (1 << ROAD_GREEN);

    for (uint8_t i = 0; i < 100; i++)
    {
        _delay_ms(100);

        if (maintenance_flag)
            return;
    }

    emergency_flag = 0;
}

void pedestrianMode(void)
{
    PORTB |= (1 << ROAD_YELLOW);

    for (uint8_t i = 0; i < 50; i++)
    {
        _delay_ms(100);

        if (emergency_flag || maintenance_flag)
            return;
    }

    allOff();

    PORTB |= (1 << ROAD_RED) | (1 << PED_GREEN);

    for (uint8_t i = 0; i < 100; i++)
    {
        _delay_ms(100);

        if (emergency_flag || maintenance_flag)
            return;
    }

    pedestrian_flag = 0;
}

void maintenanceMode(void)
{
    while (maintenance_flag)
    {
        allOff();

        PORTB |= (1 << ROAD_YELLOW);

        _delay_ms(500);

        PORTB &= ~(1 << ROAD_YELLOW);

        _delay_ms(500);
    }
}

void allOff(void)
{
    PORTB &= ~((1 << ROAD_RED) |
               (1 << ROAD_YELLOW) |
               (1 << ROAD_GREEN) |
               (1 << PED_RED) |
               (1 << PED_GREEN));
}

ISR(INT0_vect)
{
    emergency_flag = 1;
}

ISR(INT1_vect)
{
    pedestrian_flag = 1;
}

ISR(PCINT1_vect)
{
    if (!(PINC & (1 << PC0)))
    {
        maintenance_flag ^= 1;
    }
}
